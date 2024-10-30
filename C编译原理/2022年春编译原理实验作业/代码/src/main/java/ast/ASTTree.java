package ast;

import gen.MIDLBaseVisitor;
import gen.MIDLParser;

import java.util.Objects;

/**
 * 格式化输出AST
 *
 * @author suyuzhang
 * @version 1.0
 */
public class ASTTree extends MIDLBaseVisitor<String> {
    public String astParseTree = ""; //存储抽象语法树
    public int level = 0; //记录层数，便于缩进

    /**
     * 缩进方法
     *
     * @param level 层数
     */
    private void tab(int level) {
        for (int i = 0; i < level * 4; i++) {
            astParseTree += " ";
        }
    }

    /**
     * specification -> definition { definition }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitSpecification(MIDLParser.SpecificationContext ctx) {
        astParseTree += "specification(\n";
        level++;
        tab(level);

        for (int i = 0; i < ctx.getChildCount(); i++) {
            visit(ctx.getChild(i));
        }
        level--;
        astParseTree += ")\n";
        tab(level);
        return null;
    }

    /**
     * definition -> type_decl“;”| module “;”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitDefinition(MIDLParser.DefinitionContext ctx) {
        astParseTree += "definition(\n";
        level++;
        tab(level);
        visit(ctx.getChild(0));
        level--;
        astParseTree += ")\n";
        tab(level);
        return null;
    }

    /**
     * module -> “module”ID “{” definition { definition } “}”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitModule(MIDLParser.ModuleContext ctx) {
        astParseTree += "module( \n";
        level++;
        tab(level);
        astParseTree += "ID:" + ctx.getChild(1).getText();
        for (int i = 3; i < ctx.getChildCount() - 1; i++) {
            astParseTree += "\n";
//            tab(level);
            tab(level);
            visit(ctx.getChild(i));
//            level --;
        }
        level--;
        astParseTree += " ) \n";
        tab(level);
        return null;
    }

    /**
     * type_decl -> struct_type | “struct” ID
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitType_decl(MIDLParser.Type_declContext ctx) {
        if (ctx.getChildCount() == 1) {
//            astParseTree += "\n";
//            level++;
//            tab(level);
            visit(ctx.getChild(0));
//            level --;
        } else {
            astParseTree += "struct( \n";
            level++;
            tab(level);
            astParseTree += "ID:" + ctx.ID().getText();
            level--;
            astParseTree += " )\n";
            tab(level);

        }
        return null;
    }

    /**
     * struct_type->“struct” ID “{”   member_list “}”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitStruct_type(MIDLParser.Struct_typeContext ctx) {
        astParseTree += "struct( \n";
        level++;
        tab(level);
        astParseTree += "ID:" + ctx.getChild(1).getText() + "\n";
        tab(level);
        visit(ctx.getChild(3));
        level--;
        astParseTree += " ) \n";
        tab(level);
        return null;
    }

    /**
     * member_list{ type_spec declarators “;” }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitMember_list(MIDLParser.Member_listContext ctx) {
        int n = ctx.getChildCount();
        if (n == 0) {
            return null;
        } else {
            for (int i = 0; i < n / 3; i++) {
                astParseTree += "member( \n";
                level++;
                tab(level);
                visit(ctx.getChild(3 * i));
                visit(ctx.getChild(3 * i + 1));
                level--;
                astParseTree += ")\n";
                tab(level);
            }
        }
        return null;
    }

    /**
     * type_spec -> scoped_name | base_type_spec | struct_type
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitType_spec(MIDLParser.Type_specContext ctx) {
        visit(ctx.getChild(0));
        return null;
    }

    /**
     * scoped_name -> [“::”] ID {“::” ID }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitScoped_name(MIDLParser.Scoped_nameContext ctx) {
        astParseTree += "namespace( \n";
        level++;
        tab(level);
        int i;
        if (Objects.equals(ctx.getChild(0).getText(), "::")) {
            i = 1;
        } else {
            i = 0;
        }
        for (; i < ctx.getChildCount(); i += 2) {
            astParseTree += ctx.getChild(i).getText() + "\n";
            tab(level);
        }
        level--;
        astParseTree += " ) \n";
        tab(level);

        return null;
    }

    /**
     * base_type_spec->floating_pt_type|integer_type|“char”|“string”|“boolean”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitBase_type_spec(MIDLParser.Base_type_specContext ctx) {
        //终结符
        if (ctx.getChild(0).getChildCount() == 0) {
            astParseTree += ctx.getChild(0).getText() + "\n";
            tab(level);
        } else {
            visit(ctx.getChild(0));
        }
        return null;
    }

    /**
     * floating_pt_type -> “float” | “double” | “long double”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitFloating_pt_type(MIDLParser.Floating_pt_typeContext ctx) {
        astParseTree += ctx.getChild(0).getText() + "\n";
        tab(level);
        return null;
    }

    /**
     * integer_type -> signed_int | unsigned_int
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitInteger_type(MIDLParser.Integer_typeContext ctx) {
        visit(ctx.getChild(0));
        return null;
    }

    /**
     * signed_int->(“short”|“int16”)|(“long”|“int32”)|(“long long”|“int64”)|“int8”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitSigned_int(MIDLParser.Signed_intContext ctx) {
        astParseTree += ctx.getChild(0).getText() + "\n";
        tab(level);
        return null;
    }

    /**
     * 访问无符号整型
     * unsigned_int -> (“unsigned short”| “uint16”) | (“unsigned long”| “uint32”) | (“unsigned long long” | “uint64”) | “uint8”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitUnsigned_int(MIDLParser.Unsigned_intContext ctx) {

        astParseTree += ctx.getChild(0).getText() + "\n";
        tab(level);
        return null;
    }

    /**
     * declarators -> declarator {“,” declarator }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitDeclarators(MIDLParser.DeclaratorsContext ctx) {
        int n = ctx.getChildCount();
        for (int i = 0; i < n; i++) {
            if (ctx.getChild(i).getChildCount() != 0)
                visit(ctx.getChild(i));
        }
        return null;
    }

    /**
     * declarator -> simple_declarator | array_declarator
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitDeclarator(MIDLParser.DeclaratorContext ctx) {
        visit(ctx.getChild(0));
        return null;
    }

    /**
     * simple_declarator -> ID [“=” or_expr]
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitSimple_declarator(MIDLParser.Simple_declaratorContext ctx) {
        if (ctx.getChildCount() != 1) {
            astParseTree += "=( \n";
            level++;
            tab(level);
            astParseTree += "ID:" + ctx.getChild(0).getText() + "\n";
            tab(level);
            visit(ctx.or_expr());
            level--;
            astParseTree += " ) \n";
            tab(level);
        } else {
            astParseTree += "ID:" + ctx.getChild(0).getText() + "\n";
            tab(level);
        }

        return null;
    }

    /**
     * array_declarator -> ID “[” or_expr “]” [“=” exp_list ]
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitArray_declarator(MIDLParser.Array_declaratorContext ctx) {
        astParseTree += "array( \n";
        level++;
        tab(level);
        astParseTree += "ID:" + ctx.getChild(0).getText() + "\n";
        tab(level);
        visit(ctx.getChild(2));
        if (ctx.getChildCount() != 4) {
            visit(ctx.exp_list());
        }
        astParseTree += " ) \n";
        level--;
        tab(level);
        return null;
    }

    /**
     * exp_list -> “[” or_expr { “,”or_expr } “]”
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitExp_list(MIDLParser.Exp_listContext ctx) {
        astParseTree += "arrayValues( \n";
        level++;
        tab(level);
        int n = ctx.getChildCount();
        for (int i = 0; i < n; i++) {
            if (ctx.getChild(i).getChildCount() > 0)
                visit(ctx.getChild(i));
        }
        level--;
        astParseTree += " ) \n";
        tab(level);
        return null;
    }

    /**
     * or_expr -> xor_expr {“|” xor_expr }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitOr_expr(MIDLParser.Or_exprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            for (int i = 1; i < n; i += 2) {
                astParseTree += "|( \n";
                level++;
                tab(level);
                visit(ctx.getChild(i - 1));
                if (i == n - 2)
                    visit(ctx.getChild(i + 1));
            }
            for (int i = 1; i < n; i += 2) {
                level--;
                astParseTree += " ) \n";
                tab(level);
            }
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * xor_expr -> and_expr {“^” and_expr }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitXor_expr(MIDLParser.Xor_exprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            for (int i = 1; i < n; i += 2) {
                astParseTree += "^( \n";
                level++;
                tab(level);
                visit(ctx.getChild(i - 1));
                if (i == n - 2)
                    visit(ctx.getChild(i + 1));
            }
            for (int i = 1; i < n; i += 2) {
                level--;
                astParseTree += " ) \n";
                tab(level);
            }
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * and_expr -> shift_expr {“&”shift_expr }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitAnd_expr(MIDLParser.And_exprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            for (int i = 1; i < n; i += 2) {
                astParseTree += "&( \n";
                level++;
                tab(level);
                visit(ctx.getChild(i - 1));
                if (i == n - 2)
                    visit(ctx.getChild(i + 1));
            }
            for (int i = 1; i < n; i += 2) {
                level--;
                astParseTree += " ) \n";
                tab(level);
            }
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * shift_expr -> add_expr { (“>>” | “<<”) add_expr }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitShift_expr(MIDLParser.Shift_exprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            for (int i = 1; i < n; i += 2) {
                //>>或<<
                astParseTree += ctx.getChild(i).getText() + "( \n";
                level++;
                tab(level);
                visit(ctx.getChild(i - 1));
                if (i == n - 2)
                    visit(ctx.getChild(i + 1));
            }
            for (int i = 1; i < n; i += 2) {
                level--;
                astParseTree += " ) \n";
                tab(level);
            }
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * add_expr -> multi_expr {(“+” | “-”)  mult_expr }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitAdd_expr(MIDLParser.Add_exprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            for (int i = 1; i < n; i += 2) {
                astParseTree += ctx.getChild(i).getText() + "( \n";
                level++;
                tab(level);
                visit(ctx.getChild(i - 1));
                if (i == n - 2)
                    visit(ctx.getChild(i + 1));
            }
            for (int i = 1; i < n; i += 2) {
                level--;
                astParseTree += " ) \n";
                tab(level);
            }
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * mult_expr -> unary_expr { (“*” |“/”|“%”) unary_expr }
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitMult_expr(MIDLParser.Mult_exprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            for (int i = 1; i < n; i += 2) {
                astParseTree += ctx.getChild(i).getText() + "( \n";
                level++;
                tab(level);
                visit(ctx.getChild(i - 1));
                if (i == n - 2)
                    visit(ctx.getChild(i + 1));
            }
            for (int i = 1; i < n; i += 2) {
                level--;
                astParseTree += " ) \n";
                tab(level);
            }
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * unary_expr -> [“-”| “+” | “~”] literal
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitUnary_expr(MIDLParser.Unary_exprContext ctx) {

        if (ctx.getChildCount() != 1) {
            astParseTree += ctx.getChild(0).getText() + "( \n";
            level++;
            tab(level);
        }
        visit(ctx.literal());
        if (ctx.getChildCount() != 1) {
            level--;
            astParseTree += " ) \n";
            tab(level);
        }
        return null;
    }

    /**
     * literal -> INTEGER | FLOATING_PT | CHAR | STRING | BOOLEAN
     *
     * @param ctx ctx
     * @return {@link String}
     */
    @Override
    public String visitLiteral(MIDLParser.LiteralContext ctx) {
        astParseTree += ctx.getChild(0) + "\n";
        tab(level);
        return null;
    }

}
