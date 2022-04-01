/**
 * 
 */
package analyseFichier;

/**
 * @author xenoswifts
 *
 */
public class Inode {

	private String[] filename = new String[32];
	private int size;
	private int uid;
	private int uright;
	private int oright;
	private String[] ctimestamp = new String[26];
	private String[] mtimestamp = new String[26];
	private int nblock;
	private int first_byte;
	/**
	 * @return the filename
	 */
	public String[] getFilename() {
		return filename;
	}
	/**
	 * @param filename the filename to set
	 */
	public void setFilename(String[] filename) {
		this.filename = filename;
	}
	/**
	 * @return the size
	 */
	public int getSize() {
		return size;
	}
	/**
	 * @param size the size to set
	 */
	public void setSize(int size) {
		this.size = size;
	}
	/**
	 * @return the uid
	 */
	public int getUid() {
		return uid;
	}
	/**
	 * @param uid the uid to set
	 */
	public void setUid(int uid) {
		this.uid = uid;
	}
	/**
	 * @return the uright
	 */
	public int getUright() {
		return uright;
	}
	/**
	 * @param uright the uright to set
	 */
	public void setUright(int uright) {
		this.uright = uright;
	}
	/**
	 * @return the oright
	 */
	public int getOright() {
		return oright;
	}
	/**
	 * @param oright the oright to set
	 */
	public void setOright(int oright) {
		this.oright = oright;
	}
	/**
	 * @return the ctimestamp
	 */
	public String[] getCtimestamp() {
		return ctimestamp;
	}
	/**
	 * @param ctimestamp the ctimestamp to set
	 */
	public void setCtimestamp(String[] ctimestamp) {
		this.ctimestamp = ctimestamp;
	}
	/**
	 * @return the mtimestamp
	 */
	public String[] getMtimestamp() {
		return mtimestamp;
	}
	/**
	 * @param mtimestamp the mtimestamp to set
	 */
	public void setMtimestamp(String[] mtimestamp) {
		this.mtimestamp = mtimestamp;
	}
	/**
	 * @return the nblock
	 */
	public int getNblock() {
		return nblock;
	}
	/**
	 * @param nblock the nblock to set
	 */
	public void setNblock(int nblock) {
		this.nblock = nblock;
	}
	/**
	 * @return the first_byte
	 */
	public int getFirst_byte() {
		return first_byte;
	}
	/**
	 * @param first_byte the first_byte to set
	 */
	public void setFirst_byte(int first_byte) {
		this.first_byte = first_byte;
	}

	
	
	

}
