package backGen.msgStructure;

import java.util.ArrayList;

/**
 * 总struct结构信息
 *
 * @author suyuzhang
 * @version 1.0
 */
public class StructMsg {
    //此处name揉合了module的信息
    String name;
    ArrayList<MemMsg> members;
    ArrayList<ScopedMemMsg> scopeMembers;
    boolean hasScoped;

    public StructMsg(String name, ArrayList<MemMsg> members, ArrayList<ScopedMemMsg> scopeMembers, boolean hasScoped) {
        this.name = name;
        this.members = members;
        this.scopeMembers = scopeMembers;
        this.hasScoped = hasScoped;
    }

    public StructMsg() {
        scopeMembers=null;
        members=null;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setMembers(ArrayList<MemMsg> members) {
        this.members = members;
    }

    public void setScopeMembers(ArrayList<ScopedMemMsg> scopeMembers) {
        this.scopeMembers = scopeMembers;
    }

    public void setHasScoped(boolean hasScoped) {
        this.hasScoped = hasScoped;
    }

    public String getName() {
        return name;
    }

    public ArrayList<MemMsg> getMembers() {
        return members;
    }

    public ArrayList<ScopedMemMsg> getScopeMembers() {
        return scopeMembers;
    }

    public boolean isHasScoped() {
        return hasScoped;
    }
}
