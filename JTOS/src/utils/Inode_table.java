package utils;

/**
 * @author xenoswifts
 *
 */
public class Inode_table {
	private int nb_inode;
	private Inode[] table_inode;
	
	public Inode_table() {
		this.nb_inode=10;
		table_inode= new Inode[10];
		for(int i=0;i<10;i++) {
			table_inode[i]=new Inode();
		}
	}
	
	
	public Inode getInode(int inode) {
		if(inode<nb_inode) {
			return table_inode[inode];
		}
		return table_inode[0];
		
	}
	
	/*public Inode getInodepasswd(int nb_i) {
		for(int i=0;i<nb_i;i++) {
			System.out.println("bite = "+table_inode[i].getName()+"\n"+table_inode[i].getName().length());
			if("passwd".compareTo(table_inode[i].getName())==0) {
				return table_inode[i];
			}
		}
		return null;
	}*/
	
	/**
	 * @return the nb_inode
	 */
	public int getNb_inode() {
		return nb_inode;
	}
	
	
	
	
	
	
}
