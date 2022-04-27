/**
 * 
 */
package utils;

/**
 * @author xenoswifts
 *
 */
public class User_table {
	private int nb_user_max;
	private int nb_user=0;
	private int[] user_table;
	
	/**
	 * @return the nb_user
	 */
	public int getNb_user() {
		return nb_user;
	}


	public User_table(int nb_user) {
		this.nb_user_max=nb_user;
		user_table=new int[nb_user];
	}
	
	
	public boolean IsInTable(int id) {
		for(int i=0;i<this.nb_user;i++) {
			if(id==user_table[i]) {
				return true;
			}
		}
		return false;
	}
	
	
	public void Insert_new_user(int id) {
		if(nb_user<nb_user_max) {
			user_table[nb_user++]=id;
		}
	}

}
