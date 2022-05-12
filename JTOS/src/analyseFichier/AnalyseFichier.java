package analyseFichier;
import java.io.*;
import java.nio.charset.StandardCharsets;

import utils.User_table;
import utils.Super_block;
import utils.Inode;
import utils.Inode_table;

/**
 * @author xenoswifts
 *
 */
public class AnalyseFichier {
	
	public static final int INODE_TABLE_SIZE = 10;
	public static final int INODE_SIZE = (32/4)+6+((26*2)/4);
	private static final String cpy_passwd = "passwd\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	
	
	public static String inverserByte(byte[] chaine) {
		String New_chaine = new String(chaine,StandardCharsets.UTF_8);
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

	public static String verificationInode(Inode_table it,int nb_i) {
		int nb_inode=it.getNb_inode();
		Inode in=it.getInode(0);
		Inode in_1;
		for(int i=1;i<nb_i;i++) {
			in_1=it.getInode(i);
			if((in.getFirst_byte()+in.getNblock()*4)!=in_1.getFirst_byte()) {
				return "problème de fragmentation";
			}
			in=in_1;
		}
		return "tout est ok!";
	}
	
	public static String verificationUsertable(RandomAccessFile reader,Super_block sb,Inode i_passwd) {
		long pos=(long)i_passwd.getFirst_byte();
		int nb_user=0,size=i_passwd.getSize();String s;
		
		try {
			
			reader.seek(pos);
			s=reader.readLine();
			while(size>65) {
				nb_user++;
				size-=s.length();
				s=reader.readLine();
			}
			if(nb_user!=sb.getNb_user()){
				return "nombre d'utilisateurs incorrect";
			}
			return "tout est ok!";
			
			
		}
		catch(Exception e) {
			return "Erreur lecture fichier";
		}
		
	}
	public static String verification(RandomAccessFile reader,Super_block sb) {
		Inode_table it=new Inode_table();
		Inode i;String err;
		int nb_i=0,i_passwd=0,nb_block=0;
		User_table ut= new User_table(6);
		while(nb_i<sb.getNb_fichier()) {
			i=it.getInode(nb_i);
			i.set_Inode(reader);
			if(cpy_passwd.compareTo(i.getName())==0) {i_passwd=nb_i;}
			if(ut.IsInTable(i.getUid())==false) {ut.Insert_new_user(i.getUid());}
			nb_block+=i.getNblock();
			nb_i++;
			
		}
		if(nb_block!=sb.getNb_block_disk() || it.getInode(nb_i-1).getFirst_byte()+
				(it.getInode(nb_i-1).getNblock())*4!=sb.getFirst_free_byte()) {
			return "Le super bloc n'est pas valide";
		}
		err=verificationUsertable(reader,sb,it.getInode(i_passwd));
		if(err.compareTo("tout est ok!")!=0) {return err;}
		err=verificationInode(it,nb_i);
		if(err.compareTo("tout est ok!")!=0) {return err;}
		return err;
		
		
			

	}
	
	public static String run(String diskname) {
		Super_block sb= new Super_block();
		String err;
		try {
			//modifier le chemin pour que le programme puisse être utilisé sur un autre pc
			RandomAccessFile d0    = new RandomAccessFile("../../disk/"+diskname,"r");
			err=sb.set_super_block(d0);
			if(err.compareTo("tout est ok!")!=0) {return err;}
			err=verification(d0,sb);
			if(err.compareTo("tout est ok!")!=0) {return err;}
			d0.close();
			return err;
		}
		catch(Exception e) {
			return "Erreur d'ouverture du disque";
		}
		
			
	}

}
