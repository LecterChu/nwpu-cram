import java.io.Serializable;
import java.util.Date;

/**
 * TODOList类
 * @author 楚逸飞
 * @see java.io.Serializable
 *
 */
public class TODOList implements Serializable{

    private int ID;//待办事项ID，主键
    private String username;//待办事项用户名
    private String tag;//待办事项标签
    /**
     * 时间格式("yyyy-MM-dd-HH:mm")
     */
    private Date start;//待办事项开始时间
    private Date end;//待办事项结束时间

    public TODOList(int ID, String username, String tag, Date start, Date end) {
        super();
        this.ID = ID;
        this.username = username;
        this.tag = tag;
        this.start = start;
        this.end = end;
    }

    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getTag() {
        return tag;
    }

    public void setTag(String tag) {
        this.tag = tag;
    }

    public Date getStart() {
        return start;
    }

    public void setStart(Date start) {
        this.start = start;
    }

    public Date getEnd() {
        return end;
    }

    public void setEnd(Date end) {
        this.end = end;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof TODOList)) return false;

        TODOList todoList = (TODOList) o;

        if (getID() != todoList.getID()) return false;
        if (getUsername() != null ? !getUsername().equals(todoList.getUsername()) : todoList.getUsername() != null)
            return false;
        if (getTag() != null ? !getTag().equals(todoList.getTag()) : todoList.getTag() != null) return false;
        if (getStart() != null ? !getStart().equals(todoList.getStart()) : todoList.getStart() != null) return false;
        return getEnd() != null ? getEnd().equals(todoList.getEnd()) : todoList.getEnd() == null;
    }
}
