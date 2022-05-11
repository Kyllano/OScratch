package défragmentation;

import java.io.RandomAccessFile;

import utils.*;

/**
 * @author xenoswifts
 *
 */
public class Defragmentation {

	public static Inode_table init_Inode_table(RandomAccessFile fd,Super_block sb) {
		Inode_table it=new Inode_table();
		for(int i=0;i<sb.getNb_fichier();i++) {
			it.getInode(i).set_Inode(fd);
		}
		return it;
	}
	
	public static String defragmentation(RandomAccessFile fd,Super_block sb,Inode_table it) {
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
		  return "tout est ok!";
		  
		}
		catch(Exception e) {
			return "Erreur défragmentation fichier";
		}
	}
	
	public static String run(String diskname) {
		Super_block sb= new Super_block();
		String err;
		try {
			//modifier le chemin pour que le programme puisse être utilisé sur un autre pc
			RandomAccessFile opencheck = new RandomAccessFile("../../"+diskname,"r");
			opencheck.close();
			RandomAccessFile d0 = new RandomAccessFile("../../"+diskname,"rw");
			err=sb.set_super_block(d0);
			if(err.compareTo("tout est ok!")!=0) {return err;}
			err=defragmentation(d0,sb,init_Inode_table(d0,sb));
			if(err.compareTo("tout est ok!")!=0) {return err;}
			d0.close();
			return err;
		}
		catch(Exception e) {
			return "Erreur d'ouverture du disque";
		}
	}
}
