    package java.io;  
     
    public class DataInputStream extends FilterInputStream implements DataInput {  
     
        // 构造函数。  
        public DataInputStream(InputStream in) {  
            super(in);  
        }  
     
        private byte bytearr[] = new byte[80];  
        private char chararr[] = new char[80];  
     
        // 从“数据输入流”中读取一个字节  
        public final int read(byte b[]) throws IOException {  
            return in.read(b, 0, b.length);  
        }  
     
        // 从“数据输入流”中读取数据并存储到字节数组b中。  
        // off是字节数组b中开始存储元素的起始位置。  
        // len是读取字节的个数。  
        public final int read(byte b[], int off, int len) throws IOException {  
            return in.read(b, off, len);  
        }  
     
        // 从“数据输入流”中读取数据并填满字节数组b中；没有填满数组b则一直读取，直到填满位置。  
        // 从字节数组b的位置0开始存储，并且读取的字节个数等于b的长度。  
        public final void readFully(byte b[]) throws IOException {  
            readFully(b, 0, b.length);  
        }  
     
        // 从“数据输入流”中读取数据并存储到字节数组b中；若没读取len个字节，直到一直读取直到读取完len个字节为止。  
        public final void readFully(byte b[], int off, int len) throws IOException {  
            if (len < 0)  
                throw new IndexOutOfBoundsException();  
            int n = 0;  
            while (n < len) {  
                int count = in.read(b, off + n, len - n);  
                if (count < 0)  
                    throw new EOFException();  
                n += count;  
            }  
        }  
     
        // 跳过n个字节  
        public final int skipBytes(int n) throws IOException {  
            int total = 0;  
            int cur = 0;  
     
            while ((total<n) && ((cur = (int) in.skip(n-total)) > 0)) {  
                total += cur;  
            }  
     
            return total;  
        }  
     
        // 从“数据输入流”中读取boolean类型的值  
        public final boolean readBoolean() throws IOException {  
            int ch = in.read();  
            if (ch < 0)  
                throw new EOFException();  
            return (ch != 0);  
        }  
     
        // 从“数据输入流”中读取Byte类型的值  
        public final byte readByte() throws IOException {  
            int ch = in.read();  
            if (ch < 0)  
                throw new EOFException();  
            return (byte)(ch);  
        }  
     
        // 从“数据输入流”中读取“无符号的Byte类型”的值，即读取值为正数的byte值  
        public final int readUnsignedByte() throws IOException {  
            int ch = in.read();  
            if (ch < 0)  
                throw new EOFException();  
            return ch;  
        }  
     
        // 从“数据输入流”中读取“short类型”的值  
        public final short readShort() throws IOException {  
            int ch1 = in.read();  
            int ch2 = in.read();  
            if ((ch1 | ch2) < 0)  
                throw new EOFException();  
            return (short)((ch1 << 8) + (ch2 << 0));  
        }  
     
        // 从“数据输入流”中读取“无符号的short类型”的值  
        public final int readUnsignedShort() throws IOException {  
            int ch1 = in.read();  
            int ch2 = in.read();  
            if ((ch1 | ch2) < 0)  
                throw new EOFException();  
            return (ch1 << 8) + (ch2 << 0);  
        }  
     
        // 从“数据输入流”中读取“char类型”的值  
        public final char readChar() throws IOException {  
            int ch1 = in.read();  
            int ch2 = in.read();  
            if ((ch1 | ch2) < 0)  
                throw new EOFException();  
            return (char)((ch1 << 8) + (ch2 << 0));  
        }  
     
        // 从“数据输入流”中读取“int类型”的值  
        public final int readInt() throws IOException {  
            int ch1 = in.read();  
            int ch2 = in.read();  
            int ch3 = in.read();  
            int ch4 = in.read();  
            if ((ch1 | ch2 | ch3 | ch4) < 0)  
                throw new EOFException();  
            return ((ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0));  
        }  
     
        private byte readBuffer[] = new byte[8];  
     
        // 从“数据输入流”中读取“long类型”的值  
        public final long readLong() throws IOException {  
            readFully(readBuffer, 0, 8);  
            return (((long)readBuffer[0] << 56) +  
                    ((long)(readBuffer[1] & 255) << 48) +  
                    ((long)(readBuffer[2] & 255) << 40) +  
                    ((long)(readBuffer[3] & 255) << 32) +  
                    ((long)(readBuffer[4] & 255) << 24) +  
                    ((readBuffer[5] & 255) << 16) +  
                    ((readBuffer[6] & 255) <<  8) +  
                    ((readBuffer[7] & 255) <<  0));  
        }  
     
        // 从“数据输入流”中读取“float类型”的值  
        public final float readFloat() throws IOException {  
            return Float.intBitsToFloat(readInt());  
        }  
     
        // 从“数据输入流”中读取“double类型”的值  
        public final double readDouble() throws IOException {  
            return Double.longBitsToDouble(readLong());  
        }  
     
        private char lineBuffer[];  
     
        @Deprecated 
        public final String readLine() throws IOException {  
            char buf[] = lineBuffer;  
     
            if (buf == null) {  
                buf = lineBuffer = new char[128];  
            }  
     
            int room = buf.length;  
            int offset = 0;  
            int c;  
     
    loop:   while (true) {  
                switch (c = in.read()) {  
                  case -1:  
                  case '\n':  
                    break loop;  
     
                  case '\r':  
                    int c2 = in.read();  
                    if ((c2 != '\n') && (c2 != -1)) {  
                        if (!(in instanceof PushbackInputStream)) {  
                            this.in = new PushbackInputStream(in);  
                        }  
                        ((PushbackInputStream)in).unread(c2);  
                    }  
                    break loop;  
     
                  default:  
                    if (--room < 0) {  
                        buf = new char[offset + 128];  
                        room = buf.length - offset - 1;  
                        System.arraycopy(lineBuffer, 0, buf, 0, offset);  
                        lineBuffer = buf;  
                    }  
                    buf[offset++] = (char) c;  
                    break;  
                }  
            }  
            if ((c == -1) && (offset == 0)) {  
                return null;  
            }  
            return String.copyValueOf(buf, 0, offset);  
        }  
     
        // 从“数据输入流”中读取“UTF类型”的值  
        public final String readUTF() throws IOException {  
            return readUTF(this);  
        }  
     
        public final static String readUTF(DataInput in) throws IOException {  
            // 从“数据输入流”中读取“无符号的short类型”的值：  
            // 注意：UTF-8输入流的前2个字节是数据的长度  
            int utflen = in.readUnsignedShort();  
            byte[] bytearr = null;  
            char[] chararr = null;  
     
            // 如果in本身是“数据输入流”，  
            // 则，设置字节数组bytearr = "数据输入流"的成员bytearr  
            //     设置字符数组chararr = "数据输入流"的成员chararr  
            // 否则的话，新建数组bytearr和chararr  
            if (in instanceof DataInputStream) {  
                DataInputStream dis = (DataInputStream)in;  
                if (dis.bytearr.length < utflen){  
                    dis.bytearr = new byte[utflen*2];  
                    dis.chararr = new char[utflen*2];  
                }  
                chararr = dis.chararr;  
                bytearr = dis.bytearr;  
            } else {  
                bytearr = new byte[utflen];  
                chararr = new char[utflen];  
            }  
     
            int c, char2, char3;  
            int count = 0;  
            int chararr_count=0;  
     
            // 从“数据输入流”中读取数据并存储到字节数组bytearr中；从bytearr的位置0开始存储，存储长度为utflen。  
            // 注意，这里是存储到字节数组！而且读取的是全部的数据。  
            in.readFully(bytearr, 0, utflen);  
     
            // 将“字节数组bytearr”中的数据 拷贝到 “字符数组chararr”中  
            // 注意：这里相当于“预处理的输入流中单字节的符号”，因为UTF-8是1-4个字节可变的。  
            while (count < utflen) {  
                // 将每个字节转换成int值  
                c = (int) bytearr[count] & 0xff;  
                // UTF-8的单字节数据的值都不会超过127；所以，超过127，则退出。  
                if (c > 127) break;  
                count++;  
                // 将c保存到“字符数组chararr”中  
                chararr[chararr_count++]=(char)c;  
            }  
     
            // 处理完输入流中单字节的符号之后，接下来我们继续处理。  
            while (count < utflen) {  
                // 下面语句执行了2步操作。  
                // (01) 将字节由 “byte类型” 转换成 “int类型”。  
                //      例如， “11001010” 转换成int之后，是 “00000000 00000000 00000000 11001010”  
                // (02) 将 “int类型” 的数据左移4位  
                //      例如， “00000000 00000000 00000000 11001010” 左移4位之后，变成 “00000000 00000000 00000000 00001100”  
                c = (int) bytearr[count] & 0xff;  
                switch (c >> 4) {  
                    // 若 UTF-8 是单字节，即 bytearr[count] 对应是 “0xxxxxxx” 形式；  
                    // 则 bytearr[count] 对应的int类型的c的取值范围是 0-7。  
                    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:  
                        /* 0xxxxxxx*/ 
                        count++;  
                        chararr[chararr_count++]=(char)c;  
                        break;  
     
                    // 若 UTF-8 是双字节，即 bytearr[count] 对应是 “110xxxxx  10xxxxxx” 形式中的第一个，即“110xxxxx”  
                    // 则 bytearr[count] 对应的int类型的c的取值范围是 12-13。  
                    case 12: case 13:  
                        /* 110x xxxx   10xx xxxx*/ 
                        count += 2;  
                        if (count > utflen)  
                            throw new UTFDataFormatException(  
                                "malformed input: partial character at end");  
                        char2 = (int) bytearr[count-1];  
                        if ((char2 & 0xC0) != 0x80)  
                            throw new UTFDataFormatException(  
                                "malformed input around byte " + count);  
                        chararr[chararr_count++]=(char)(((c & 0x1F) << 6) |  
                                                        (char2 & 0x3F));  
                        break;  
     
                    // 若 UTF-8 是三字节，即 bytearr[count] 对应是 “1110xxxx  10xxxxxx  10xxxxxx” 形式中的第一个，即“1110xxxx”  
                    // 则 bytearr[count] 对应的int类型的c的取值是14 。  
                    case 14:  
                        /* 1110 xxxx  10xx xxxx  10xx xxxx */ 
                        count += 3;  
                        if (count > utflen)  
                            throw new UTFDataFormatException(  
                                "malformed input: partial character at end");  
                        char2 = (int) bytearr[count-2];  
                        char3 = (int) bytearr[count-1];  
                        if (((char2 & 0xC0) != 0x80) || ((char3 & 0xC0) != 0x80))  
                            throw new UTFDataFormatException(  
                                "malformed input around byte " + (count-1));  
                        chararr[chararr_count++]=(char)(((c     & 0x0F) << 12) |  
                                                        ((char2 & 0x3F) << 6)  |  
                                                        ((char3 & 0x3F) << 0));  
                        break;  
     
                    // 若 UTF-8 是四字节，即 bytearr[count] 对应是 “11110xxx 10xxxxxx  10xxxxxx  10xxxxxx” 形式中的第一个，即“11110xxx”  
                    // 则 bytearr[count] 对应的int类型的c的取值是15   
                    default:  
                        /* 10xx xxxx,  1111 xxxx */ 
                        throw new UTFDataFormatException(  
                            "malformed input around byte " + count);  
                }  
            }  
            // The number of chars produced may be less than utflen  
            return new String(chararr, 0, chararr_count);  
        }  
    } 