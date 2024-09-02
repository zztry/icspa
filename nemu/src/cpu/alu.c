#include "cpu/cpu.h"

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest + src;
	
	set_CF_add(res, src, data_size);//unsigned arithmetic overflow
	set_PF(res);//
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	set_OF_add(res, src, dest, data_size);
	
	return res & (0xFFFFFFFF >> (32- data_size));//高位清0
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest + src + cpu.eflags.CF;
	uint32_t cf = cpu.eflags.CF;
	
	set_CF_adc(res,src,dest,data_size);
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	set_OF_adc(res,src,dest,cf,data_size );
	
	return res & (0xFFFFFFFF >> (32- data_size));
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest - src;
	
	set_CF_sub(res, dest, data_size);
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	set_OF_sub(res, src, dest, data_size);
	
	return res & (0xFFFFFFFF >> (32- data_size));
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest - src - cpu.eflags.CF;
	
	set_CF_sbb(res, src ,dest, data_size);
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	set_OF_sub(res, src, dest, data_size);
	
	return res & (0xFFFFFFFF >> (32- data_size));
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
    src = src & (0xFFFFFFFF >> (32- data_size));
    dest = dest & (0xFFFFFFFF >> (32- data_size));
	uint64_t res = 0;
	res = (uint64_t)dest * (uint64_t)src;
	//强制转换成64位乘法后正确
	//经验证，有些情况下会产生溢出，32位数相乘后只保留32位才赋给64位的参数，4000000000（dcd65000）*2 = ee6b2800不是80w
	res = res & (0xFFFFFFFFFFFFFFFF >> (64- data_size*2));
	if(data_size == 8)
	{
	    uint64_t test = 0x00000000000000FF & res;
	    if(test == res)
	    {
	        cpu.eflags.CF = 0;
	    }
	    else{
	        cpu.eflags.CF = 1;
	    }
	}
	else if(data_size == 16)
	{
	    uint64_t test = 0x000000000000FFFF & res;
	    if(test == res)
	    {
	        cpu.eflags.CF = 0;
	    }
	    else{
	        cpu.eflags.CF = 1;
	    }
	}
	else if (data_size == 32)
	{
	    uint64_t test = 0x00000000FFFFFFFF & res;
	    if(test == res)
	    {
	        cpu.eflags.CF = 0;
	    }
	    else{
	        cpu.eflags.CF = 1;
	    }
	}
	cpu.eflags.OF = cpu.eflags.CF;
	return res;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	int64_t src_ = sign_ext_64(src & (0xFFFFFFFF >> (32- data_size)),data_size);
    int64_t dest_ = sign_ext_64(dest & (0xFFFFFFFF >> (32- data_size)),data_size);
	int64_t res = 0;
	
	res = dest_ * src_;
	
	//res = res & (0xFFFFFFFFFFFFFFFF >> (64- data_size*2));
	
	return res;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	uint32_t res = 0;
	if(src == 0)
	{
	    assert(0);
	}
	else
	{
	    res = dest/src;
	}
	return res;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	int32_t res = 0;
	if(src == 0)
	{
	    assert(0);
	}
	else
	{
	    res = dest/src;
	}
	return res;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	uint32_t res = 0;
	res = dest % src;
	return res;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	int32_t res = 0;
	res = dest % src;
	return res;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest & src;
	
	cpu.eflags.CF = 0;
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	cpu.eflags.OF = 0;
	
	return res & (0xFFFFFFFF >> (32- data_size));//高位清0
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest ^ src;
	
	cpu.eflags.CF = 0;
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	cpu.eflags.OF = 0;
	
	return res & (0xFFFFFFFF >> (32- data_size));//高位清0
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	uint32_t res = 0;
	res = dest | src;
	
	cpu.eflags.CF = 0;
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	cpu.eflags.OF = 0;
	
	return res & (0xFFFFFFFF >> (32- data_size));//高位清0
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t res = dest;
	for(int i = 0;i<src;i++)
	{
	    cpu.eflags.CF = sign(sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size));
	    res = res * 2;
	}
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	
	return res & (0xFFFFFFFF >> (32- data_size));//高位清0
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
//逻辑右移，高位补0
//右移将高位移入了非0数字
	uint32_t res = dest;
	uint32_t di = 2;
	for(int i = 0;i<src;i++)
	{
	    cpu.eflags.CF = res & 0x00000001;
	    res = res / di;
	    if (data_size ==8)
	    {
	        //第八位变成0
	        res = res & 0xFFFFFF7F;
	    }
	    else if(data_size ==16)
	    {
	        //第16位变成0
	        res = res & 0xFFFF7FFF;
	    }
	}

	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	
	return res & (0xFFFFFFFF >> (32- data_size));//高位清0
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
//算数右移，高位补符号位
    uint32_t dest_sign = sign(sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size));
	uint32_t res = dest;
	//uint32_t di = 2;
	for(int i = 0;i<src;i++)
	{
	    
	    cpu.eflags.CF = res & 0x00000001;
	    res = res >>1 ;
	    if(dest_sign==0)
	    {
	        if (data_size ==8)
	        {
	            //第八位变成0
	            res = res & 0xFFFFFF7F;
	        }
	        else if(data_size ==16)
	        {
	            //第16位变成0
	            res = res & 0xFFFF7FFF;
	        }
	        else if(data_size ==32)
	        {
	            //第32位变成0
	            res = res & 0x7FFFFFFF;
	        }
	    }
	    else 
	    {
	        if (data_size ==8)
	        {
	            //第八位变成1
	            res = res | 0x00000080;
	        }
	        else if(data_size ==16)
	        {
	            //第16位变成1
	            res = res | 0x00008000;
	        }
	        else if(data_size == 32)
	        {
	            //第32位变成1
	            res = res | 0x80000000;
	        }
	    }
	    
	}

	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
//与shl相同
	uint32_t res = dest;
	for(int i = 0;i<src;i++)
	{
	    cpu.eflags.CF = sign(sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size));
	    res = res * 2;
	}
	set_PF(res);
	set_ZF(res ,data_size);
	set_SF(res, data_size);
	
	return res & (0xFFFFFFFF >> (32- data_size));//高位清0
#endif
}

//


//CF contains information relevant to unsigned integers
void set_CF_add(uint32_t result,uint32_t src, size_t data_size)
{
    //保留data_size位，符号扩展,右边是一个带符号数，左边为无符号数
    result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    //若和比加数小则借位，无符号数溢出
    cpu.eflags.CF = (result<src);
    
}

void set_CF_adc(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
    //先比较前两个加数
    uint32_t res1 = dest + src;
    res1 = sign_ext(res1 & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    if(res1<src)
    {
        cpu.eflags.CF = (res1<src);
    }
    else{
        result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size);
        cpu.eflags.CF = (result<res1);
    }
}

void set_CF_sub(uint32_t result, uint32_t dest,size_t data_size)
{
    result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (result>dest);
}

void set_CF_sbb(uint32_t result,uint32_t src,uint32_t dest,size_t data_size)
{
    //res1方法错误，见下
    uint32_t res1 = cpu.eflags.CF + src;
    res1 = sign_ext(res1 & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    if(cpu.eflags.CF == 0){
        cpu.eflags.CF = (src>dest);
    }
    else{
        cpu.eflags.CF = (src>=dest);
        //这里不能是(src+1)>dest，只能是src>=dest,为什么
        //个人推测是+1产生了溢出之后此bool表达式为假，就与无符号减法中x-x-1借位不符，故先算res+1的方法也错误
        //但是>=能避免此问题
    }
}

void set_PF(uint32_t result)
{
    uint32_t res[8];
    res[0] = result & 0x00000001;
    res[1] = (result & 0x00000002)>>1;
    res[2] = (result & 0x00000004)>>2;
    res[3] = (result & 0x00000008)>>3;
    res[4] = (result & 0x00000010)>>4;
    res[5] = (result & 0x00000020)>>5;
    res[6] = (result & 0x00000040)>>6;
    res[7] = (result & 0x00000080)>>7;
    
    int even = 0;
    for(int i = 0;i<8;i++)
    {
        if(res[i]==1){
            even+=1;
        }
    }
    if(even%2==0)
    {
        cpu.eflags.PF=1;
    }
    else{
        cpu.eflags.PF=0;
    }
}

void set_ZF(uint32_t result, size_t data_size) 
{
    result = result & (0xFFFFFFFF >> (32 - data_size));
    //保留data_size位，然后赋给无符号32位数，由于右边为无符号数故机器数不变，同时避免高位的影响
	cpu.eflags.ZF = (result == 0);
}

// SF and OF contain information relevant to signed integers
void set_SF(uint32_t res,size_t data_size)
{
    res = sign_ext(res & ( 0xFFFFFFFF >>(32 - data_size) ) ,data_size );//符号扩展
    cpu.eflags.SF = sign(res);//此函数取32位的最高位，返回一个无符号数
}

void set_OF_add(uint32_t res,uint32_t src,uint32_t dest,size_t data_size)
{
    //先进行符号扩展
    if(data_size==8){
        res = sign_ext(res & 0xFF, 8); 
		src = sign_ext(src & 0xFF, 8); 
		dest = sign_ext(dest & 0xFF, 8); 

    }
    else if(data_size ==16){
        res = sign_ext(res & 0xFFFF, 16); 
		src = sign_ext(src & 0xFFFF, 16); 
		dest = sign_ext(dest & 0xFFFF, 16); 
    }
    
    //如果一正一负必为0，符号相同则判断
    if(sign(dest)==sign(src))
    {
        if(sign(res)!=sign(src))
        {
            cpu.eflags.OF = 1;
        }
        else{
            cpu.eflags.OF = 0;
        }
    }
    else{
        cpu.eflags.OF = 0;
    }
}


void set_OF_adc(uint32_t res,uint32_t src,uint32_t dest,uint32_t CF,size_t data_size)
{
    //uint32_t res1 = dest + src;
    //先进行符号扩展
    if(data_size==8){
        res = sign_ext(res & 0xFF, 8); 
		src = sign_ext(src & 0xFF, 8); 
		dest = sign_ext(dest & 0xFF, 8); 
        //res1 = sign_ext(res1 & 0xFF, 8); 
    }
    else if(data_size ==16){
        res = sign_ext(res & 0xFFFF, 16); 
		src = sign_ext(src & 0xFFFF, 16); 
		dest = sign_ext(dest & 0xFFFF, 16); 
		//res1 = sign_ext(res1 & 0xFFFF, 16); 
    }
    
     if(sign(dest)==sign(src))
        {
            if(sign(res)!=sign(src))
            {
                cpu.eflags.OF = 1;
            }
        else{
                cpu.eflags.OF = 0;
            }
        }
        else{
            cpu.eflags.OF = 0;
        }
    /* why it is error 在这种情况下应该等价
    //如果符号相同相加后不同则为1
    if(CF == 0)
    {
        if(sign(dest)==sign(src))
        {
            if(sign(res)!=sign(src))
            {
                cpu.eflags.OF = 1;
            }
        else{
                cpu.eflags.OF = 0;
            }
        }
        else{
            cpu.eflags.OF = 0;
        }
    }
    else{
        //CF为1，所以若res1为正而res为负则of=1
        if(sign(res1)==0 && sign(res)>0)
        {
            cpu.eflags.OF = 1;
        }
        else{
            cpu.eflags.OF = 0;
        }
    }*/
    
    
}

void set_OF_sub(uint32_t res,uint32_t src,uint32_t dest,size_t data_size)
{
    //先进行符号扩展
    if(data_size==8){
        res = sign_ext(res & 0xFF, 8); 
		src = sign_ext(src & 0xFF, 8); 
		dest = sign_ext(dest & 0xFF, 8); 

    }
    else if(data_size ==16){
        res = sign_ext(res & 0xFFFF, 16); 
		src = sign_ext(src & 0xFFFF, 16); 
		dest = sign_ext(dest & 0xFFFF, 16); 
    }
    
    //sign(src) ->-sign(src)
    if(sign(dest)!=sign(src))
    {
        if(sign(res)==sign(src))
        {
            cpu.eflags.OF = 1;
        }
        else{
            cpu.eflags.OF = 0;
        }
    }
    else{
        cpu.eflags.OF = 0;
    }
}




