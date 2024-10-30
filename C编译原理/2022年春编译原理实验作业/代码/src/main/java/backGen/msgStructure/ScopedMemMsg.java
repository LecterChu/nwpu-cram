package backGen.msgStructure;

import java.util.ArrayList;

/**
 * 外来引用的成员信息体
 *
 * @author suyuzhang
 * @version 1.0
 */
public class ScopedMemMsg {
    String name;
    String type;
    ArrayList<MemMsg> members;

    public ScopedMemMsg() {

    }

    public ScopedMemMsg(String name, String type,ArrayList<MemMsg> members) {
        this.name = name;
        this.type = type;
        this.members = members;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setMembers(ArrayList<MemMsg> members) {
        this.members = members;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }

    public ArrayList<MemMsg> getMembers() {
        return members;
    }
}
