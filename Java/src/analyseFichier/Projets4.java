/**
 * 
 */
package analyseFichier;
import java.io.*;
import java.nio.charset.StandardCharsets;

/**
 * @author xenoswifts
 *
 */
public class Projets4 {
	
	public static final int INODE_TABLE_SIZE=10;
	public static final int INODE_SIZE = (32/4)+6+((26*2)/4);
	private static final String cpy_passwd="passwd\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	
	
	public static String inverserByte(byte[] chaine) {
		String New_chaine= new String(chaine,StandardCharsets.UTF_8);
		return New_chaine;
	}
	
	public static int BigEndianToLittleEndianint(int value) { 
	    int a = (value >> 24) & 0xFF; 
	    int b = (value >> 16) & 0xFF; 
	    int c = (value >> 8) & 0xFF; 
	    int d = value & 0xFF; 
	    int result = (d << 24) | (c << 16) | (b << 8) | a; 
	    return result; 
	}

	public static void verificationInode(Inode_table it) {
		int nb_inode=it.getNb_inode();
		Inode in=it.getInode(0);
		Inode in_1;
		for(int i=1;i<nb_inode;i++) {
			in_1=it.getInode(i);
			System.out.println("suisse "+i+" "+in.getFirst_byte()+" "+in_1.getFirst_byte()+" "+in.getNblock()+"\n");
			if(in.getFirst_byte()+in.getNblock()*4!=in_1.getFirst_byte()) {
				System.out.println("Catalogue incorrect\n");
				System.exit(6);
			}
			in=in_1;
		}
	}
	
	public static void verificationUsertable(RandomAccessFile reader,Super_block sb,Inode i_passwd) {
		long pos=(long)i_passwd.getFirst_byte();
		int nb_user=0;String s;
		
		try {
			
			reader.seek(pos);
			s=reader.readLine();
			while(s!=null) {
				/*System.out.println(s);*/
				if(s.length()>65) {nb_user++;}
				s=reader.readLine();
			}
			if(nb_user!=sb.getNb_user()){
				System.out.println("nombre d'utilisateurs incorrect\n");
				System.exit(5);
			}
			
			
		}
		catch(Exception e) {
			System.out.println("Erreur lecture fichier");
			System.exit(5);
		}
		
	}
	public static void verification(RandomAccessFile reader,Super_block sb) {
		Inode_table it=new Inode_table(10);
		int nb_i=0,i_passwd=0;
		int nb_block=0;
		User_table ut= new User_table(5);
		Inode i=it.getInode(nb_i);
		i.set_Inode(reader);
		while(nb_i<sb.getNb_fichier()) {
			i.printInode();
			if(cpy_passwd.compareTo(i.getName())==0) {i_passwd=nb_i;}
			nb_block+=i.getNblock();
			nb_i++;
			i=it.getInode(nb_i);
			i.set_Inode(reader);
			
		}
		if(nb_i!=sb.getNb_fichier() || nb_block!=sb.getNb_block_disk() || it.getInode(nb_i-1).getFirst_byte()+
				(it.getInode(nb_i-1).getNblock())*4!=sb.getFirst_free_byte()) {
			System.out.println("Le super bloc n'est pas valide");
			System.exit(4);	
		}
		verificationUsertable(reader,sb,it.getInode(i_passwd));
		verificationInode(it);
		
		
			

	}
	
	public static void main(String[] args) {
		Super_block sb= new Super_block();
		try {
			//modifier le chemin pour que le programme puisse être utilisé sur un autre pc
			RandomAccessFile d0    = new RandomAccessFile("/home/xenoswifts/Bureau/OScratch/OScratch/d0","r");
			sb.set_super_block(d0);
			sb.printsb();
			verification(d0,sb);
			d0.close();
		}
		catch(Exception e) {
			e.printStackTrace();
			System.out.println("Erreur ouverture fichier");
			System.exit(2);
		}
		
			
	}

}
