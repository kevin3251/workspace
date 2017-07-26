#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

int low,high,scale3,total_count;
string out_bits;
vector<int> cum;
string sid;


int lookup(char symbol){
	return sid.find(symbol);
}

int binaryToDecimal(string s){
    int tag = 0,i = 0,rem;
    int num = atoi(&s[0]);
    while(num!=0){
        rem = num%10;
        num /= 10;
        tag += rem*pow(2,i);
        i++;
    }
    return tag;
}

char decodeSymbol(string& bit_buffer, string& tag_str ,int& tag){
    int range = high - low + 1;
    int id = 1;
    while(tag > (low + (range * cum[id]) / total_count -1))
        id++;

    high = low + (range * cum[id] / total_count ) -1;
    low = low + (range * cum[id-1] / total_count);
    while(true){
        if(high < 128){

        }else if(low >=  128){
            tag -= 128;
            low -= 128;
            high -= 128;
        }else if(low > 64 && high  < 192){
            tag -= 64;
            low -= 64;
            high -= 64;
        }else
            break;

        low <<= 1;
        high = (high << 1) + 1;
        if(bit_buffer.empty()==false){
            tag_str.assign( bit_buffer, 0, 1);
            bit_buffer.erase(0,1);
        }else{
            tag_str.assign(1,'0');
        }
        tag = (tag << 1) + binaryToDecimal(tag_str);
    }
    return sid[id];
}

void decodeMsg(string out_bits){
    string decodeText = "";
    string bit_buffer,tag_str;
    bit_buffer.assign(out_bits);
    low = 0;
    high = 255;
    char symbol;
    if(bit_buffer.length() >= 8){
        tag_str.assign( bit_buffer, 0, 8);
        bit_buffer.erase(0,8);
    }else{
        tag_str.assign( bit_buffer, 0, bit_buffer.length()-1);
        tag_str.resize(8,'0');
        bit_buffer.clear();
    }
    int tag = binaryToDecimal(tag_str);
    while((symbol = decodeSymbol(bit_buffer, tag_str, tag))!='$'){
        decodeText.push_back(symbol);
    }
    cout <<"decode_text : "<<decodeText << endl;
}

void encodeSymbol(int sid){
	int range = high - low + 1;
	high = low + (range*cum[sid])/total_count -1;
	low  = low + (range*cum[sid-1])/total_count;

	while(true){
		if(high < 128){
			out_bits.push_back('0');
			while(scale3 > 0){
				out_bits.push_back('1');
				scale3--;
			}
		}else if(low >= 128){
			out_bits.push_back('1');
			while(scale3 > 0){
				out_bits.push_back('0');
				scale3--;
			}
			low -= 128;
			high -= 128;
		}else if( low > 64 && high < 192 ){
			scale3++;
			low -= 64;
			high -= 64;
		}else
			break;

		low <<= 1;
		high = (high << 1) + 1;
	}
}

void encodeMsg(string& text){
	low = 0;
	high = 255;
	out_bits ="";
	scale3 = 0;

	for(int i = 0; i < (int)text.length();i++){
		char symbol = text[i];
		int id = lookup(symbol);
		encodeSymbol(id);
	}
	scale3 += 1;
	if(low < 64){
		out_bits.push_back('0');
		while(scale3 > 0){
			out_bits.push_back('1');
			scale3--;
		}
	}else{
		out_bits.push_back('1');
		while(scale3 > 0){
			out_bits.push_back('0');
			scale3--;
		}
	}
}



int main() {
	sid.clear();
	cum.clear();
	sid.push_back(' ');
	string text = "";
	cout << "input_text : ";
	for(int i = 0;i < 256; i++){
		char c;
		cin.get(c);
		if(c != '\n'){
			text.push_back(c);
			if(sid.find(c)==string::npos)
				sid.push_back(c);
		}else
			break;
	}
    text.push_back('$');
	sid.push_back('$');
	cum.resize(sid.length(),0);
	for(int i = 0;i < (int)text.length(); i++)
        cum[lookup(text[i])]++;
	for(int i = 1;i <(int)cum.size();i++)
        cum[i] += cum[i-1];

    total_count = cum.back();
    encodeMsg(text);
    cout <<"out_bits: "<<out_bits << endl;
    decodeMsg(out_bits);
	return 0;
}
