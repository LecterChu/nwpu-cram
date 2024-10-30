package symtab;

import java.util.ArrayList;

/**
 * 符号表中的元素链
 *
 * @author suyuzhang
 * @version 1.0
 */
public class SymbolList {
    public SymbolNode head; // 元素链的头节点

    /**
     * 列表初始化
     */
    public SymbolList()
    {
        head = new SymbolNode();
    }

    /**
     * 在元素链的头部插入一个新的节点。该方法将给定的节点 sn 设置为头节点的下一个节点，然后将头节点的下一个节点设置为新的节点 sn。
     *
     * @param sn sn
     */
    public void insertNode(SymbolNode sn)
    {
        sn.setNext(head.getNext());
        head.setNext(sn);
    }

    public SymbolNode getHead()
    {
        return head;
    }

    /**
     * tofind中非null的值进行匹配
     *
     * @param toFind 找到
     * @return {@link SymbolNode}
     */
    public SymbolNode findNode(SymbolNode toFind)
    {
        SymbolNode tp = head;
        while((tp=tp.getNext())!=null){
            //tp = tp.getNext();
            if(toFind.getName()!=null && !(toFind.getName().equals(tp.getName()))){
                continue;
            }
            if(toFind.getModuleName()!=null && !(toFind.getModuleName().equals(tp.getModuleName()))){
                continue;
            }
            if(toFind.getStructName()!=null && !(toFind.getStructName().equals(tp.getStructName()))){
                continue;
            }
            if(toFind.getType()!=null && !(toFind.getType().equals(tp.getType()))){
                continue;
            }
            if(toFind.getVal()!=null && !(toFind.getVal().equals(tp.getVal()))){
                continue;
            }
            break;
        }
        return tp;
    }

    /**
     * tofind中非null的值进行匹配所有的
     *
     * @param toFind 找到
     * @return {@link ArrayList}<{@link SymbolNode}>
     */
    public ArrayList<SymbolNode> findNodes(SymbolNode toFind)
    {
        ArrayList<SymbolNode> ans = new ArrayList<SymbolNode>();

        SymbolNode tp = head;
        while((tp=tp.getNext())!=null){
            //tp = tp.getNext();
            if(toFind.getName()!=null && !(toFind.getName().equals(tp.getName()))){
                continue;
            }
            if(toFind.getModuleName()!=null && !(toFind.getModuleName().equals(tp.getModuleName()))){
                continue;
            }
            if(toFind.getStructName()!=null && !(toFind.getStructName().equals(tp.getStructName()))){
                continue;
            }
            if(toFind.getType()!=null && !(toFind.getType().equals(tp.getType()))){
                continue;
            }
            if(toFind.getVal()!=null && !(toFind.getVal().equals(tp.getVal()))){
                continue;
            }
            ans.add(tp);
        }
        return ans;
    }


    /**
     * 字符串
     *
     * @return {@link String}
     */
    @Override
    public String toString()
    {
        SymbolNode tp = head.getNext();
        String nodes="";
        while(tp!=null){
            nodes += tp.toString()+"\n";
            tp = tp.getNext();
        }
        return nodes;
    }

}
