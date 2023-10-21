#ifndef __INSTR_JCC_H__
#define __INSTR_JCC_H__

make_instr_func(je_short_);         //74 ok
make_instr_func(ja_short_);         //77
make_instr_func(jae_short_);        //73
make_instr_func(jb_short_);         //72
make_instr_func(jecxz_short_);      //e3
make_instr_func(jg_short_);         //  ?7f ok
make_instr_func(jge_short_);        //7d
make_instr_func(jl_short_);         //7c
make_instr_func(jle_short_);        //  ?7e ok
make_instr_func(jna_short_);        //76
make_instr_func(jne_short_);        //75
make_instr_func(jno_short_);        //71
make_instr_func(jnp_short_);        //7b
make_instr_func(jns_short_);        //79
make_instr_func(jo_short_);         //70
make_instr_func(jp_short_);         //7a
make_instr_func(js_short_);         //78

make_instr_func(je_near);
make_instr_func(ja_near);
make_instr_func(jae_near);
make_instr_func(jb_near);
make_instr_func(jg_near);
make_instr_func(jge_near);
make_instr_func(jl_near);
make_instr_func(jle_near);
make_instr_func(jna_near);
make_instr_func(jne_near);
make_instr_func(jno_near);
make_instr_func(jnp_near);
make_instr_func(jns_near);
make_instr_func(jo_near);
make_instr_func(jp_near);
make_instr_func(js_near);

#endif
