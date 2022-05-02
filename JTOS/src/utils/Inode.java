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
	
	
	
	public String set_Inode(RandomAccessFile i) {
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
			return "tout est ok!";
			
			
		}catch(IOException e) {
			return "Erreur de lecture du catalogue";
		}
	}
	
	
	public String write_Inode(RandomAccessFile i) {
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
			return "tout est ok!";
			
		}catch(IOException e) {
			return "Erreur d'écriture du catalogue";
		}
	}

	
	public void printInode() {
		System.out.print("\n"+name+"\n"+size+"\n"+uid+"\n"+uright+"\n"+oright+
				"\n"+nblock+"\n"+first_byte);
	}


	public String getName() {
		return name;
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

	public int getNblock() {
		return nblock;
	}

	public int getFirst_byte() {
		return first_byte;
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

	public void setNblock(int nblock) {
		this.nblock = nblock;
	}

	public void setFirst_byte(int first_byte) {
		this.first_byte = first_byte;
	}
}
