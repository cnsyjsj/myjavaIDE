enum cc_sgn{
	_class_name,
	_string_text,
	_class,
	_info,
	_info_type,
	_info_name,
	_short_class,
	_short_other,
	_method_name,
	_method_type,
	_atri_type
};
enum sh_num{
	_consw,
	_flagw,
	_confw,
	_methw,
	_codew,
	_exmpw,
	_trysw,
	_linsw,
	_variw
};
enum po_num{
	_methp,
	_codep,
	_trysp,
	_linsp,
	_varip,
	_endmp=7
};
char c2x(char c){
	if(c>='0'&&c<='9')
		return c-'0';
	else if(c>='A'&&c<='F')
		return c-'A'+10;
	else return -1;
}
