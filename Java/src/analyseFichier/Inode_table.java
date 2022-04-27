/**
 * 
 */
package analyseFichier;

/**
 * @author xenoswifts
 *
 */
public class Inode_table {
	private int nb_inode;
	private Inode[] table_inode;
	
	public Inode_table(int nb_fichier) {
		this.nb_inode=nb_fichier;
		table_inode= new Inode[10];
		for(int i=0;i<nb_inode;i++) {
			table_inode[i]=new Inode();
		}
	}
	
	
	public Inode getInode(int inode) {
		if(inode>=nb_inode) {
			return table_inode[nb_inode-1];
		}
		return table_inode[inode];
		
	}
	/**
	 * @return the nb_inode
	 */
	public int getNb_inode() {
		return nb_inode;
	}
	
	
	
	
	
	
}
