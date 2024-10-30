package gen;// Generated from C:/Users/admin/Desktop/lab1_maven/src/main/resources/MIDL.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link MIDLParser}.
 */
public interface MIDLListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link MIDLParser#specification}.
	 * @param ctx the parse tree
	 */
	void enterSpecification(MIDLParser.SpecificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#specification}.
	 * @param ctx the parse tree
	 */
	void exitSpecification(MIDLParser.SpecificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#definition}.
	 * @param ctx the parse tree
	 */
	void enterDefinition(MIDLParser.DefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#definition}.
	 * @param ctx the parse tree
	 */
	void exitDefinition(MIDLParser.DefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#module}.
	 * @param ctx the parse tree
	 */
	void enterModule(MIDLParser.ModuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#module}.
	 * @param ctx the parse tree
	 */
	void exitModule(MIDLParser.ModuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#type_decl}.
	 * @param ctx the parse tree
	 */
	void enterType_decl(MIDLParser.Type_declContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#type_decl}.
	 * @param ctx the parse tree
	 */
	void exitType_decl(MIDLParser.Type_declContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#struct_type}.
	 * @param ctx the parse tree
	 */
	void enterStruct_type(MIDLParser.Struct_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#struct_type}.
	 * @param ctx the parse tree
	 */
	void exitStruct_type(MIDLParser.Struct_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#member_list}.
	 * @param ctx the parse tree
	 */
	void enterMember_list(MIDLParser.Member_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#member_list}.
	 * @param ctx the parse tree
	 */
	void exitMember_list(MIDLParser.Member_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#type_spec}.
	 * @param ctx the parse tree
	 */
	void enterType_spec(MIDLParser.Type_specContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#type_spec}.
	 * @param ctx the parse tree
	 */
	void exitType_spec(MIDLParser.Type_specContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#scoped_name}.
	 * @param ctx the parse tree
	 */
	void enterScoped_name(MIDLParser.Scoped_nameContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#scoped_name}.
	 * @param ctx the parse tree
	 */
	void exitScoped_name(MIDLParser.Scoped_nameContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#base_type_spec}.
	 * @param ctx the parse tree
	 */
	void enterBase_type_spec(MIDLParser.Base_type_specContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#base_type_spec}.
	 * @param ctx the parse tree
	 */
	void exitBase_type_spec(MIDLParser.Base_type_specContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#floating_pt_type}.
	 * @param ctx the parse tree
	 */
	void enterFloating_pt_type(MIDLParser.Floating_pt_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#floating_pt_type}.
	 * @param ctx the parse tree
	 */
	void exitFloating_pt_type(MIDLParser.Floating_pt_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#integer_type}.
	 * @param ctx the parse tree
	 */
	void enterInteger_type(MIDLParser.Integer_typeContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#integer_type}.
	 * @param ctx the parse tree
	 */
	void exitInteger_type(MIDLParser.Integer_typeContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#signed_int}.
	 * @param ctx the parse tree
	 */
	void enterSigned_int(MIDLParser.Signed_intContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#signed_int}.
	 * @param ctx the parse tree
	 */
	void exitSigned_int(MIDLParser.Signed_intContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#unsigned_int}.
	 * @param ctx the parse tree
	 */
	void enterUnsigned_int(MIDLParser.Unsigned_intContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#unsigned_int}.
	 * @param ctx the parse tree
	 */
	void exitUnsigned_int(MIDLParser.Unsigned_intContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#declarators}.
	 * @param ctx the parse tree
	 */
	void enterDeclarators(MIDLParser.DeclaratorsContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#declarators}.
	 * @param ctx the parse tree
	 */
	void exitDeclarators(MIDLParser.DeclaratorsContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#declarator}.
	 * @param ctx the parse tree
	 */
	void enterDeclarator(MIDLParser.DeclaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#declarator}.
	 * @param ctx the parse tree
	 */
	void exitDeclarator(MIDLParser.DeclaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#simple_declarator}.
	 * @param ctx the parse tree
	 */
	void enterSimple_declarator(MIDLParser.Simple_declaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#simple_declarator}.
	 * @param ctx the parse tree
	 */
	void exitSimple_declarator(MIDLParser.Simple_declaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#array_declarator}.
	 * @param ctx the parse tree
	 */
	void enterArray_declarator(MIDLParser.Array_declaratorContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#array_declarator}.
	 * @param ctx the parse tree
	 */
	void exitArray_declarator(MIDLParser.Array_declaratorContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#exp_list}.
	 * @param ctx the parse tree
	 */
	void enterExp_list(MIDLParser.Exp_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#exp_list}.
	 * @param ctx the parse tree
	 */
	void exitExp_list(MIDLParser.Exp_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#or_expr}.
	 * @param ctx the parse tree
	 */
	void enterOr_expr(MIDLParser.Or_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#or_expr}.
	 * @param ctx the parse tree
	 */
	void exitOr_expr(MIDLParser.Or_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#xor_expr}.
	 * @param ctx the parse tree
	 */
	void enterXor_expr(MIDLParser.Xor_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#xor_expr}.
	 * @param ctx the parse tree
	 */
	void exitXor_expr(MIDLParser.Xor_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#and_expr}.
	 * @param ctx the parse tree
	 */
	void enterAnd_expr(MIDLParser.And_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#and_expr}.
	 * @param ctx the parse tree
	 */
	void exitAnd_expr(MIDLParser.And_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#shift_expr}.
	 * @param ctx the parse tree
	 */
	void enterShift_expr(MIDLParser.Shift_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#shift_expr}.
	 * @param ctx the parse tree
	 */
	void exitShift_expr(MIDLParser.Shift_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#add_expr}.
	 * @param ctx the parse tree
	 */
	void enterAdd_expr(MIDLParser.Add_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#add_expr}.
	 * @param ctx the parse tree
	 */
	void exitAdd_expr(MIDLParser.Add_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#mult_expr}.
	 * @param ctx the parse tree
	 */
	void enterMult_expr(MIDLParser.Mult_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#mult_expr}.
	 * @param ctx the parse tree
	 */
	void exitMult_expr(MIDLParser.Mult_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#unary_expr}.
	 * @param ctx the parse tree
	 */
	void enterUnary_expr(MIDLParser.Unary_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#unary_expr}.
	 * @param ctx the parse tree
	 */
	void exitUnary_expr(MIDLParser.Unary_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link MIDLParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteral(MIDLParser.LiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link MIDLParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteral(MIDLParser.LiteralContext ctx);
}