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

	public static final int TIMESTAMP_SIZE = 26;
	private byte[] filename = new byte[32];
	private int size;
	private int uid;
	private int uright;
	private int oright;
	private byte[] ctimestamp = new byte[26];
	private byte[] mtimestamp = new byte[26];
	private int nblock;
	private int first_byte;
	
	public int set_Inode(DataInputStream i) {
		try {
			
			this.filename = i.readNBytes(32);
			this.size = i.readInt();
			this.uid = i.readInt();
			this.uright = i.readInt();
			this.oright = i.readInt();
			this.ctimestamp = i.readNBytes(TIMESTAMP_SIZE);
			this.mtimestamp = i.readNBytes(32);
			this.nblock = i.readInt();
			this.first_byte = i.readInt();
			return 0;
		}
		catch (IOException e) {
			System.out.println("Erreur de lecture du super bloc");
			return 1;
		}
	}
	
	public boolean isEmpty(){
		if (this.nblock != 0) return true;
		return false;
	}

	public byte[] getFilename() {
		return filename;
	}

	public int getSize() {
		return size;
	}

	public int getUid() {
		return uid;
	}

	public int getUright() {
		return uright;
	}

	public int getOright() {
		return oright;
	}

	public byte[] getCtimestamp() {
		return ctimestamp;
	}

	public byte[] getMtimestamp() {
		return mtimestamp;
	}

	public int getNblock() {
		return nblock;
	}

	public int getFirst_byte() {
		return first_byte;
	}


	public void setFilename(byte[] filename) {
		this.filename = filename;
	}

	public void setSize(int size) {
		this.size = size;
	}

	public void setUid(int uid) {
		this.uid = uid;
	}

	public void setUright(int uright) {
		this.uright = uright;
	}

	public void setOright(int oright) {
		this.oright = oright;
	}

	public void setCtimestamp(byte[] ctimestamp) {
		this.ctimestamp = ctimestamp;
	}

	public void setMtimestamp(byte[] mtimestamp) {
		this.mtimestamp = mtimestamp;
	}

	public void setNblock(int nblock) {
		this.nblock = nblock;
	}

	public void setFirst_byte(int first_byte) {
		this.first_byte = first_byte;
	}
}
