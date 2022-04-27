/**
 * 
 */
package analyseFichier;
import java.io.*;

/**
 * @author xenoswifts
 *
 */
public class Super_block {

	private int nb_fichier;
	private int nb_user;
	private int nb_block_disk;
	private int first_free_byte;
	
	
	
	public void set_super_block(DataInputStream i){
		try {
			
			this.nb_fichier=i.readInt();
			this.nb_user=i.readInt();
			this.nb_block_disk=i.readInt();
			this.first_free_byte=i.readInt();
			
		}catch(IOException e) {
			System.out.println("Erreur de lecture du super bloc");
			System.exit(3);
		}
		
	}



	/**
	 * @return the nb_fichier
	 */
	public int getNb_fichier() {
		return nb_fichier;
	}



	/**
	 * @return the nb_user
	 */
	public int getNb_user() {
		return nb_user;
	}



	/**
	 * @return the nb_block_disk
	 */
	public int getNb_block_disk() {
		return nb_block_disk;
	}



	/**
	 * @return the first_free_byte
	 */
	public int getFirst_free_byte() {
		return first_free_byte;
	}
	
	
	

}
