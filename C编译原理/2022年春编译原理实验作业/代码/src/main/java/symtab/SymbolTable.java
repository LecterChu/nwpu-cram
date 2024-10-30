package symtab;

import java.util.ArrayList;

/**
 * 符号表
 *
 * @author suyuzhang
 * @version 1.0
 */
public class SymbolTable {
    public static final int SIZE = 211; // 质数
    public static final int SHIFT = 4;
    public SymbolList[] symTable;

    /**
     * 输入字符串,输出哈希值
     *
     * @param key 关键
     * @return hashcode
     */
    public static int hash(String key) {
        int hashCode = 0;
        for (int i = 0; i < key.length(); i++) {
            hashCode = ((hashCode << SHIFT) + key.charAt(i)) % SIZE;
        }
        return hashCode;
    }

    public SymbolTable() {
        symTable = new SymbolList[SIZE];
    }

    /**
     * 属性信息插入符号表
     *
     * @param sn sn
     */
    public void insertST(SymbolNode sn) {
        int hashCode = hash(sn.getName());
        SymbolList sl = symTable[hashCode];

        //该位置还没链表
        if (sl == null) {
            sl = new SymbolList();
            sl.insertNode(sn);
        } else {
            sl.insertNode(sn);
        }
        symTable[hashCode] = sl;
    }

    /**
     * 检查命名冲突
     *
     * @param sn sn
     * @return {@link SymbolNode}
     */
    public SymbolNode lookupSt(SymbolNode sn) {
        int hashCode = hash(sn.getName());
        SymbolList sl = symTable[hashCode];
        if (sl == null) {
            return null;
        } else {
            return sl.findNode(sn);
        }
    }

    /**
     * 查找所有节点，检查未定义即使用的情况
     *
     * @param sn sn
     * @return {@link ArrayList}<{@link SymbolNode}>
     */
    public ArrayList<SymbolNode> lookupAll(SymbolNode sn) {
        ArrayList<SymbolNode> ans = new ArrayList<SymbolNode>();
        SymbolList sl;
        for (int i = 0; i < SIZE; i++) {
            ArrayList<SymbolNode> tp;
            sl = symTable[i];
            if (sl != null) {
                tp = sl.findNodes(sn);
                ans.addAll(tp);
            }
        }
        return ans;
    }

    @Override
    public String toString() {
        StringBuilder syms = new StringBuilder();
        for (int i = 0; i < SIZE; i++) {
            if (symTable[i] != null) {
                syms.append(symTable[i].toString()).append("\n");
            }
        }
        return syms.toString();
    }

}
