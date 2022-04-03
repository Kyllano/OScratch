/**
 * 
 */
package analyseFichier;

import java.io.DataInputStream;
import java.io.IOException;

/**
 * @author xenoswifts
 *
 */
public class Inode {

	private byte[] filename = new byte[32];
	private int size;
	private int uid;
	private int uright;
	private int oright;
	private byte[] ctimestamp = new byte[26];
	private byte[] mtimestamp = new byte[26];
	private int nblock;
	private int first_byte;
	
	
	
	public void set_Inode(DataInputStream i) {
		try {
			
			this.filename=i.readNBytes(32);
			this.size=i.readInt();
			this.uid=i.readInt();
			this.uright=i.readInt();
			this.oright=i.readInt();
			this.filename=i.readNBytes(32);
			this.filename=i.readNBytes(32);
			this.uright=i.readInt();
			this.oright=i.readInt();
			
			
		}catch(IOException e) {
			System.out.println("Erreur de lecture du super bloc");
			System.exit(1);
		}
	}



	/**
	 * @return the filename
	 */
	public byte[] getFilename() {
		return filename;
	}



	/**
	 * @return the size
	 */
	public int getSize() {
		return size;
	}



	/**
	 * @return the uid
	 */
	public int getUid() {
		return uid;
	}



	/**
	 * @return the uright
	 */
	public int getUright() {
		return uright;
	}



	/**
	 * @return the oright
	 */
	public int getOright() {
		return oright;
	}



	/**
	 * @return the ctimestamp
	 */
	public byte[] getCtimestamp() {
		return ctimestamp;
	}



	/**
	 * @return the mtimestamp
	 */
	public byte[] getMtimestamp() {
		return mtimestamp;
	}



	/**
	 * @return the nblock
	 */
	public int getNblock() {
		return nblock;
	}



	/**
	 * @return the first_byte
	 */
	public int getFirst_byte() {
		return first_byte;
	}



	/**
	 * @param filename the filename to set
	 */
	public void setFilename(byte[] filename) {
		this.filename = filename;
	}



	/**
	 * @param size the size to set
	 */
	public void setSize(int size) {
		this.size = size;
	}



	/**
	 * @param uid the uid to set
	 */
	public void setUid(int uid) {
		this.uid = uid;
	}



	/**
	 * @param uright the uright to set
	 */
	public void setUright(int uright) {
		this.uright = uright;
	}



	/**
	 * @param oright the oright to set
	 */
	public void setOright(int oright) {
		this.oright = oright;
	}



	/**
	 * @param ctimestamp the ctimestamp to set
	 */
	public void setCtimestamp(byte[] ctimestamp) {
		this.ctimestamp = ctimestamp;
	}



	/**
	 * @param mtimestamp the mtimestamp to set
	 */
	public void setMtimestamp(byte[] mtimestamp) {
		this.mtimestamp = mtimestamp;
	}



	/**
	 * @param nblock the nblock to set
	 */
	public void setNblock(int nblock) {
		this.nblock = nblock;
	}



	/**
	 * @param first_byte the first_byte to set
	 */
	public void setFirst_byte(int first_byte) {
		this.first_byte = first_byte;
	}

	
	
	

}
