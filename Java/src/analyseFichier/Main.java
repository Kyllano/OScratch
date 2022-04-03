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
	/**
	 * @param args
	 * 
	 */
	
	
	public static void main(String[] args) {
		/*File file=new File("d0");*/
		Super_block sb= new Super_block();
		try {
			DataInputStream lecteur = new DataInputStream(new BufferedInputStream(new FileInputStream(args[1])));
			DataOutputStream writer = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(args[1])));
			
			try {
				
				sb.set_super_block(lecteur);
				
			
				
			}
			catch(Exception e){
				System.out.println("Erreur de lecture disque");
			}
			lecteur.close();
		}	
		catch( Exception e) {
			
			System.out.println("Erreur ouverture fichier");
			
		}
	}

}
