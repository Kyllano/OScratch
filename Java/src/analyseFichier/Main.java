/**
 * 
 */
package analyseFichier;
import java.io.*;

/**
 * @author xenoswifts
 *
 */
public class Main {
	
	public static final int INODE_TABLE_SIZE=10;
	public static final int INODE_SIZE = (32/4)+6+((26*2)/4);

	
	public static void verification(DataInputStream reader,Super_block sb) {
		Inode_table it=new Inode_table(10);int nb_i=0;int nb_block=4+(INODE_SIZE*INODE_TABLE_SIZE);
		User_table ut= new User_table(5);
		Inode i=it.getInode(nb_i);
		i.set_Inode(reader);
		while(!i.isEmpty() && nb_i<10) {
			nb_block+=i.getNblock();
			if(!ut.IsInTable(i.getUid()) && !ut.Insert_new_user(i.getUid())) {break;}
			nb_i++;
			i=it.getInode(nb_i);
			i.set_Inode(reader);
			
		}
		if(nb_i!=sb.getNb_fichier() || ut.getNb_user()!=sb.getNb_user() 
				|| nb_block!=sb.getNb_block_disk() || it.getInode(nb_i-1).getFirst_byte()!=sb.getFirst_free_byte()) {
			System.out.println("Le super bloc n'est pas valide");
			System.exit(4);	
		}
		for(int j=1;j<nb_i-1;j++) {
			if((it.getInode(j).getFirst_byte())-(it.getInode(j-1).getSize())!=(it.getInode(j-1).getFirst_byte())) {
				System.out.println("problème de fragmentation");
				System.exit(5);
			}
		}
		
			

	}
	
	public static void main(String[] args) {
		Super_block sb= new Super_block();
		try {
			DataInputStream reader = new DataInputStream(new BufferedInputStream(new FileInputStream(args[1])));
			DataOutputStream writer = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(args[1])));
			sb.set_super_block(reader);
			verification(reader,sb);
			reader.close();
		}	
		catch( Exception e) {
			
			System.out.println("Erreur ouverture fichier");
			System.exit(2);
			
		}
	}

}
