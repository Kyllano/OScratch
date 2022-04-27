/**
 * 
 */
package défragmentation;

import java.io.RandomAccessFile;

import utils.*;

/**
 * @author xenoswifts
 *
 */
public class Defragmentation {

	/**
	 * 
	 */
	public static Inode_table init_Inode_table(RandomAccessFile fd,Super_block sb) {
		Inode_table it=new Inode_table();
		for(int i=0;i<sb.getNb_fichier();i++) {
			it.getInode(i).set_Inode(fd);
		}
		return it;
	}
	

	
	
	public static void defragmentation(RandomAccessFile fd,Super_block sb,Inode_table it) {
		int byte_start=1136;
		try {
		  for(int i=0;i<sb.getNb_fichier();i++) {
			if(it.getInode(i).getFirst_byte()!=byte_start) {
				byte[] cpy=new byte[it.getInode(i).getNblock()*4];
				fd.seek(it.getInode(i).getFirst_byte());
				fd.read(cpy,0,it.getInode(i).getNblock()*4);
				fd.seek(byte_start);
				fd.write(cpy,0,it.getInode(i).getNblock()*4);
				it.getInode(i).setFirst_byte(byte_start);
				
			}
			byte_start+=it.getInode(i).getNblock()*4;
		  }
		  fd.seek(16);
		  for(int j=0;j<sb.getNb_fichier();j++) {
			  it.getInode(j).write_Inode(fd);
		  }
		  
		}
		catch(Exception e) {
			System.out.println("Erreur défragmentation fichier");
			System.exit(2);
		}
	}
	
	public static void main(String[] args) {
		Super_block sb= new Super_block();
		try {
			//modifier le chemin pour que le programme puisse être utilisé sur un autre pc
			RandomAccessFile d0    = new RandomAccessFile("/home/xenoswifts/Bureau/OScratch/OScratch/d0","rw");
			sb.set_super_block(d0);
			sb.printsb();
			defragmentation(d0,sb,init_Inode_table(d0,sb));
			d0.close();
		}
		catch(Exception e) {
			e.getStackTrace();
			System.out.println("Erreur ouverture fichier");
			System.exit(2);
		}

	}

}
