#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "header.h"

using namespace std;

int iE00 = 33;
const int N0=124;


const char Arr00[]=
"Ä,Q`WTPIº®\bDS_`][]^hgaJõ¬é9MWaJ6/,.:WjiiVÙª£«>ISW=! -3Fafga5ð¶¤°>NRN5\r\f\f\b\n9\\gi`8ïµ¢¦÷;LU[<\n÷áäßÝØëA_ijd.à­¢ß2FMR;þäÚÏÅÁ¹¹ÃØï\"HYgi`$Ò¤À\"DOQM+ýßÔÌÁº±©«®¶Íî-O^gjUµ¡öAQWL5\våÕË¿·®­¨¥¥­´È\aA]dfd8Ø¤Á,KTWF!îÛÐÃ¹®¨¦¦¦¤¥¨¼ÞO^nlW­ñAQ\\U?\nÝÒÈÁ¯¦£ £©°ÇD]hmn6Â¥O[^T-ûßË½¸¦ £¤¯Ãå)YhpqWéØ=P_]I'ñÚÄ¶´¢¥¬½ÙMhosn£\vF[e`DçÒ½±°¢£ª»ÒÿEcrwu@§&O]gWDàÌº¯©  ©±Ëò:Zpvv`ÃD\\acY6ýàÈ²¬§­Èæ#Pkswoã½K]eaW1ôÛÁ²¬¢¢ªÃÜ\fJhvxpþþR_ifSæ×Á¯© ª¾ÑIexzt0,ZfigRãÕÁ²ª ª½ÏýEbxzvc>[gpfTáÕÁ°£ ªÁÏüAdxvtjP_gsgR\nÝË¸¬£ ªÁËù<duuqjWfkvjR\nßÌ·§ ª¾Êü;_sukf[fqvjO\tÝË´§§½Ð?`sukf_gxzjM\bÜÄ±¤ª½Ð<`ouhb[jxzmN\bÜÆµ¥ ª½ØB`nmd_[q{zmQ\bÙÅ¶«­½ÖA_opd_bw{zmQ\aÔÆµ«®ÁÖA^god_bw{zjPÑÉ³§°Ä×AZgicTb{{zkV\bÓÇ³§£´ÉÚ\bAVegZFbz{znV\tÕÃ±¤£¶ÊÚAUggY*,v{zr]ÚÈ³¤¨¶Ìà>WdcTírzwq]\"ãÊ¶¥«¾Ôë#C[b\\E´Ör{wtc2ìÌ¶¢¢°ÄÜô&G[a[>½dzyufGÏ·¥¡¦¶ÇÞ.L]]Q\"¤Dv{vjNÎ½ª£ª³Ëå8S_[P¤pyvjVÙÃ®¥ ¡¬¼Ñç=WZYBÑ¤óWysn^-îÈµ¥ ¦¯ÇÓñ JWXPÁ2rtqbM\vÎ¶ª¤¡ªµÇÔ1JUWEò¥YspcQãÃ²©§¢¥¨²ÅÎà:HMN(¾¤Ü7qsf_A\bÎ½·ª¤£¢¢¥«½ÃÖ-EQQDø°úStpcS*òÍ¾²§¦¦¤±ºÄÐð<HMH%¸¤Ð$`pnbKóÖÉ´²²²ÀÏßø,GLF=ä§ß5fsmcB\aäÏÌÏÓÛñ\b1LLJEù¤¶ñ:jxnd=\f\vþ\r+>NOD¦ ´ð=jtvlF3!7KRPF£­Þ&cstw`D;2.4BNUT?æ ±ÿSosska[[S^\\I® ¢¹\fWb\\Y]Y6Å";
int iE01 = 23;
const int N1=126;


const char Arr01[]=
"¡£´ÓîçÁÂËÓÝÆÍ¡¨¹Òåýûêõý÷õíÆ¨«ºÌÝ.*$\núûõéÏ«¶ÉÚè+-:AE;\rþýóéÚ ²½ÁÉÙéú/1CHS\\?þ÷ïäÓ±¹½¹Ìåö\r#1DGXrbB!þ÷ïÛÆµÅËÕäíý\r#8H[msgBøèÐÂ¹ËÓ×âîó\b';VelziEøàÎ½½ÈÙÝÛçïø'?V`kxf=öÚÅµÉÌÌËÕàôý<L^hqe?úåÕÃ±ÅÈÍàêòõý\"0ETim`AòãÏÂ­±ÊÐÓÕãèó\f*CYdbY@ðàÌ½©½ÌÏÓ×âæè*@NY^W<ìßÌ»¥µ½ÁÇÊÒÝÛö8K[`Y;çÔÄ¸¥±´½ÁÄÅÅÍò5IV`Y;\fþåÒÄ¸¥­­··´µºÂé4H[`W5\rúäÒÄ¸¥¤¡¡¥±¿ã8H]aW3\t÷ÞÉÂ·¥¡±¹à:M_aU-÷ÞÉÁ´¥¨°â=NYYS.ñ×ÉÁ´¡£²äAP[YQ,ñÕÇ¿´¡­è BP[\\O(ìÑÇ¿´¡¶ï\"DPWZM(ìÎÆ¼´¡ ¾ò#HPWXK%ýêÎÇ¿´¡£Áò#DNUVJ#øèÌÅ¿´¡«Æù%DHYZH!öãÌÃ¼´¡°Çø%BIUTFóáÌÃ¼´¡°Êø#@IUTFðàÊÃ»°¡´Ïú#>IUQEðàÊÃ»°¡¢¹Ïú#>LPRBíàÊÃ»°¡¢¹Ñû!;LNP?íÝÊÃ¹ª «»Ñþ!;JLL:êÝÈÁ¹ª «¿Ñþ=JLL:êÝÈÁ¹ª ¬ÀÔþ@CJK:æÝÈÁ¹ª  ¬ÀÒú>AJG6æÝÈÁ¹«¤¦®ÃÒú;AJG6æÛÅÁ¹«¤¦²ÃÑ÷!:CHG6\væÛÅÁ¹«¤¦µÂÑö7AHG4\tæÛÅÁ¶¨¤§¬¹ÂÎö2?DC4\fæÞÎÅº®­¡¨¯¹ÂÊô2?DC6æÞÎÅ¼¯¨¡¨²¼ÃÊö2?DA0æÞÑÉ½­¨«­²»ÃÎõ-=A@*çÞÎÈ·­¨¡¬±·ÀÆÐó09@A0äÙÍÌÁ¶­¨°·¾ÄÎ×ü!39@>3ôâØÔÇº±­½ÁÄÉÓÝð(75>>@+õíäÕÉÅ¤ÄÅÈÍØâù,35@A=5ÿóïæÙÎ±ÄØÝÞçð\v(987<7<9+ü÷ïáÕÅÚñû\b'.5622--;73%\nöÉéú\v&('!$%(4::6.)";
int iE02 = 32;
const int N2=122;


const char Arr02[]=
"¡»ø/NXafg[=ÿ»¦¨½ð,TW\\cgimlrwjV6ü½¤ª¹Þ\"LYXSTTVT^ajhptgU-ö¶¡­Î\b6QOF@C7324@DRYdipiT4\tË­Ë\t9JDA9)!(0146L_kojU3\aÐ¦Ä÷1MA0/÷îéêçí*5CXenhO1Á´Û63%ñäÚÔÇÂÁÆÏÚí*@QdjY@î£»ò'-#\nñáÖÊÆ¿¶µ°ºÂÔè*FZjgQ9\rÒÈû#øåÕÃºº®§©¦©³¾Õí\n+NdnX<ðÉ\fþîÑË¿¸±¤¤°Êà÷@XnaH8ý¸ÜýñÙÃ¼´®¥«½Íê+KleP8\fÜç\r\t\tÿôÎ¶¶¯§¡¦ºËá&DjjX>âßøéÇ¼¹© ´ÅÚ >ijU:éÆêóìä×Äºµ´§±ÅÜÿ\"BjkU:é²×ÞÙÛÓÈ¼·¯¦¢±Æá\b%?jiQ3ß®ÁËÓÒÌÇ¿¸³¢¤³Éå\a%GjjN)\bÖ¨®½¿ÀÂ»¹®¤¥±Ìï\n+KjeKûÉ¡¤¯²²®¯¬£¨µÔú>ThW<\bäª¤¥¥¥¤ «Ãæ)C]bS(üÎ£§µÚõ<LV[AñÅ­Åí\n)MSZI%øÐ¥®¸Úþ GQZX=\nàÄ«»Óú4JPYEèÉ ¨ÁÕé\bHSWF#úÏ¯ »Öç\a:LRH*×°º×ã,KPA,Ú´º×æû)GO@'ß¶¡±Íâò+>E;&\rÝ·¨Èßó\n\"#83 è½ªÅÚì\b3.\réÂ¯ÃÒå$4/ê¿­¾Ñéü!!)\vêÀ©»Êâô%\"\v\bèÁ¢¤µÊâò+!\n\tã¼¦µÊáö'#\n\fç¸ ¨»Ðè)%'\tæ·£§¥¼Ôèô\"(+çÃ¤ ¤±¸¿§½Ðç÷*-!\fàÆ¬©¦¤¢¡ ¡¤¦ª´¸ÈÙÃ¸Ïì'/!áË¶µ³³µµ··µ³°µÃÈÎÕäÊ«Éð\f!#1A,íÔÆÃÁ½½Â¿ÁÁ¿ÀÄÍÑÌÕãã½¡¿ì-6L:'úßÓÐÎÍÌÍÏÏÑÔÔÏÓàåçïýì¿«á0EWH4\vùïíïíêêêîññòôôú\t\bíÍÉ\t0G][G.,)),,+,,,*&)/-0//-2. \nàã2I`da[WTTTTWWWWTTTX[[YWXSPOC\"òû%HbfjhhikkkknlnkkfeghfededbO4 õþ8Z__^^_`aba`^`aaadhfbaa_ZZTC2òBGIKMLFIJFDJMMMOTUWTVVMLKGB9\"\rè\"/*0+0/131/,-03249=98;6844.'\"ÿØ";
int iE03 = 31;
const int N3=124;


const char Arr03[]=
"¨»×ö&KTT[`_SÙºµ³©£¨ÁÓâúMX^`dfjkpvwsY(áÂ¸¬¤¡²ÃÝöDRZORRUUT`elrwytNÖ¿°£«ÂÑø%?NNGI>7234:E[chhrjR ßÁ¨®Êí!:G>1# %5FT\\^hdTÚº®Õ,8/\füçãÛÜàáëû(7CLXmfIÀ¦«Ò(-÷êàÖÉÅ··¹»ÈØô7DX_gX4Ù±©åùàÏÍ·¯±®«®¯·¼Ïí?GXb_Cö½­åûãÙÑ¹®¨©©¦¤¢§«¸×ü4EQ`]H!Ð°ãûïçÝÐÁ¯¢¯Íë;G\\ZN1Ô±ÞçâØÒÍÂª ´Ëê\v0GXYI-Ò´ÕØÐÐÇ¹¬¦¯Ëæ\a0GXPA*Ìº¼¸½¹®¢¢©³Êç\n.ITJ;Â¡¡¥¥©¦ªª³¸Òò9KM>4Á¡ª¨°»Þÿ>MG:\"ø²¡¥ª³Áí(IG?*Ó¥¥¤ª·¿Ü @F;.þµ¥¬²½ÁÔú1C;(\tÖ§ ¥«µ¾ÁÉç3@3Ü¯¢°³·¼ÐÜãý7FI>3+ä¼§¬¸Ñåÿ%1BLJQSF;ùÆ©§ÃÏß÷6HSX_chaM1+á¼¨²ÆÛð\"<HTXX\\[]K7þñÝº¤§¹Èå*,,/8AL_gcY>\vöâÄ¤¬¸ÃÕêùÿ\t#8Rjmh]?\tå½¦¬µ½À¾ÆÎØàø)DcmoqSã±¬¿Ôæÿ*H`lvuUÊ³Øü!GeswnJì¨¡³Ð\t7\\lwrb:¾«¼âFgqyiNÜ¦·Ò<gnzoW¤±Íì^npp`H§­­¦¥¯Êãainp\\K¡¥¬´´«¥¯Ëå\\gnp]K§¾ÆÈÄ¾®¢¥´Ðì\"^gllWDÎãèåàÏ¸©¢¥´ÖìWgkfR1ØùóðçØË³¢¢¬½Üó[fdZFìýõíâÑ¹¦¡ªµÊßCaeeN2çÒ\fòæØ¼ª¢ ª²ÁÕïSca^>Ü\vïæÔÂ²¥¢§±ÁÏç9[_`K)úÕ÷èßË¿°¨£¡¡¤ª³ÄÏä\a/M\\]U4¹ÈêÙËÃº¶µ²·»ÀÉÓí\b$L]\\S>èÎ(@4îìÝÓÕÒÕØÚçð\b+DZ`VC÷Òõ!4L:'\aÿüüÿ\r4N[ZU;õ¦Îç\"7UN=-.'0OQZVC'ê »Ñí=Zc[J>69>@BJS[YI/þ¾®ÄÜø4Gemjkh`\\[[XJ+þÆ¤µÔåý)C\\he_G*íÁ";
int iE04 = 34;
const int N4=124;


const char Arr04[]=
"¨§±ÁÐáú\fëÐª¡¬ª²¾Òã\t()4-\n×°¤­±½Ïà\n089A4Þ¶£ ©±¸Ìàø-8?AF;â»¥¤­³ÉÛ÷9?AGK9æ½§¢ª°¾Þî49HKJL;æ½¥§°¹Ðè\n,7=BJLO?å½¤¤­´Êå(6?@EKNRAåº  ©³ÆÜö2?/5@OSS;äº¥¢°¾Ðô*80 )9SRM8å½§¬¸Èæ\t)55\n<SPN=é¾¤ ³ÇÛ'-;ý9QQLAæ»¡´¿Ìñ.+\"üìì:OQTAè½¢§¹Ìò,-\níÒà\r9LWWEæ» ¢±ÄÙ\r.3#ñ×ÇÜ\r5KWYGæ¸§ÁÒ'0)éÔ½ÅÚ\t2UZ\\Jç¸¡·Íó(5üÛ¹¼ÀÚ\v6U\\]Gà¶°Æå+7(Þ¹«±»Ö\f;U\\]Fßµ¢½Õ\n\"1,îÈ¦¥®·ØC]d^Iß´³Éú+*÷Ð®¤¯ºÜEah`IÝ²ªÃë+4)Ü¶¢ª»æHah_EÝ°½á\r+7-ðÈ¨ª½çG_bZ@\rÙ¬³Ðú&3*$ùÒ¯ªÄê\"I_`Y>\nÙ­¦Àñ4=3Ü½®Æí#I\\^[BÜ°¾Ý+8/!óÐ®¡¦¹Ëð#I\\__EÝ° ªØú(2.'\tÞÁ¬¦¡ª½Ðð$L_b`Hä¶¨£½î 4>6ðÙ¾·³®¬ª·ÌÜö)NcgaP#ïÅ´¨¥¬Þ\b7NF9ñÐËÄÁÁ¿½ËÞí.NcidV,ûÖÈ½ºÂ¼Åø6OXN5\vïèãÞÝÛÙÙæöý9Xjoma:íà×ÝÝÓë D^aR5&\r\v\a\a\n 1M^ijh_G#\tüþòô2LVOA-\r\v'*;Q`gbdV;!\vÿþì\a/EE:/\"!-07ET[a]]P7%\bïû/.,*%$\"!!!&,8@GKXZ\\YYK4*$\nøû\"!!!&*,:>GK[ab]YI6*%\aøâôõøúõ÷úøøöóü\t!.EX_\\T=øöóêäÈÞââßÞÞÞÞÞÞâæêìö\t7QZXS9óëßÝ×ÕÒ¹ºÃÅÅÅÅÅÅÅÅÈÌÓÖÚçè÷\v.KWXR5ÛÏÆÄÂÃÂ£££££££§©®¹ºÈÇÚôDSWO0ÿË®¢¡¦£ ª¬¶¿ÖñFOOI(÷Å¦ §©°¹ÑêALKE'÷Å¤¡¢²ºÓê@LJA(ùÅ¤¡¡­ºÓê@LH=(üÆ¤ ¡£¯ÅÙð?JJ@(Îª  ¤²ÊÙò=JJ@*Ô­£©´Èàþ#>LHD0Õµ£¨­¼Øî\">HA:,æ¼§§´¹ÄÖèò0?>;2èÉ±¦¦­ÂÍÖëïõ\a';42(õÙ¾³¥";
int iE05 = 29;
const int N5=124;


const char Arr05[]=
"¡½Úê\a\t\f!&#\nïÊ¥¿ä**09:8<==>@<974>IQJ9¾«Èù7AIQ[\\^aaaa`^_aahjj\\=÷®¯Ì,CGL[a^ceaaaa`^^^bh`Q*Ü ¯Í*<<EORX\\PMMMMMMQW\\`WGÈ¯Ï\f1;/*0**.*!!#&&'-0/+ýÚ®¹Ý7>&ýóñèãåçèêéêíáÑÃ²ºê92#ïãÙÑËÌÌÌÌÍËÆÃ½¬¥»ç8/\aùåÙÒËÂÂ¿¼¸¶³°ª»ì1!\féÖÈÀ±ª¥¤¤¢ ¿ï#7&æÍ¾²¤£À÷&<+åÎ½´££Ãû):'üÝË¹«§È07ôÚÃ·­ §Ì\f6?ùèÐÂ·¦£¡¡§Ï8C%ïÒÊ»¶ÁÀÂ¾¸¶¢«Ï;G+\nõâáÝäçíêêçÝÎ·¤«Ô>G/\n\n\r\v\tþüúôïèàÍ¸¬å=9++4A:.0463,&\bòèàÃ³ñAEEATPKE@B>GAA>91õåÆ­ð29FLM>4&&+7?LKJA/ìÁ¬è0?>=.\r1>KZWM:ñ·²í$#öëíâÙØàô\t=Pa^YEæ ©ÙïõîáØÒÇÂÁÀ¿Ìâ9QfgYC\t·³ÈÓÕÉ¸¶¬«­¦£¦²ÅÖì\b@aljV=í¢³³«¤ ¯¿Öç.JamdD¡£±¿ÕöC\\mn\\7À£³»Úü0RglgRï¡©¸ÃîIdklV¤±ÇÞ\t>_jlX)¤¯¾×ÿ7_jl]=§±½Öü4]hj\\=©±½Õö7aim\\:£¡¤ ¡¨°»Ë÷:bhj\\0²µ°­© §±ºÌ>bhiR¼ÅÍÒÏ¶¥¨±¹Ñ\tGfjjKýÌã×Ü×Ä§¤ª²Çè!Wclb5²ÖðóèßÇ³¡£¨­µÏö0\\ejVÆ÷ê×¼¢£«°Âå\fE^lgEëÝðØÅ« ¡ª¶Ãßü1TbgM°Ö\"úëÓÂ­¨¢¡¤¨¶ÈÝõ B\\f\\/ßÌ\t)'÷ÞÒÉ»·¶®²·»Ëæÿ;[`^?§Æ\v.:.ÿôëÙÔÏÐÓÜä9Waa@¹Öö\">D?,üþ!>Tdb>\v¾Ïç2OXUC9/  $6I^_T9µÉáõ\r.Je_VKC<8>FLZ][Jï¤ºÏì#FfpliaY[__UI\"ó³¡¶Éß%7^gbXDðÅ";
int iE06 = 33;
const int N6=123;


const char Arr06[]=
"¬¼È×çó\n\túïíôäÐ¾±¥°¾ÈÛçô#+3>C<þê½¨­¾ÊÖåø\t!/DHC:)*\bçÐ½§±ÂÑÞê'AG@2%\vèÊ´§±ÊÕâ÷9?1(þòòïßÍ³¢²ÉÕæû ,(ñãäÛÕØÜÜÜÏ¸¢®ÂÒçý\r+#îÙÔÆÆÉÑÐÉÂÅÆ½¨ÄÓèû&\tùáÏÈ¿ºº¼¿½¿¼¼¼¸§ºÓãú&#ùßÏÄ¹º²±®®µ¹º¼¹º¬¯Éå÷\f!-#üßÇ¹²²°©¨¡¦­³¶´¸¸°ÃÙõ\n7/\vßÈ½®®ª¦¤ ª´µ·´¬­Éé\b!69íÏ¿±¯©¦¢§®°ªÁÜû3K7\vøÜÆ²¯¬¥Êñ/FA$ýÞËº²¬§¹Ü$CQ<\vòØÃµ²¬ Èò;MO8ÿßÎÅºµ¤Ë*ISM.óÖÉ¿¼­¨ª¤¢¥ª¬®Þ:NVG#ìÔÉÇ¼ÀÓÖÞäçêãÑ»°¢¯ù,JUXG ÞÕÛéâò\v\r$%#óÜ¾¯Á<O\\aC üæö\r\"+28?EB6%Ô·¡Î&HW^\\B$)$!&)7?AGQQH9!ç¸¢ä=OX_^>&093*\")2AJPZ`RJ.ö·¡ù>YchbK<=5( \a÷éëîú'CS_cd^Q2þ±F]godUO=+þð×ÈÈÆÄÉÔëATZli]P2ï¥1Qbrof\\O(üØÉ½±®²²°µ¾Ôú@XajkdI\"¶A\\hvri\\GõÑÂ¾­¢¥¥¢£®¼»Ç\a<Z`ji_@\nG_nvqiT#úÙÆº³¢¡«´ÁÙSeklkY/«ShsytfFçÎ·­ªª±Êõ2\\eim`=ÉZot|vh?óÖÇ·« ¥­¾äWgikbT#crv{uc3ðÍº­§¥®º×ÿ;afgc\\D]rx{vb(ëÌ·©£¡¨·Òì-Ydjg_PSuy{t_!éÈ®¤£ ¨¾Ïå'Xdgg`W;sy{ua ãÅ¬¡¦¼ÏæS`eg`Tuy{ug&èÅ®¤®¼ÐäQYcb`Qðovvvk1ëÄ­§±¼ÐáNYab_JÔ\\rvvmCùÈ®ª¥³ÂÔåGW_`U3¬9pvvmJ\tÓº­¦«¶ÃÖö-JY`aHÝ¢iomkY+ê¼­©¤¦ª¸ÈØ8NWaY8×<otshDýÇ¶°©¡£­¶¾Îì=QV\\M´bmpiM'é¾¶±ª¢¢¤¢£¦±½É×5HRWR5ÃÛ1ajm]?\fØ¿¹·©¥¤¨¦¯ÀÆØö8LZUH²÷OgjlX5ÝÒÁµµ¶µ¶ÀÓÛó7DNSN(®Ç\rYfliZ6\n÷äÎËËÌÏ×ð6@JSL4Ì£ËZhoiYDúñðñ÷\"8DSVL5Ñ¡ÅXhri]R0\v\b\f-;LUQL0Â¡¼öMftle^M9;9>HRXXUC¦£½Zkvvrjdba^ZXP²¨ÉHbjc`XN4Í";
int iE07 = 31;
const int N7=122;


const char Arr07[]=
"å*28.030,10//-,,,)&&&$   &,37'õ#0CNUWRTUXZXVPNKHHHHGIHGHMPUN-ø$>S\\bfgllmmmmmljjjhkmmgfhgknc(û)>U_jllpqsqpppppmmmnppmmruyyYû)FPX]`cdfdcccccc`^^``ceinsuhAüâ\n(.554554010//..//-,.,3LcpnYÆÖï\bøïççåãåååååååèåèõ\v4ap_,ì§Ðúþ÷ðÞÐÍÐÎÍÍÍÍÌÈÊÊÊÏÓßå\a;^^R\bÎ ÊîùçÖÁµ·¶´´±®±¯®±±´·ÆØñI[V$á¯ÁèëÔÀ¶««ª¢¢¢¤¥¥¥¥¥ª²Äà-KQ?þÌ ÄâÚÀ°§¢§·Íé=LJ\"àººÒ½«¢¬½ä\t$F?2ÿÎ¥ºÉ­­Íô6B?Þ¿¥«¥¼æ\t%A<-Î¨¯Õ÷*=<æÃªÈï54/Ê¯ ºÚø-;4äÂ¡°Ðî\a55(Óµ¼Üú.8*áÃ£´Öõ.4&\bÞ¾ Ââý,3%ðÈ®¼Òö!-.#ßÀ¦Çç$0#öÒ´ ½Õú\f,-$çÇ¢±Íì\t(3$þÚ»¥»Úû\n'-&ëË²¡²Ëì!-& \bÜÂ¦©¿Þö\"-(ëÏ¸¡¢­Çê$/'âÉ¬©ºÝø\t\"''!ôØ¾£¯Êæù#2)\råÍ·¨µÔð+)&ýàÉ®£±Áçú\a%.-$ëÖÂ¦§´Íë*-&æÒ³¢£­µÞ÷\b#-0'öáÔ³ ¦¯Éé()-!\bêÙË®¡ª±Õó '.)úèÔÀ®¢ª½çú**/&óÜÌ½¬¡°Ìø\b*(*!ê×Èµ¦ ¨µáø -/)÷çÌÃ¶§¡®Ãæý$.%&\bòäÓÂ³¤§³Íë,+) þíÙÍ¾°£®ÃÜú\t '))öçÖÊ½²¤ºËæÿ')$óâÑÇ»°¡«ÄÑãþ\"%(òàÐÅ¸¦¡·ÊÓêÿ!íèÜÊ¿·¨¨»ÁÏèþ\b\fóéÝÐÊ¿¶¨¡±¸ÈØùüöêà×ÏÊÁ¸©";
int iE08 = 32;
const int N8=123;


const char Arr08[]=
"È\"CLMU_]Z\"Ó°Î\"CKIJKPWdjtwrb!Ð¬¡µ\v;EFH;-,.0<LaehmhYÄ¬£Î FLA1\"+=RTbmd(Ü·¦Õ!HJ>-\vþüüþ3FSioc-Ý·ÊDK?'óÞÞÖÔÏËÚë/GTghc*Ì©­ÿ=GB6õáÔÊÂºµ­­¸Êß/NZfbIò±Ó)HJ<$õÚËÄ¼³ª¢¢ ª²¿ä=R_f`'Ä¤ø7MG;\aÞÏÈÄ³¦ £¬Áñ'FVha?Ü¬ÎJLK8øàÏÅº¯£·Û;WeePñ°Ú+LHE6òÒÊ¿¸©¤±Ö\v8TccPü´Ü.LHH>îÑÉÀ´¦­Ù>UbbPü©Ü0MJI>õÙÊÀµ¦©ÜBX]\\Dô¢Ü0OKI@1ßÍÃ¸¦³çJ[\\W/Ý×,HJJB>õÖÇ¸­£Ë-PZYA\nÔ¾\f>LKJE6íÔ½­¢¡µå8\\\\K#è»£ï3DGMNE3õ×»°§£±Ø\b*J]R+Ò£Ñ<ELNQE9÷äÏ»°©¥©Ïÿ DSU(ß½³í\"?CMWSG@%õÙÆÄÐÝ%BNK'ÿèÆ¶ð ?GPYXRH>-\tý!0HP?&éÉ¨ Äò7KT[]_ZQRLABCOH3&\våÊ©¯Êá3P\\`cgf``bb^^J.\vîË¯¯Ëì@ZilglilkiigbFîÅ®«Ëï%Kfoqihkqrohf\\?ò¸¡«Òð\v)BdjeIOU[gnmjemjZ3\nÐ§­Óõ>\\`O<ÿù\"?LYZ_hpl_E×¦©Û1KdW> ùÓ¿ÁÁÒï3MX[flh^HÖÕE\\fZ;Û¸°¦£¬²³Ìê2OX_ji^F¼Ä@Yl]@\aØ´ª£¯¿Ý)MZagdY@ôî<VqkJÜ¹¦ °Å×ú!M[`d_Z4°¨+Qos^3ûÍ¬©´ÄÕù+Q`de^MàÚLmuhMÝ¶¬¶ÁÜÿ3\\Z_\\W8_urf>ùÍ²¥²ºÍï$PV`a\\WJtvqd5çÁ­ ®¶Éá\aCW``]Z`uvob5çÃ­¬´ÆÕ;O^`]Tluwq`4æ¿­¥®´ÅÓ:M[`ZMssvq`4ä¾³£©°·ÇÑ9NY\\SG`ssqe9üË¶¥¨±¹ÉÜ?QY\\P.tsnfEÔµ¬¥§±ÀËë'DMXWAÌÔosshU)ýÑ·¬ ¥¯»Æâ0EPSL&@prlc@êÆ¶°­££¤²¹Ã×ü&?MTTGçñarrgQ.ìÑÄ·¯®°³²´ÃÏßþ4EMQJ¤!fprhL-ùðÙÇÈÉÈÉÍáú/>LPI\"¾³#dnuhP;\"þóóóóóý\n1?JPF'ÈµcnvjZE1\"\v\t\n!0=HMLEº¥ðLqsukcQ=8699<IQUTO?ë¡®õVvw|umkdcaYWWS>ü¢¬ëPmqsj`\\P<é";
int iE09 = 33;
const int N9=120;


const char Arr09[]=
"Ò(FQ[fhfR¿­À GRY\\\\Z\\_fsys^¿«¬ARXUNB8357I_ru|jOó½£Ï3FMTQD2 0Maisk^Ë©à6EJLC;$\r\bþüþþ\a?Rajff(Õ¯Ô4EJHC9*ãÖØÒÐÖé÷\f0UenrgÑ­¹+FKC?7 æÛÅ½¶´²µÄÒá2Tjru^û½AQLF@'ÝÉÇ»«¤£¤¥²ºÆáCcourJé§Ó=ONKJ?äÍÁ½« ¡¢£«²¸Èõ,Mcstj¸(JVRLE+ùÕÇ¿³§¡«¶ÁÖA]pvvIÛ:S^PPAáÌ¼·¨¨«¶Êí.Wkxu]ûèDVWUP4ûÚË»³£¤ª²¾ÝUnttn0±0LY\\YU%ë×Åµª¤¯¸ÓJelrpMÑ=U^\\\\U$èÐÁµ¤¡£ªµÐú;^jst^ñFV^\\\\Z#ãÐÀ±¤¢¨¨´Îò*WjvxkI\\a]^]%ãÐ¾­¤£¨³Îë!Ultvk<M\\b_b_$çÓ¿°¦§°½Ñë!SiuvmWI^cec^-íÐÁ²§¡¬°ÀÔë VjttlZ@]gfb\\:ýÓÂ¶³ ¦³¶ÁÓñ)Xltrj]*[ghedQäÁ»·©ª¹ÀÐà8`lrrg\\ÌEadbdY2øÊºº­¡¶ÁÌÝò@cmolaP©7Vbbd_TéÈ½·©¥¾ÌÙë.Lcjmk^DAX\\b^R7\aÖÍ¿°¤ £¦­¹ËØåø?WehkdY4¾-LTU`\\P7ý×ËÂ½¿ÅÁÄÌÕêü3GZfdf`S(¤÷4HNYa[O=ðÔÒÔØÒÔëú\v(3?DPcc``Gµ7FJS^WN9/üòðù\t !.9;1KZWZW;ø¾.?GQUSF;*! ).7/!@WWYO-à¡½ó 29CNNMF:/'\" \b&?SUXGÍ·Ý (34631,'úçêú9STU;\rÆ«ÃÖè\fìÚÛÇÕç#;MTG#ñ­§µÄÓÚÙØÚÍÉÄ¼¹¿×ò\b@OR<Ý£¦§©§¨¦ª®±¹ÊØï\v)FPG%øÆ©±ºÑæü0LO:ëÅ ¤­ºÉÜë\a7I9!ýØ¶ ¥ª¯¼Ïåï\t BH7éÅ¬±µÅÔç\f,@6ùÝÁ¥¨¥£¡¬®µ¾Îãò84!ãÉ±¦«¬­«¥ ¦­¯·ÀÉÞôþ'3)öØÃ®²²¯±©££¢£«··ºÃÇÚô\b$$\rõÝÉ±­·¶º¶­¬©°®´ÁÅËÒÜô\t#õæÐ¸ª¸¸º´´²¼ÁÅÆÈÒÏÛö\n%øãÏÀ¦¥¶¿¿¹ÄÑÒÒÑÚÜÜð\rùèÎ¿¬¢»ÑÕÔÔÙÜÝäêù%#\tûâÏÈ³ ³Íèóòû\r+15.\tþôÞÐÆ¯¥·Ëð\a *<<?9+ÿùéÚÈ¼¬ªÂØø1<=IDA4þìàÔÅ²«ªÈè)FI;7#ïçÙÐÄ¶¬¡³ÆÝðöñêôúèÐÊ½´ª";


typedef struct _Pix
{
   int iHeight;
   int iWidth;
} Pix;

const int M=200;
const int N=200;

static char Matrix[M][N];
static char Digit[7][M][N];
static unsigned char DigitResized[3][M][N];
static bool used[M][N];
Pix query[M*N];

static int iTopDigit[7];
static int iBottomDigit[7];
static int iLeftDigit[7];
static int iRightDigit[7];

static int iTopDigitResized[3];
static int iBottomDigitResized[3];
static int iLeftDigitResized[3];
static int iRightDigitResized[3];

static int iMaxLine=0;
static int iMaxStolb=0;

static int Iter=0;
static int iOrder[3]={0,1,2};

bool BoG(char c)
{
	return (c=='@' || c=='%' || c=='#');
}
unsigned char ProcChar(char c)
{
	//'.' - 0 *255/3 ; '%' - 1*255/3; '#' - 2*255/3; '@' - 255
	switch(c)
	{
	case('%'):
		return 85;
		break;
	case('#'):
		return 170;
		break;
	case('@'):
		return 255;
		break;
	};
	return 0;

}
void Get_ii_jj(const int iHeight,const int iWidth,int &ii,int &jj,int iFlag)
{
   switch(iFlag)
   {
   case(1):
      ii=iHeight-1;
      jj=iWidth-1;
      break;
   case(2):
      ii=iHeight-1;
      jj=iWidth;
      break;
   case(3):
      ii=iHeight-1;
      jj=iWidth+1;
      break;
   case(4):
      ii=iHeight;
      jj=iWidth-1;
      break;
   case(5):
      ii=iHeight;
      jj=iWidth+1;
      break;
   case(6):
      ii=iHeight+1;
      jj=iWidth-1;
      break;
   case(7):
      ii=iHeight+1;
      jj=iWidth;
      break;
   case(8):
      ii=iHeight+1;
      jj=iWidth+1;
      break;
   };
}
void get_local_black(int iter, Pix* start)
{
   for(int i=iLeftDigit[iter];i<=iRightDigit[iter];i++)
      for(int j=iTopDigit[iter];j<=iBottomDigit[iter];j++)
		  if (BoG(Digit[iter][j][i]))
         {
            start->iHeight=j;
            start->iWidth=i;
            return ;
         }

	return;
}

bool bSeparated(int iter,int iStolbNo)
{
	bool lused[M][N];
	Pix start;
	get_local_black(iter, &start);

    int t=0;int h=0;

    int ilRightDigit=0;

    query[t++]=start;

    ilRightDigit=max(ilRightDigit,start.iWidth);
   
	lused[start.iHeight][start.iWidth]=1;
   
	while(h<t)
    {
      Pix cur=query[h++];

      for(int iFlag=1;iFlag<=8;iFlag++)
      {
         int ii,jj;
         Get_ii_jj(cur.iHeight,cur.iWidth,ii,jj, iFlag);

		 if (! ((ii>=iTopDigit[iter] && ii<=iBottomDigit[iter]) && (jj>=iLeftDigit[iter] && jj<=iRightDigit[iter]) ))
			 continue;

         if ( BoG(Digit[iter][ii][jj]) && (!lused[ii][jj]))
         {


			lused[ii][jj]=1;
			query[t].iHeight=ii;
			query[t].iWidth=jj;
			++t;

			ilRightDigit=max(ilRightDigit,jj);
			if (ilRightDigit > iStolbNo)
				return false;
         }
      }
   }
	return true;

}
bool bBlackHeight(int iter,int iStolbNo)
{
	for(int i=iTopDigit[iter];i<=iBottomDigit[iter];++i)
		if (Digit[iter][i][iStolbNo] == '@')
			return true;
	return false;
}
void GetNewTop_and_Bottom(int iter, int iTopDigitOld,int iBottomDigitOld)
{
	int iNewTop=M;
	int iNewBottom=0;
	for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
	{		
		for(int i=iTopDigitOld;i<=iBottomDigitOld;i++)
		{
			if (BoG(Digit[iter][i][j]))			
			{
				iNewTop=min(iNewTop,i);
				iNewBottom=max(iNewBottom,i);
			}
		}			
	}
	iTopDigit[iter]=iNewTop;
	iBottomDigit[iter]=iNewBottom;
}
bool bExistBlack(int iter, int iLeftStolb, int iRightStolb)
{
	for(int i=iTopDigit[iter];i<=iBottomDigit[iter];++i)
	for(int j=iLeftStolb; j<=iRightStolb;++j)
		if (Digit[iter][i][j] == '@')
			return true;

	return false;
}
void Del_Possible_Noize(int iter)
{
	int iLine=iTopDigit[iter];
	while(iLine<=iBottomDigit[iter])
	{
		for(;iLine<=iBottomDigit[iter] && !BoG(Digit[iter][iLine][iRightDigit[iter]]);iLine++);
		int iL1=iLine;
		bool bNoize=true;
		for(;iLine<=iBottomDigit[iter] && BoG(Digit[iter][iLine][iRightDigit[iter]]);iLine++)
		{
			if (BoG(Digit[iter][iLine+1][iRightDigit[iter]-1]) || BoG(Digit[iter][iLine][iRightDigit[iter]-1]) || BoG(Digit[iter][iLine-1][iRightDigit[iter]-1]))
				bNoize=false;
		}
		int iL2=iLine-1;
		if (bNoize)
			for(int ii=iL1;ii<=iL2;ii++)
				Digit[iter][ii][iRightDigit[iter]]=0;
	}

}
//false - êîãäà áîëüøå íå÷åãî äåëèòü
bool trySeprate(int iter)
{

	for(int j=iLeftDigit[iter]+1;j<=iRightDigit[iter]-1;j++)
	{
		if (!bBlackHeight(iter,j) && bExistBlack(iter,iLeftDigit[iter],j-1) && bExistBlack(iter,j+1,iRightDigit[iter]))// åùå íàäî äåëèòü òàê, ÷òîá è ñëåâà è ñïðàâà áûëî ÷åðíîå!!!
		{
			for(int i=iTopDigit[iter];i<=iBottomDigit[iter];i++)
			{
				if (Digit[iter][i][j]=='#')
					Digit[iter][i][j]='$';
				else if (Digit[iter][i][j]=='%')
					Digit[iter][i][j]='^';
			}
			if (bSeparated(iter,j))
			{
				for(int jj=j+1;jj<=iRightDigit[iter];jj++)
					for(int ii=iTopDigit[iter];ii<=iBottomDigit[iter];ii++)
						Digit[iter+1][ii][jj]=Digit[iter][ii][jj];
				iRightDigit[iter+1]=iRightDigit[iter];
				iLeftDigit[iter+1]=j+1;
				iRightDigit[iter]=j;
						
				for(int i=iTopDigit[iter];i<=iBottomDigit[iter];i++)
				{
					if (Digit[iter][i][j]=='$')
						Digit[iter][i][j]='#';
					else if (Digit[iter][i][j]=='^')
						Digit[iter][i][j]='%';
				}	

				GetNewTop_and_Bottom(iter+1,iTopDigit[iter],iBottomDigit[iter]);
				GetNewTop_and_Bottom(iter,iTopDigit[iter],iBottomDigit[iter]);
				Del_Possible_Noize(iter);
				Iter++;
				return true;				
			}
			
			for(int i=iTopDigit[iter];i<=iBottomDigit[iter];i++)
			{
				if (Digit[iter][i][j]=='$')
					Digit[iter][i][j]='#';
				else if (Digit[iter][i][j]=='^')
					Digit[iter][i][j]='%';
			}

		}
	}

	return false;
}
void get_first_cur_cur2(int iter,Pix *cur,Pix *cur2)
{
	int iLine=iTopDigit[iter]+(int)(0.6*(iBottomDigit[iter]-iTopDigit[iter]+1));
	for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
		if (BoG(Digit[iter][iLine][j]))
		{
			cur->iWidth=j;
			break;
		}
	
	for(int j=iRightDigit[iter];j>=iLeftDigit[iter];j--)
		if (BoG(Digit[iter][iLine][j]))
		{
			cur2->iWidth=j;
			break;
		}
	cur->iHeight=cur2->iHeight=iLine;
}
void  get_first_under_hole(int iter,Pix *start)
{


   for(int i=iBottomDigit[iter];i>=iTopDigit[iter];i--)	
   for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
	   if (BoG(Digit[iter][i][j])
		    && (Digit[iter][i-1][j] == 0))
         {
            start->iHeight=i;
            start->iWidth=j;
            return ;
         }	
}
int get_first_black_or_grey(Pix *start)
{
   int iBegStolb=0;

   for(int ii=0;ii<Iter;ii++)
	   iBegStolb=max(iBegStolb,iLeftDigit[ii]);
   
   for(int i=iBegStolb;i<iMaxStolb;i++)
      for(int j=0;j<iMaxLine;j++)
		  if ((! used[j][i]) && (BoG(Matrix[j][i])))
         {
            start->iHeight=j;
            start->iWidth=i;
            return 0;
         }
   return 1;
}

bool isNoize(int iNumPx,int iMaxNeigh,bool bHasGrey)
{
	//return ((iNumPx < 10) || (bHasGrey && (iMaxNeigh < 8)))	;	
	return (iNumPx<10);
}

void Resize_Digit(int iter, int iNewWidth)
{
	int new_Height=48;
	double yFactor = (double) (iBottomDigit[iter]-iTopDigit[iter]+1) / new_Height;
	double xFactor=  (double) (iRightDigit[iter]-iLeftDigit[iter]+1) /iNewWidth;

	iLeftDigitResized[iter]=0;
	iRightDigitResized[iter]=iNewWidth-1;
	iTopDigitResized[iter]=0;
	iBottomDigitResized[iter]=new_Height-1;
	
    double  ox, oy, dx1, dy1, dx2, dy2;
    int     ox1, oy1, ox2, oy2;
	
	int ymax = iBottomDigit[iter]-iTopDigit[iter]+1 - 1;
	int xmax = iRightDigit[iter]-iLeftDigit[iter]+1 - 1;

	for ( int y = 0; y < new_Height; y++ )
	{
		oy  = (double) y * yFactor;
		oy1 = (int) oy;
		oy2 = ( oy1 == ymax ) ? oy1 : oy1 + 1;
		dy1 = oy - (double) oy1;
		dy2 = 1.0 - dy1;

		for ( int x = 0; x < iNewWidth; x++ )
		{
			ox  = (double) x * xFactor;
			ox1 = (int) ox;
			ox2 = ( ox1 == xmax ) ? ox1 : ox1 + 1;
			dx1 = ox - (double) ox1;
			dx2 = 1.0 - dx1;

				DigitResized[iter][y][x] = (char)
					
					(dy2 * ( dx2 * ProcChar(Digit[iter][iTopDigit[iter]+oy1][iLeftDigit[iter]+ox1]) + dx1 * ProcChar(Digit[iter][iTopDigit[iter]+oy1][iLeftDigit[iter]+ox2])) +
				
				dy1 * (dx2 * ProcChar(Digit[iter][iTopDigit[iter]+oy2][iLeftDigit[iter]+ox1]) + dx1 * ProcChar( Digit[iter][iTopDigit[iter]+oy2][iLeftDigit[iter]+ox2])));
		}
	}
}
bool Get_Digit()
{
   Pix start;
   if (get_first_black_or_grey(&start))
	   return false;

   int t=0;int h=0;
   int ilTopDigit=M;
   int ilBottomDigit=0;
   int ilLeftDigit=N;
   int ilRightDigit=0;

   query[t++]=start;

   ilTopDigit=min(ilTopDigit,start.iHeight);
   ilBottomDigit=max(ilBottomDigit,start.iHeight);
   ilLeftDigit=min(ilLeftDigit,start.iWidth);
   ilRightDigit=max(ilRightDigit,start.iWidth);
   used[start.iHeight][start.iWidth]=1;
   Digit[Iter][start.iHeight][start.iWidth]=Matrix[start.iHeight][start.iWidth];

   bool bHasGrey=(Matrix[start.iHeight][start.iWidth]!='@');
   int iNumPx=1;
   int iMaxNeigh=0;
  
   while(h<t)
   {
      Pix cur=query[h++];
	  int iNeigh=0;
      for(int iFlag=1;iFlag<=8;iFlag++)
      {
         int ii,jj;
         Get_ii_jj(cur.iHeight,cur.iWidth,ii,jj, iFlag);

		 if (! ((ii>=0 && ii<iMaxLine) && (jj>=0 && jj<iMaxStolb) ))
			 continue;

         if (BoG(Matrix[ii][jj]))
         {
			 iNeigh++;
			 if (Matrix[ii][jj]=='%' || Matrix[ii][jj]=='#')
				 bHasGrey=true;
			 if (! used[ii][jj])
			 {
				used[ii][jj]=1;
				query[t].iHeight=ii;
				query[t].iWidth=jj;
				++t;

				Digit[Iter][ii][jj]=Matrix[ii][jj];
				iNumPx++;
				ilTopDigit=min(ilTopDigit,ii);
				ilBottomDigit=max(ilBottomDigit,ii);
				ilLeftDigit=min(ilLeftDigit,jj);
				ilRightDigit=max(ilRightDigit,jj);
			 }
         }
      }
	  iMaxNeigh=max(iMaxNeigh,iNeigh);

   }

   if (! isNoize(iNumPx,iMaxNeigh,bHasGrey))
   {
	   iLeftDigit[Iter]=ilLeftDigit;
	   iTopDigit[Iter]=ilTopDigit;
	   iBottomDigit[Iter]=ilBottomDigit;
	   iRightDigit[Iter]=ilRightDigit;
	   while(trySeprate(Iter));
	   Iter++;
   }
   else
   {

	   for (int i=ilTopDigit;i<=ilBottomDigit;++i)
	   {
		  for(int j=ilLeftDigit;j<=ilRightDigit;++j)
		  {	   
			  Digit[Iter][i][j]='.';
		  }
	   }
   }
   return true;
}
float formal_cmp_2_Pict(int DigitPattern[M][N],int dH1,int dW1,unsigned char Digit2[M][N],int dH2,int dW2,int iHeightRama,int iWidthRama)
{

	long long int lNevyaz=0;
	for(int i=0;i<iHeightRama;i++)
	{
		for(int j=0;j<iWidthRama;j++)
		{
			lNevyaz+=abs(((int)DigitPattern[i+dH1][j+dW1])-((int)Digit2[i+dH2][j+dW2]));
		}
	}

	return 1-(((float) lNevyaz)/(iHeightRama*iWidthRama*255));
}
float cmp_2_Pict_with_Rama(int DigitPattern[M][N],int iHeight1,int iWidth1,
		unsigned char Digit2[M][N],int iHeight2,int iWidth2, int iHeightRama, int iWidthRama)
{
	float fMax=0;
	int		dH1Best=0;
	int		dH2Best=0;
	int		dW1Best=0;
	int		dW2Best=0;

	for(int dH1=0;dH1+iHeightRama<=iHeight1;dH1++)
	for(int dW1=0;dW1+iWidthRama<=iWidth1;dW1++)
	for(int dH2=0;dH2+iHeightRama<=iHeight2;dH2++)
	for(int dW2=0;dW2+iWidthRama<=iWidth2;dW2++)
	{
		float f=formal_cmp_2_Pict(DigitPattern,dH1,dW1,Digit2,dH2,dW2,iHeightRama,iWidthRama);
		if (fMax<f)
		{
			fMax=f;
			dH1Best=dH1;
			dH2Best=dH2;
			dW1Best=dW1;
			dW2Best=dW2;
		}
	}
	
	return fMax;
}
 float cmp_2_Pict(const char *sPattern,int iHeight1,int iWidth1,
		unsigned char Digit2[M][N],int iHeight2,int iWidth2)
 {
	 float fMax=0;
	 int iHeightRama = iHeight1;
	 int iWidthRama  = iWidth1;

	 int DigitPattern[M][N];
	 for(int i=0;i<iHeight1;i++)
		 for(int j=0;j<iWidth1;j++)
		 {
			 DigitPattern[i][j]=(int)(sPattern[j+iWidth1*i])+128;
		 }

	 	 
     for(int iHeightTemp=iHeightRama;iHeight1-iHeightTemp<=2;iHeightTemp--)
	 for(int iWidthTemp=iWidthRama;iWidth1-iWidthTemp<=4;iWidthTemp--)		
	 {

		 
		 if (max(iHeight1,iHeight2)-iHeightRama>2 || max(iWidth1,iWidth2)-iWidthRama>3)
			 return 0.;

		 float f;
		 f=cmp_2_Pict_with_Rama(DigitPattern,iHeight1,iWidth1,Digit2,iHeight2,iWidth2,iHeightTemp,iWidthTemp);
		 
		 if (fMax<f)
		 {
			 fMax=f;
		 }
	 }
	 
	 return fMax;
 }
 bool Intersect_1_point(int iter, int iLine)
 {
	 bool bWasGrey=false;
	 int iPoints=0;
	 for(int j=iLeftDigit[iter];j<=iRightDigit[iter];++j)
	 {
		 if (!bWasGrey && (BoG(Digit[iter][iLine][j])))
			 bWasGrey=true;
		 if (bWasGrey && (Digit[iter][iLine][j]==0 || Digit[iter][iLine][j]=='.'))
		 {
			 bWasGrey=false;
			 iPoints++;
		 }
	 }
	 if (bWasGrey)
		 iPoints++;
	 return (1 == iPoints);
 }
 //1 - ok, 0 - get next point
 int ok_Regim(int iter,Pix cur2,int Reg)
 {
	 Pix cur3;
	 int iFlag[3];
	 
	 switch(Reg)
	 {
	 case(0):
		 {
			 iFlag[0]=2;iFlag[1]=3;iFlag[2]=5;		
			 break;
		 }
	 case(1):
		 {
			 iFlag[0]=5;iFlag[1]=7;iFlag[2]=8;	
			 break;
		 }
	 case(2):
		 {
			 iFlag[0]=4;iFlag[1]=6;iFlag[2]=7;		
			 break;
		 }
	 case(3):
		 {
			 iFlag[0]=1;iFlag[1]=2;iFlag[2]=4;
			 break;
		 }
	 }

	 
	 for(int iFlagIter=0;iFlagIter<=2;iFlagIter++)
	 {
		 Get_ii_jj(cur2.iHeight,cur2.iWidth,cur3.iHeight,cur3.iWidth,iFlag[iFlagIter]);
		 if (Digit[iter][cur3.iHeight][cur3.iWidth] == 0 || Digit[iter][cur3.iHeight][cur3.iWidth] == '.')
			 
		 {
			 return 1;
		 }
	 }

	 return 0;
 }
  bool Get_Next_Point2(int iter, Pix *cur, bool &bWas4)
 {
	 Pix cur2;
	 int iFlag[3]={4,6,7};
	 int iFlagBreak=1;


	 for(int iFlagIter=(bWas4)?0:1;iFlagIter<=2;iFlagIter++)
	 {

		 Get_ii_jj(cur->iHeight,cur->iWidth,cur2.iHeight,cur2.iWidth,iFlag[iFlagIter]);		 

		 if (BoG(Digit[iter][cur2.iHeight][cur2.iWidth]))
		 {
			 int iOkReg=ok_Regim(iter,cur2,3);			 
			 if (iOkReg == 0)
				 continue;

			 (*cur)=cur2;
			 bWas4=(iFlagIter == 0);
			 return true;
		 }
	 }

	 return false;

 }
  bool Get_Next_Point(int iter, int Reg, Pix *cur, bool &bExPoints)
 {
	 Pix cur2;
	 int iFlag[3];
	 int iFlagBreak;

	 switch(Reg)
	 {
	 case(0):
		 {
			 iFlag[0]=2;iFlag[1]=1;iFlag[2]=4;	
			 iFlagBreak=3;
			 break;
		 }
	 case(1):
		 {
			 iFlag[0]=5;iFlag[1]=3;iFlag[2]=2;		
			 iFlagBreak=8;
			 break;
		 }
	 case(2):
		 {
			 iFlag[0]=7;iFlag[1]=8;iFlag[2]=5;		
			 iFlagBreak=6;
			 break;
		 }
	 case(3):
		 {
			 iFlag[0]=4;iFlag[1]=6;iFlag[2]=7;
			 iFlagBreak=1;
			 break;
		 }
	 }
	
	 if (bExPoints)
	 {
		 Get_ii_jj(cur->iHeight,cur->iWidth,cur2.iHeight,cur2.iWidth,iFlagBreak);
		 if (BoG(Digit[iter][cur2.iHeight][cur2.iWidth]))
			 return false;
	 }


	 for(int iFlagIter=0;iFlagIter<=2;iFlagIter++)
	 {
		 Get_ii_jj(cur->iHeight,cur->iWidth,cur2.iHeight,cur2.iWidth,iFlag[iFlagIter]);		 

		 if (BoG(Digit[iter][cur2.iHeight][cur2.iWidth]))
		 {
			 int iOkReg=ok_Regim(iter,cur2,Reg);			 
			 if (iOkReg == 0)
				 continue;

			 (*cur)=cur2;
			 bExPoints=true;
			 return true;
		 }
	 }

	 return false;

 }
 int VERSUS_12_Cur(int iter,Pix cur,Pix cur2)
 {	
	 int iMaxLeft=0;
	 int iMaxRight=0;
	 for(int i=iBottomDigit[iter];i>=cur.iHeight;i--)
	 for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
	 {
		 if (BoG(Digit[iter][i][j]))
		 {
			 iMaxLeft=max(iMaxLeft,cur.iWidth-j);
			 iMaxRight=max(iMaxRight,j-cur2.iWidth);
		 }
	 }
	 return (iMaxRight-iMaxLeft>=5)?2:1;
 }
 void Get_F_L_Lin(int iter,int *iFLin,int *iLLin)
 {
	 int iL2=iTopDigit[iter]+((int)(0.6*(iBottomDigit[iter]-iTopDigit[iter]+1)));

	 int iMaxRight=0;

	 for(int i=iTopDigit[iter];i<=iL2;i++)
	 {
		 int j;
		 for(j=iRightDigit[iter];j>=iLeftDigit[iter];j--)
		 {
			 if (BoG(Digit[iter][i][j]))
				 break;
		 }
		 if (iMaxRight<j)
		 {
			 iMaxRight=j;
			 (*iFLin)=i;
		 }
	 }
	 Pix cur;
	 cur.iHeight=iL2;
	 for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
		 if (BoG(Digit[iter][iL2][j]))
		 {
			 cur.iWidth=j;
			 break;
		 }
   do
   {
	   if (BoG(Digit[iter][cur.iHeight-1][cur.iWidth]))
	   {
		   cur.iHeight--;
	   }
	   else if (BoG(Digit[iter][cur.iHeight-1][cur.iWidth+1]))
	   {
		   cur.iHeight--;
		   cur.iWidth++;
	   }
	   else if (BoG(Digit[iter][cur.iHeight-1][cur.iWidth+2]))
	   {
		   cur.iHeight--;
		   cur.iWidth+=2;
	   }
	   else
		   break;
   }while(!(BoG(Digit[iter][cur.iHeight-1][cur.iWidth-1])));
   
   (*iLLin)=cur.iHeight-1;

 }
 int Width_Line(int iter,int iLine)
 {
	 int iRes=0;
	 for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
		 if (BoG(Digit[iter][iLine][j]))
			 iRes++;
	 return iRes;
	 
 }
 int VERSUS_17(int iter)
 {
	 int iFLin,iLLin;
	 Get_F_L_Lin(iter,&iFLin,&iLLin);

	 int iW1=Width_Line(iter,iFLin);
	 for(int iLine=iFLin;iLine<=iLLin;iLine++)
	 {
		 int iWt=Width_Line(iter,iLine);
		 if (!(iWt/(double) iW1 < 1.4 && 
			 iWt/(double)(iBottomDigit[iter]-iTopDigit[iter]+1)>0.4))
			 return 1;
	 }

	 return 7;
 }
 int VERSUS_12(int iter)
 {
   Pix cur,cur2;
   get_first_cur_cur2(iter,&cur,&cur2);


   int iPalWidths;
   bool bWas4=false;
   
   do
   {
	   if (BoG(Digit[iter][cur2.iHeight+1][cur2.iWidth+1]))
	   {
		   cur2.iHeight++;
		   cur2.iWidth++;
	   }
	   else if (BoG(Digit[iter][cur2.iHeight+1][cur2.iWidth]))
		   cur2.iHeight++;
	   else if (BoG(Digit[iter][cur2.iHeight+1][cur2.iWidth-1]))
	   {
		   cur2.iHeight++;
		   cur2.iWidth--;
	   }
	   else if (BoG(Digit[iter][cur2.iHeight+1][cur2.iWidth-2]))
	   {
		   cur2.iHeight++;
		   cur2.iWidth-=2;
	   }
	   else
		   break;
   }while(!(BoG(Digit[iter][cur2.iHeight][cur2.iWidth+1])));

   for(int Reg=3;Reg<=3;Reg++)
   {
	   while(Get_Next_Point2(iter,&cur,bWas4))
	   {
		   if (cur.iHeight == cur2.iHeight)
			   iPalWidths=cur2.iWidth-cur.iWidth;
	   }
   }
   if (bWas4)
	   cur.iWidth++;

   cur2.iHeight=cur.iHeight;
   cur2.iWidth=cur.iWidth+iPalWidths;
   
   return VERSUS_12_Cur(iter,cur,cur2);
 }
 int   VERSUS_09(int iter)
 {
   Pix start,cur;
   get_first_under_hole(iter,&start);
   int iStartReg=0;

   cur=start;

   for(int ii=0;ii<=3;ii++)
   {
	   bool bExPoints=false;
	   int Reg=(iStartReg+ii)%4;
	   while(Get_Next_Point(iter,Reg,&cur,bExPoints))
	   {
		   if (start.iHeight==cur.iHeight && start.iWidth == cur.iWidth ||
			   cur.iHeight <=iTopDigit[iter]+(int)(0.2*(iBottomDigit[iter]-iTopDigit[iter]+1)))
			   return 0;
	   }
	   if (!bExPoints)
		   return 9;
   }

   return 9;  
 }
 int VERSUS_56(int iter)
 {
   Pix start,cur;
   get_first_under_hole(iter,&start);
   int iStartReg=0;

   cur=start;

   for(int ii=0;ii<=3;ii++)
   {
	   bool bExPoints=false;
	   int Reg=(iStartReg+ii)%4;
	   while(Get_Next_Point(iter,Reg,&cur,bExPoints))
	   {
		   if (start.iHeight==cur.iHeight && start.iWidth == cur.iWidth ||
			   cur.iHeight <=iTopDigit[iter]+(int)(0.2*(iBottomDigit[iter]-iTopDigit[iter]+1)))
			   return 6;
	   }
	   if (!bExPoints)
		   return 5;
   }

   return 5;  
 }
 int VERSUS_06(int iter)
 {
	 int iUpStr=(int)((iBottomDigit[iter]-iTopDigit[iter]+1)*0.25)+iTopDigit[iter];
	 int iDownStr=(int)((iBottomDigit[iter]-iTopDigit[iter]+1)*0.65)+iTopDigit[iter];

	 for(int iLine=iUpStr;iLine<=iDownStr;++iLine)
	 {
		 if (Intersect_1_point(iter,iLine))
			 return 6;
	 }

	 return 0;
 }
int Get_Final_Number(int iter)
{
   float f,fM2=0,fM1=0;
   int iBD1=0,iBD2=0;

   for(int iDigit=0;iDigit<=9;iDigit++)
   {

		   int iWidth;
		   const char *sArr;
		   switch(iDigit)
		   {
		   case(0):				   
			   iWidth=iE00;					  
			   sArr=Arr00;				   
			   break;			   
		   case(1):
			   iWidth=iE01;					   
			   sArr=Arr01;
			   break;			   
		   case(2):					   
			   iWidth=iE02;					   
			   sArr=Arr02;				     
			   break;
		   case(3):					   
			   iWidth=iE03;					   
			   sArr=Arr03;			   
			   break;
		   case(4):					   
			   iWidth=iE04;					   
			   sArr=Arr04;
			   break;
		   case(5):					   
			   iWidth=iE05;					   
			   sArr=Arr05;
			   break;

		   case(6):
			   iWidth=iE06;					   
			   sArr=Arr06;
			   break;
		   case(7):
			   iWidth=iE07;					   
			   sArr=Arr07;
			   break;
		   case(8):
			   iWidth=iE08;					   
			   sArr=Arr08;
			   break;
		   case(9):
			   iWidth=iE09;					   
			   sArr=Arr09;
			   break;

		   };
		  					  
		   Resize_Digit(iter,iWidth);
		   f=cmp_2_Pict(sArr,48,iWidth,DigitResized[iter],48,iWidth);
		   //printf("DIGIT=%d f=%f\n",iDigit,f); 
	   
	   //printf("\n");
	   
	   if (fM1<f)
	   {
		   fM2=fM1;
		   iBD2=iBD1;
		   fM1=f;
		   iBD1=iDigit;
	   }
	   else if (fM2<f)
	   {
		   fM2=f;
		   iBD2=iDigit;
	   }
   }
   if (min(iBD1,iBD2)==0 && max(iBD1,iBD2)==6)
	   return VERSUS_06(iter);
   else if (min(iBD1,iBD2)==5 && max(iBD1,iBD2)==6)
	   return VERSUS_56(iter);
   else if (min(iBD1,iBD2)==0 && max(iBD1,iBD2)==9)
	   return VERSUS_09(iter);
   else if (min(iBD1,iBD2)==1 && max(iBD1,iBD2)==2)
	   return VERSUS_12(iter);
   else if (min(iBD1,iBD2)==1 && max(iBD1,iBD2)==7)
	   return VERSUS_17(iter);
   else	
	   return iBD1;
}
int main()
{
   int iStolb=0;
   char c;

   while((c=fgetc(stdin))!=EOF)
   {
      if (c == '\n')
      {
         iMaxLine++;
         iMaxStolb=iStolb;
         iStolb=0;
      }
      else
      {
         Matrix[iMaxLine][iStolb++]=c;
      }
   }
   iMaxLine++;

   
   while(Get_Digit());

   int iRes=0;
   
   for(int iPos=0;iPos<Iter;iPos++)
   {   
	   int iRes2=Get_Final_Number(iOrder[iPos]);
	   iRes=iRes*10+iRes2;
   }

   printf("%d",iRes);
  

   return 0;
}