/**
 * 
 */
package utils;
import analyseFichier.*;
import java.io.*;

/**
 * @author xenoswifts
 *
 */
public class Inode {

	private String name;
	private int size;
	private int uid;
	private int uright;
	private int oright;
	private String ctime;
	private String mtime;
	private int nblock;
	private int first_byte;
	
	
	
	public void set_Inode(RandomAccessFile i) {
		try {
			byte[] tab=new byte[32];
			byte[] tab2=new byte[28];
			i.read(tab,0,32);
			this.name=AnalyseFichier.inverserByte(tab);
			this.size=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			this.uid=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			this.uright=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			this.oright=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			i.read(tab2,0,28);
			this.ctime=AnalyseFichier.inverserByte(tab2);
			i.read(tab2,0,28);
			this.mtime=AnalyseFichier.inverserByte(tab2);
			this.nblock=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			this.first_byte=AnalyseFichier.BigEndianToLittleEndianint(i.readInt());
			
			
		}catch(IOException e) {
			System.out.println("Erreur de lecture d'une inode");
			System.exit(1);
		}
	}
	
	
	public void write_Inode(RandomAccessFile i) {
		try {
			i.writeBytes(name);
			i.writeInt(AnalyseFichier.BigEndianToLittleEndianint(size));
			i.writeInt(AnalyseFichier.BigEndianToLittleEndianint(uid));
			i.writeInt(AnalyseFichier.BigEndianToLittleEndianint(uright));
			i.writeInt(AnalyseFichier.BigEndianToLittleEndianint(oright));
			i.writeBytes(ctime);
			i.writeBytes(mtime);
			i.writeInt(AnalyseFichier.BigEndianToLittleEndianint(nblock));
			i.writeInt(AnalyseFichier.BigEndianToLittleEndianint(first_byte));
			
		}catch(IOException e) {
			System.out.println("Erreur d'écriture d'une inode");
			System.exit(2);
		}
	}

	
	public void printInode() {
		System.out.print("\n"+name+"\n"+size+"\n"+uid+"\n"+uright+"\n"+oright+
				"\n"+nblock+"\n"+first_byte);
	}


	public String getName() {
		return name;
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
