#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "header.h"

using namespace std;
int iE00 = 33;
const int N0=124;


const char Arr00[]=
"€€€€ƒ„„„„„†Ä,Q`WTPIºŸ’‹Œ†„€€€€ƒ„„„„„Š®\bDS_`][]^hgaJõ¬—•Œ‡€€€ƒ„„„„„é9MWaJ6/,.:WjiiVÙª£–‹‡€„„„„„„«>ISW=! -3Fafga5ğ¶¤—„„„„„…°>NRN5\r\f\f\b\n9\\gi`8ïµ¢•‡„„„…¦÷;LU[<\n÷áäßİØëA_ijd.à­¢”‹„„„•ß2FMR;şäÚÏÅÁ¹¹ÃØï\"HYgi`$Ò¤˜‹„„…À\"DOQM+ıßÔÌÁº±©«®¶Íî-O^gjUµ¡„„–öAQWL5\våÕË¿·®­¨¥¥­´È\aA]dfd8Ø¤“„‡Á,KTWF!îÛĞÃ¹®¨¦¦¦¤¥¨¼ŞO^nlW­“„ŒñAQ\\U?\nİÒÈÁ¯¦£ “–š£©°ÇD]hmn6Âš„¥O[^T-ûßË½¸¦ £ŸŒ”Ÿ¤¯Ãå)YhpqWé„Ø=P_]I'ñÚÄ¶´¢œ›‹Œ™¥¬½ÙMhosn£‡\vF[e`DçÒ½±°¢—‡‡ˆ—£ª»ÒÿEcrwu@§‹&O]gWDàÌº¯© ‡‡‡ˆ‹– ©±Ëò:Zpvv`Ã‹D\\acY6ıàÈ²¬§š‹‡‡‡ˆ‹™Ÿ­Èæ#Pkswoã½K]eaW1ôÛÁ²¬¢”‹‹‡‡ˆ•œ¢ªÃÜ\fJhvxpşşR_ifSæ×Á¯©‘ˆ‹‹‹Œ‹“› ª¾ÑIexzt0,ZfigRãÕÁ²ª™‹ˆ…„…ˆ•› ª½ÏıEbxzvc>[gpfTáÕÁ°£˜‹†„„‰‘•› ªÁÏüAdxvtjP_gsgR\nİË¸¬£˜ˆƒ…‡ˆ˜› ªÁËù<duuqjWfkvjR\nßÌ·§Ÿ•†€…‡‡ˆ˜ ª¾Êü;_sukf[fqvjO\tİË´§Ÿ†„‡‡‡ˆŒ–§½Ğ?`sukf_gxzjM\bÜÄ±¤Ÿˆ„‡‡‡ˆŒ–›ª½Ğ<`ouhb[jxzmN\bÜÆµ¥ “ˆ„‡‡‡ˆŒ’•ª½ØB`nmd_[q{zmQ\bÙÅ¶«’ˆ„„„‡†ˆ•­½ÖA_opd_bw{zmQ\aÔÆµ«’‹†„„‚ƒ‡•Ÿ®ÁÖA^god_bw{zjPÑÉ³§’‹ˆ…‚‚…‡•Ÿ°Ä×AZgicTb{{zkV\bÓÇ³§’‹ˆ†„„…‡—£´ÉÚ\bAVegZFbz{znV\tÕÃ±¤’‰„„„„…‡—£¶ÊÚAUggY*,v{zr]ÚÈ³¤‡„„„„…‡š¨¶Ìà>WdcTírzwq]\"ãÊ¶¥‡„„„„…‡‘œ«¾Ôë#C[b\\E´Ör{wtc2ìÌ¶¢–‡„„„„…‰˜¢°ÄÜô&G[a[>‘½dzyufGÏ·¥¡˜‡„„„„…Œš¦¶ÇŞ.L]]Q\"¤Dv{vjNÎ½ª£˜‹„„„„‰’œª³Ëå8S_[P…¤pyvjVÙÃ®¥ ˆ‡‡‹”¡¬¼Ñç=WZYBÑ„¤óWysn^-îÈµ¥ “ˆŠ‹‘š¦¯ÇÓñ JWXPŸ„™Á2rtqbM\vÎ¶ª¤˜‹”¡ªµÇÔ1JUWEòŒ„™¥YspcQãÃ²©§¢˜–˜¥¨²ÅÎà:HMN(¾…„‹¤Ü7qsf_A\bÎ½·ª¤£¢¢¥«½ÃÖ-EQQDø—„„‹š°úStpcS*òÍ¾²§¦¦¤±ºÄĞğ<HMH%¸…„„„–¤Ğ$`pnbKóÖÉ´²²²ÀÏßø,GLF=ä“„„„„‹—§ß5fsmcB\aäÏÌÏÓÛñ\b1LLJEù¤…„„„„‹‘¶ñ:jxnd=\f\vş\r+>NOD¦†„„„„„„‹– ´ğ=jtvlF3!7KRPF£†„„„„„€ƒ‡‹•Ÿ­Ş&cstw`D;2.4BNUT?æœ„„„„„ƒ€€€ƒ‡Š“š ±ÿSosska[[S^\\I®‡„„„„„ƒ€€€€€ƒ„Š‹‘œ ¢¹\fWb\\Y]Y6ÅŒ‡…„„„„„ƒ€€€";
int iE01 = 23;
const int N1=126;


const char Arr01[]=
"€„„„ˆ‰‘˜¡£´ÓîçÁÂËÓİÆÍˆŒ’””’—¡¨¹Òåıûêõı÷õíÆ”™™˜¨«ºÌİ.*$\núûõéÏ‘™«¶ÉÚè+-:AE;\rşıóéÚ ²½ÁÉÙéú/1CHS\\?ş÷ïäÓ±¹½¹Ìåö\r#1DGXrbB!ş÷ïÛÆµÅËÕäíı\r#8H[msgBøèĞÂ¹ËÓ×âîó\b';VelziEøàÎ½½ÈÙİÛçïø'?V`kxf=öÚÅµÉÌÌËÕàôı<L^hqe?úåÕÃ±ÅÈÍàêòõı\"0ETim`AòãÏÂ­±ÊĞÓÕãèó\f*CYdbY@ğàÌ½©½ÌÏÓ×âæè*@NY^W<ìßÌ»¥µ½ÁÇÊÒİÛö8K[`Y;çÔÄ¸¥±´½ÁÄÅÅÍò5IV`Y;\fşåÒÄ¸¥­­··´µºÂé4H[`W5\rúäÒÄ¸¥¤¡¡ŸŸ¥±¿ã8H]aW3\t÷ŞÉÂ·¥˜•”˜›¡±¹à:M_aU-÷ŞÉÁ´¥””˜›Ÿ¨°â=NYYS.ñ×ÉÁ´¡””””•£²äAP[YQ,ñÕÇ¿´¡Œ‹•Ÿ­è BP[\\O(ìÑÇ¿´¡ŒŠŠ‹‘œ¶ï\"DPWZM(ìÎÆ¼´¡Œˆˆˆ‹ ¾ò#HPWXK%ıêÎÇ¿´¡„ˆˆˆˆ£Áò#DNUVJ#øèÌÅ¿´¡ˆˆˆ†‡«Æù%DHYZH!öãÌÃ¼´¡ˆˆ‡„‡•°Çø%BIUTFóáÌÃ¼´¡„„„„Š—°Êø#@IUTFğàÊÃ»°¡„„„…Ÿ´Ïú#>IUQEğàÊÃ»°¡„„„…¢¹Ïú#>LPRBíàÊÃ»°¡„„„‹¢¹Ñû!;LNP?íİÊÃ¹ª „„„Œš«»Ñş!;JLL:êİÈÁ¹ª „„ˆš«¿Ñş=JLL:êİÈÁ¹ª „„‹¬ÀÔş@CJK:æİÈÁ¹ª „„Œ• ¬ÀÒú>AJG6æİÈÁ¹«¤„ˆ™¦®ÃÒú;AJG6æÛÅÁ¹«¤„Œ›¦²ÃÑ÷!:CHG6\væÛÅÁ¹«¤„Œ“¦µÂÑö7AHG4\tæÛÅÁ¶¨¤ˆ‘›§¬¹ÂÎö2?DC4\fæŞÎÅº®­’¡¨¯¹ÂÊô2?DC6æŞÎÅ¼¯¨•¡¨²¼ÃÊö2?DA0æŞÑÉ½­¨«­²»ÃÎõ-=A@*çŞÎÈ·­¨”¡¬±·ÀÆĞó09@A0äÙÍÌÁ¶­œ¨°·¾ÄÎ×ü!39@>3ôâØÔÇº±­½ÁÄÉÓİğ(75>>@+õíäÕÉÅ¤ÄÅÈÍØâù,35@A=5ÿóïæÙÎ±ÄØİŞçğ\v(987<7<9+ü÷ïáÕÅÚñû\b'.5622--;73%\nöÉéú\v&('!$%(4::6.)";
int iE02 = 32;
const int N2=122;


const char Arr02[]=
"€ƒƒ„‡‡‡‰•¡»ø/NXafg[=ÿ»¦˜ƒƒƒ€€€€ƒ„‡Š™¨½ğ,TW\\cgimlrwjV6ü½¤†ƒƒ€€ƒ†™ª¹Ş\"LYXSTTVT^ajhptgU-ö¶šŠƒƒ€ƒ“¡­Î\b6QOF@C7324@DRYdipiT4\tË„€‡­Ë\t9JDA9)!(0146L_kojU3\aĞœŠ„‡¦Ä÷1MA0/÷îéêçí*5CXenhO1Á•„´Û63%ñäÚÔÇÂÁÆÏÚí*@QdjY@î£ˆš»ò'-#\nñáÖÊÆ¿¶µ°ºÂÔè*FZjgQ9\rÒÈû#øåÕÃºº®§©¦©³¾Õí\n+NdnX<ğšÉ\fşîÑË¿¸±¤šœ¤°Êà÷@XnaH8ı¸—ÜıñÙÃ¼´®¥™——«½Íê+KleP8\fÜ‘ç\r\t\tÿôÎ¶¶¯§¡—‘“”—¦ºËá&DjjX>âßøéÇ¼¹© ›—“›Ÿ´ÅÚ >ijU:éÆêóìä×Äºµ´§šš’ŠšŸ±ÅÜÿ\"BjkU:éš²×ŞÙÛÓÈ¼·¯¦œ™’Šˆ˜¢±Æá\b%?jiQ3ßš®ÁËÓÒÌÇ¿¸³¢œ—‡‡•¤³Éå\a%GjjN)\bÖ—¨®½¿ÀÂ»¹®¤›”‘ŠŠ—¥±Ìï\n+KjeKûÉ”¡¤¯²²®¯¬£—“‘Šš¨µÔú>ThW<\bäªšœš¤¥¥¥¤ ——“’•«Ãæ)C]bS(üÎ“—š˜™œ£Ÿ——–‹‹’‘œ§µÚõ<LV[AñÅ‡–”–’”š—””’’“•’Ÿ­Åí\n)MSZI%øĞ¥ˆƒ““•”””–————•“–š®¸Úş GQZX=\nàÄ•…ƒŠ“’‘“””–“•“š«»Óú4JPYEèÉ „ƒ‡Œ‹ŠŠŠ––¨ÁÕé\bHSWF#úÏ¯•ˆƒ†‡ŠŠ‹Š‹’ »Öç\a:LRH*×°˜Œ‡‡ƒ„ˆŠŠŠŠŠŠŒœº×ã,KPA,Ú´š‡€‡ƒƒ„‡‰ŠŠŒ’•º×æû)GO@'ß¶¡“…ƒ€ƒƒƒƒ„‡„…ŒŠ—±Íâò+>E;&\rİ·Ÿ‘…ƒƒ€ƒƒƒƒƒ„…ŠŒ‘˜¨Èßó\n\"#83 è½œ“‰„ƒ‚€€ƒƒƒƒƒ…ˆ”˜ªÅÚì\b3.\réÂ”‰„ƒƒ‚€€ƒƒƒƒ…‰Œ”¯ÃÒå$4/ê¿›“‰‡„ƒƒ‚€€ƒƒƒ†‰•­¾Ñéü!!)\vêÀ›”‡…‡‡…„†ƒƒƒ†ˆŠ”©»Êâô%\"\v\bèÁ‘Š‡‡…‡‡…‡‰„ƒƒ†ˆ“¢¤µÊâò+!\n\tã¼‘‹‰‡‡ˆŠ‰‡ŠŠƒ†ˆŒ›¦µÊáö'#\n\fç¸Ÿ‘Š‡‡Œ‘“ššƒ‡ ¨»Ğè)%'\tæ·™‘Œ‹ŒŒ”“˜œ£§ƒ‹–¥¼Ôèô\"(+çÃ¤ œš™—”‘’’–Ÿ¤±¸¿‡‘§½Ğç÷*-!\fàÆ¬©¦¤¢¡ Ÿ¡¤¦ª´¸ÈÙÃ‘›¸Ïì'/!áË¶µ³³µµ··µ³°µÃÈÎÕäÊ‘«Éğ\f!#1A,íÔÆÃÁ½½Â¿ÁÁ¿ÀÄÍÑÌÕãã½¡¿ì-6L:'úßÓĞÎÍÌÍÏÏÑÔÔÏÓàåçïıì¿«á0EWH4\vùïíïíêêêîññòôôú\t\bíÍÉ\t0G][G.,)),,+,,,*&)/-0//-2. \nàã2I`da[WTTTTWWWWTTTX[[YWXSPOC\"òû%HbfjhhikkkknlnkkfeghfededbO4 õş8Z__^^_`aba`^`aaadhfbaa_ZZTC2òBGIKMLFIJFDJMMMOTUWTVVMLKGB9\"\rè\"/*0+0/131/,-03249=98;6844.'\"ÿØ";
int iE03 = 31;
const int N3=124;


const char Arr03[]=
"ƒŒ‹‘˜¨»×ö&KTT[`_SÙºµ³©£›””‘Š‡›¨ÁÓâúMX^`dfjkpvwsY(áÂ¸¬¤¡–‹Š›²ÃİöDRZORRUUT`elrwytNÖ¿°£šŠ«ÂÑø%?NNGI>7234:E[chhrjR ßÁ¨—„‡®Êí!:G>1# %5FT\\^hdTÚº›‘ƒ®Õ,8/\füçãÛÜàáëû(7CLXmfIÀ¦•‡«Ò(-÷êàÖÉÅ··¹»ÈØô7DX_gX4Ù±™Š©åùàÏÍ·¯±®«®¯·¼Ïí?GXb_Cö½–Š­åûãÙÑ¹®¨©©¦¤¢§«¸×ü4EQ`]H!ĞŸŠ°ãûïçİĞÁ¯¢ššš™™š¯Íë;G\\ZN1ÔŸ±ŞçâØÒÍÂªœ™š››™˜ ´Ëê\v0GXYI-Ò™´ÕØĞĞÇ¹¬Ÿ™›”™š••š¦¯Ëæ\a0GXPA*Ì™Šº¼¸½¹®¢˜”’—¢©³Êç\n.ITJ;Â•Š‘¡¡¥¥©¦š•˜Š’˜ªª³¸Òò9KM>4Á•Š‡“—˜š˜—‘’”–¡ª¨°»Şÿ>MG:\"ø²‹€€†‡†ŠŒŠ‘–›¡¥ª³Áí(IG?*Ó¥‹€€€„†ˆŠ‰–™œ¥¤ª·¿Ü @F;.şµ•Š€€€ƒ„Œ””“’“—š¥¬²½ÁÔú1C;(\tÖ§ƒ€€€‚Š“‘› ¥«µ¾ÁÉç3@3Ü¯—Œ‡ƒƒ‚…‰“˜¢°³·¼ĞÜãı7FI>3+ä¼Ÿˆ‡ƒƒƒ…‹”§¬¸Ñåÿ%1BLJQSF;ùÆ©’Š‰„ƒƒƒ…—§ÃÏß÷6HSX_chaM1+á¼¨œ‹„ƒƒƒ†Œœ²ÆÛğ\"<HTXX\\[]K7şñİº¤œ‘…ƒƒƒ†‹–§¹Èå*,,/8AL_gcY>\vöâÄ¤“ƒƒƒ†‹“¬¸ÃÕêùÿ\t#8Rjmh]?\tå½‘ƒƒƒƒ‰–¦¬µ½À¾ÆÎØàø)DcmoqSã±”ƒƒƒƒ…‡‡Œ“•—œŸ¬¿Ôæÿ*H`lvuUÊ˜ƒƒƒ†‰‰‡‡ŠŠŠŒ–™Ÿ³Øü!GeswnJì¨ƒ„‡‡‰ŠŒŒŠŠ‡‡‡‰Š‹”š¡³Ğ\t7\\lwrb:¾ƒ‡‡ˆŠŠŒŒŠˆ†ƒ†‰Š‹–›«¼âFgqyiNÜƒ‡ˆ’’‰ƒƒƒ†‰Š‹”™¦·Ò<gnzoWƒ‹“›Ÿ˜•‰‡†‰ŠŠ‹‘œ¤±Íì^npp`H›§­­¦—“ŒŠ‰…†ŠŠ‹‘Ÿ¥¯Êãainp\\K¡¥¬´´«Ÿš•ŠŠŠŠ‹‡Š‹”Ÿ¥¯Ëå\\gnp]K§¾ÆÈÄ¾®“‰ŠŒŠŒŠ‹š¢¥´Ğì\"^gllWDÎãèåàÏ¸©œŒŒ‹ŠŠ“›¢¥´ÖìWgkfR1ØùóğçØË³¢‘‹Š‰ŠŠ’—¢¬½Üó[fdZFìıõíâÑ¹¦™”ŒŒ”š¡ªµÊßCaeeN2çÒ\fòæØ¼ª¢˜•Œ•— ª²ÁÕïSca^>Ü\vïæÔÂ²¥Ÿš—›šœ¢§±ÁÏç9[_`K)ú‡Õ÷èßË¿°¨£¡›¡¤ª³ÄÏä\a/M\\]U4¹„ÈêÙËÃº¶µ²·»ÀÉÓí\b$L]\\S>èƒÎ(@4îìİÓÕÒÕØÚçğ\b+DZ`VC÷„ƒÒõ!4L:'\aÿüüÿ\r4N[ZU;õ¦ˆƒƒÎç\"7UN=-.'0OQZVC'ê ‰ƒƒ€»Ñí=Zc[J>69>@BJS[YI/ş¾‘†ƒƒƒ€®ÄÜø4Gemjkh`\\[[XJ+şÆ’†ƒƒƒƒ€€ƒ“›¤µÔåı)C\\he_G*íÁ’…ƒƒƒƒƒ€€€€";
int iE04 = 34;
const int N4=124;


const char Arr04[]=
"€€€€€€€ƒƒ„Š™šš¨§±ÁĞáú\fëĞª–”‘‡€€€€‚ƒƒ‚€€Œ•›¡¬ª²¾Òã\t()4-\n×°Ÿ˜–“‡€€€‚ƒƒ‚€€€†šŸ¤­±½Ïà\n089A4Ş¶£š–•Š€ƒƒƒ€€€€„Š–› ©±¸Ìàø-8?AF;â»¥˜–•Š€ƒƒƒ€€ƒ…‘™›¤­³ÉÛ÷9?AGK9æ½§š–“‡ƒƒƒ€€€‚†Œ“›¢ª°¾Şî49HKJL;æ½¥˜—‰ƒƒƒ€€‚†‹’™œ§°¹Ğè\n,7=BJLO?å½¤˜–‰‰ƒƒƒ€ƒƒ‹“œ¤­´Êå(6?@EKNRAåº ššƒƒƒƒƒ†— ©³ÆÜö2?/5@OSS;äº¥Š€ƒƒƒƒƒƒ‹‘œ¢°¾Ğô*80 )9SRM8å½§‡€ƒƒƒ……†Œ’š¬¸Èæ\t)55\n<SPN=é¾¤“‰‰„€€€„††‹• ³ÇÛ'-;ı9QQLAæ»¡‘‰„ƒ€€€‚ƒ†Œ˜´¿Ìñ.+\"üìì:OQTAè½¢˜‹†€€‚ƒƒ‰Œ’§¹Ìò,-\níÒà\r9LWWEæ» •‹‰ƒ€€‚ƒ†‰¢±ÄÙ\r.3#ñ×ÇÜ\r5KWYGæ¸ŸŠ†ƒ€€‚ƒ‰—§ÁÒ'0)éÔ½ÅÚ\t2UZ\\Jç¸ŸŠ†ƒ€ƒƒ†‰¡·Íó(5üÛ¹¼ÀÚ\v6U\\]Gà¶›††ƒ€ƒ††Œœ°Æå+7(Ş¹«±»Ö\f;U\\]Fßµš††ƒ€ƒ†‰¢½Õ\n\"1,îÈ¦¥®·ØC]d^Iß´–‹†ƒƒ€††Œ˜³Éú+*÷Ğ®›¤¯ºÜEah`Iİ²•‰†ƒƒƒ†Œ•ªÃë+4)Ü¶Ÿ”¢ª»æHah_Eİ°•‰†ƒƒ‰‰Ÿ½á\r+7-ğÈ¨–’œª½çG_bZ@\rÙ¬”Œ‰‡‰‰”³Ğú&3*$ùÒ¯˜“™ªÄê\"I_`Y>\nÙ­˜‰‰‡‰“¦Àñ4=3Ü½œ”‘Š—®Æí#I\\^[BÜ°–Œ›¾İ+8/!óĞ®¡•“¦¹Ëğ#I\\__Eİ° “”™™ªØú(2.'\tŞÁ¬¦Ÿ¡ª½Ğğ$L_b`Hä¶¨Ÿš›“£½î 4>6ğÙ¾·³®¬ª·ÌÜö)NcgaP#ïÅ´¨¥Ÿœ¬Ş\b7NF9ñĞËÄÁÁ¿½ËŞí.NcidV,ûÖÈ½ºÂ¼Åø6OXN5\vïèãŞİÛÙÙæöı9Xjoma:íà×İİÓë D^aR5&\r\v\a\a\n 1M^ijh_G#\tüşòô2LVOA-\r\v'*;Q`gbdV;!\vÿşì\a/EE:/\"!-07ET[a]]P7%\bïû/.,*%$\"!!!&,8@GKXZ\\YYK4*$\nøû\"!!!&*,:>GK[ab]YI6*%\aøâôõøúõ÷úøøöóü\t!.EX_\\T=øöóêäÈŞââßŞŞŞŞŞŞâæêìö\t7QZXS9óëßİ×ÕÒ¹ºÃÅÅÅÅÅÅÅÅÈÌÓÖÚçè÷\v.KWXR5ÛÏÆÄÂÃÂ™œœ£££££££§©®¹ºÈÇÚôDSWO0ÿË®¢Ÿ¡¦£““““’“”— ª¬¶¿ÖñFOOI(÷Å¦•“”˜–†‡‰‰‰‰‰‰‰‰’– §©°¹ÑêALKE'÷Å¤‘ƒƒƒƒƒƒƒƒƒ†‹‘¡¢²ºÓê@LJA(ùÅ¤‘‹‡Šƒƒƒƒƒƒƒƒƒ‰Œ‘¡¡­ºÓê@LH=(üÆ¤‘‹‰Š‰€€€€€€€€€…‰Œ– ¡£¯ÅÙğ?JJ@(Îª•‰††€€€€€€€€ƒˆ‰˜  ¤²ÊÙò=JJ@*Ô­™†††€€€€€€€€ƒ…Š˜Ÿ£©´Èàş#>LHD0Õµ”Š‰†€€€€€€€€ƒ…Š“£¨­¼Øî\">HA:,æ¼§–Œ‰€€€€€€€€ƒ…Šš§´¹ÄÖèò0?>;2èÉ±¦œ–“€€€€€‚ƒƒƒ†¦­ÂÍÖëïõ\a';42(õÙ¾³¥œ™";
int iE05 = 29;
const int N5=124;


const char Arr05[]=
"ƒ“¡½Úê\a\t\f!&#\nïÊ‡–¥¿ä**09:8<==>@<974>IQJ9¾ƒ–«Èù7AIQ[\\^aaaa`^_aahjj\\=÷®ƒ–¯Ì,CGL[a^ceaaaa`^^^bh`Q*Ü ƒ™¯Í*<<EORX\\PMMMMMMQW\\`WGÈŸ‡™¯Ï\f1;/*0**.*!!#&&'-0/+ıÚ®Š™¹İ7>&ıóñèãåçèêéêíáÑÃ²•‡Šœºê92#ïãÙÑËÌÌÌÌÍËÆÃ½¬¥šŒ„ŠŸ»ç8/\aùåÙÒËÂÂ¿¼¸¶³°ªœ˜™‘†€‡Ÿ»ì1!\féÖÈÀ±ª¥¤¤¢ŸŸœ›—–—†€‡ ¿ï#7&æÍ¾²¤œ”’‘ŒŠŠ‰ˆƒ€‡£À÷&<+åÎ½´£—–”’‹ŠŠŠŠ‰ˆƒ€‡£Ãû):'üİË¹«š’‘‹‹Œˆ‡†‡ƒ€‡§È07ôÚÃ·­ ™—•™•”“‡ƒ€€€‡§Ì\f6?ùèĞÂ·¦£¡¡š–””‘‹ˆ„€€€ƒ§Ï8C%ïÒÊ»¶ÁÀÂ¾¸¶¢–”‘‘ŒŠ…€€ƒ«Ï;G+\nõâáİäçíêêçİÎ·¤“’‘ŒŠ„€‡«Ô>G/\n\n\r\v\tşüúôïèàÍ¸—‘‹‰Š¬å=9++4A:.0463,&\bòèàÃ‘ŠŠ³ñAEEATPKE@B>GAA>91õåÆ‘‹‡Š­ğ29FLM>4&&+7?LKJA/ìÁ›‡Š¬è0?>=.\r1>KZWM:ñ·‡Š²í$#öëíâÙØàô\t=Pa^YEæ ‡Š©ÙïõîáØÒÇÂÁÀ¿Ìâ9QfgYC\t·‹‡œ³ÈÓÕÉ¸¶¬«­¦£¦²ÅÖì\b@aljV=í‘‡•¢³³«¤™–—•™›Ÿ ¯¿Öç.JamdD¡€Š‹’”‘‘••’’–™£±¿ÕöC\\mn\\7À€†„Š‡‡Š‰ˆŒ‹”›£³»Úü0RglgRïƒ„‡Š‡‡‰‡‡‰‹ŠŠ‹‘™¡©¸ÃîIdklV‡‡ŠŠŠŒ‹Œ‹‘—œ¤±ÇŞ\t>_jlX)ƒŠŠ‘‘‘‘‘Š‹‰ˆ‘—œ¤¯¾×ÿ7_jl]=ƒ‡•—“““‘‘‘ˆŒ‘—Ÿ§±½Öü4]hj\\=‡‘—š—‘‘Œ‡Œ‹ˆ—Ÿ©±½Õö7aim\\:£¡¤ š‰‰Š‘‹Œ–¡¨°»Ë÷:bhj\\0²µ°­©˜“‡‰’Œ— §±ºÌ>bhiR¼ÅÍÒÏ¶›––‹ŠŒ’‹Œ‘›¥¨±¹Ñ\tGfjjKıÌã×Ü×Ä§œ™‹Œ‹‘¤ª²Çè!Wclb5²ÖğóèßÇ³¡‘–£¨­µÏö0\\ejV•Æ÷ê×¼¢œ’‘“—£«°Âå\fE^lgEëŒİğØÅ« ™˜™—•š¡ª¶Ãßü1TbgM°ˆÖ\"úëÓÂ­¨¢š™¡¤¨¶Èİõ B\\f\\/ß”ƒÌ\t)'÷ŞÒÉ»·¶®²·»Ëæÿ;[`^?§†ƒÆ\v.:.ÿôëÙÔÏĞÓÜä9Waa@¹ƒƒÖö\">D?,üş!>Tdb>\v¾†ƒƒÏç2OXUC9/  $6I^_T9µ†ƒƒ€Éáõ\r.Je_VKC<8>FLZ][Jï¤‡…ƒƒƒ€”ºÏì#FfpliaY[__UI\"ó³…ƒƒƒƒ€€‡“•¡¶Éß%7^gbXDğÅ•‡…ƒƒƒƒ€€€";
int iE06 = 33;
const int N6=123;


const char Arr06[]=
"€ƒƒƒƒƒƒƒ‚‚ƒƒ…Ÿ¬¼È×çó\n\túïíôäĞ¾±¥œƒƒƒƒƒƒƒƒƒ†—°¾ÈÛçô#+3>C<şê½¨Ÿ”ƒƒƒƒƒƒƒƒ‘­¾ÊÖåø\t!/DHC:)*\bçĞ½§›“ƒƒƒƒƒƒ…”±ÂÑŞê'AG@2%\vèÊ´§˜“ƒƒƒƒƒ…“±ÊÕâ÷9?1(şòòïßÍ³¢–ƒƒƒƒƒ’²ÉÕæû ,(ñãäÛÕØÜÜÜÏ¸¢–ƒƒƒƒ‘®ÂÒçı\r+#îÙÔÆÆÉÑĞÉÂÅÆ½Ÿ”Šƒƒƒ‹¨ÄÓèû&\tùáÏÈ¿ºº¼¿½¿¼¼¼¸§„ƒƒ„”ºÓãú&#ùßÏÄ¹º²±®®µ¹º¼¹º¬‘†ƒƒ‹¯Éå÷\f!-#üßÇ¹²²°©¨¡¦­³¶´¸¸°–†ƒ„”ÃÙõ\n7/\vßÈ½®®ª¦¤šš ª´µ·´¬–€ƒ…­Éé\b!69íÏ¿±¯©¦˜–“‘•™¢§®°ª˜„ƒ‹ÁÜû3K7\vøÜÆ²¯¬¥šŒ“”›œ–Š„ƒ™Êñ/FA$ıŞËº²¬§Ÿ‘’˜“‘““”ˆ††ƒƒ¹Ü$CQ<\vòØÃµ²¬ ”“’“’“‘ŒŠ‡†ƒƒÈò;MO8ÿßÎÅºµ¤š–””——–––‘Š‡ƒƒ€ƒË*ISM.óÖÉ¿¼­¨ª¤¢¥ª¬®––’Œ‡†ƒƒ€–Ş:NVG#ìÔÉÇ¼ÀÓÖŞäçêãÑ»°¢“‘Œ‡ƒƒ€¯ù,JUXG ŞÕÛéâò\v\r$%#óÜ¾¯›ŒˆƒƒÁ<O\\aC üæö\r\"+28?EB6%Ô·¡‘‹ƒƒÎ&HW^\\B$)$!&)7?AGQQH9!ç¸¢ˆƒä=OX_^>&093*\")2AJPZ`RJ.ö·¡Œƒù>YchbK<=5( \a÷éëîú'CS_cd^Q2ş±ƒF]godUO=+şğ×ÈÈÆÄÉÔëATZli]P2ï¥Š1Qbrof\\O(üØÉ½±®²²°µ¾Ôú@XajkdI\"¶A\\hvri\\GõÑÂ¾­¢¥¥¢£®¼»Ç\a<Z`ji_@\n•G_nvqiT#úÙÆº³¢š–“‘’¡«´ÁÙSeklkY/«ShsytfFçÎ·­ª˜“‰‹Œ”Ÿª±Êõ2\\eim`=ÉZot|vh?óÖÇ·« ”‹†ƒ…Œ”¥­¾äWgikbT#crv{uc3ğÍº­§•Š†ƒ…Š“¥®º×ÿ;afgc\\D]rx{vb(ëÌ·©£Ÿ–‹‰ˆ‰‰Š’¡¨·Òì-Ydjg_PSuy{t_!éÈ®¤£›–Œ‰ˆŠŠ ¨¾Ïå'Xdgg`W;sy{ua ãÅ¬¡˜“Š‰…ƒ„Š¦¼ÏæS`eg`Tuy{ug&èÅ®¤—Š†ƒƒ…“®¼ĞäQYcb`Qğovvvk1ëÄ­§Ÿ—“‡†ƒŠ“Ÿ±¼ĞáNYab_JÔ\\rvvmCùÈ®ª˜”“ŒŠ–¥³ÂÔåGW_`U3¬9pvvmJ\tÓº­¦Ÿ“““«¶ÃÖö-JY`aHİ¢iomkY+ê¼­©¤•““‘”›¦ª¸ÈØ8NWaY8™–×<otshDıÇ¶°©¡›”—™£­¶¾Îì=QV\\Mˆ“´bmpiM'é¾¶±ª¢¢¤¢£¦±½É×5HRWR5ÃƒŒŸÛ1ajm]?\fØ¿¹·©¥¤¨¦¯ÀÆØö8LZUH’ƒƒ’²÷OgjlX5İÒÁµµ¶µ¶ÀÓÛó7DNSN(®ƒƒƒŸÇ\rYfliZ6\n÷äÎËËÌÏ×ğ6@JSL4Ì…ƒƒƒ„’£ËZhoiYDúñğñ÷\"8DSVL5Ñ‹ƒƒƒƒƒ…‘¡ÅXhri]R0\v\b\f-;LUQL0Â‡ƒƒƒƒƒƒƒ‡¡¼öMftle^M9;9>HRXXUC¦ƒƒƒƒƒƒƒƒƒƒƒ‹–£½Zkvvrjdba^ZXP²†ƒƒƒƒƒƒƒ€ƒƒƒƒƒƒ‰‘›¨ÉHbjc`XN4Íˆƒƒƒƒƒƒƒƒƒ€";
int iE07 = 31;
const int N7=122;


const char Arr07[]=
"å*28.030,10//-,,,)&&&$   &,37'õ#0CNUWRTUXZXVPNKHHHHGIHGHMPUN-ø$>S\\bfgllmmmmmljjjhkmmgfhgknc(û)>U_jllpqsqpppppmmmnppmmruyyYû)FPX]`cdfdcccccc`^^``ceinsuhAüâ\n(.554554010//..//-,.,3LcpnYÆÖï\bøïççåãåååååååèåèõ\v4ap_,ì§Ğúş÷ğŞĞÍĞÎÍÍÍÍÌÈÊÊÊÏÓßå\a;^^R\bÎ ÊîùçÖÁµ·¶´´±®±¯®±±´·ÆØñI[V$á¯ÁèëÔÀ¶««ª¢¢¢¤¥¥¥¥¥ª²Äà-KQ?şÌ ÄâÚÀ°§š›™™™›œœœŸŸ¢§·Íé=LJ\"àº–…ºÒ½«–“•’’’”–™™œœ¢¬½ä\t$F?2ÿÎ¥Š„ºÉ­•’‘’’’—­Íô6B?Ş¿™…ƒ¥«š‹‰‰Œ‰††ˆ‰‰Š‘–¥¼æ\t%A<-Î¨…ƒœœ‰ƒƒƒ†ƒƒƒ…††ˆ“›¯Õ÷*=<æÃš…ƒƒ‰‰ƒƒ€‚€€€€‚…†‰˜ªÈï54/Ê¯…ƒƒ‰„ƒƒƒ€€€€‚…‡— ºÚø-;4äÂ¡…ƒƒ†€€€€€ƒƒƒ‚…†‹’™°Ğî\a55(Óµ†ƒƒƒƒ€€€€ƒƒƒƒ……Š™¼Üú.8*áÃ£†ƒƒƒ€€€€ƒƒƒƒƒ…‹‹’œ´Öõ.4&\bŞ¾•‹ƒƒƒƒ€€€€ƒƒƒƒ…†Œ™ Ââı,3%ğÈ®Šƒƒƒ€€€€€ƒƒ††ˆ‹“—Ÿ¼Òö!-.#ßÀš…ƒƒƒ€€€€€€†††ˆ’”™¦Çç$0#öÒ´˜††ƒ€€€€€€€ƒ†‰‰– ½Õú\f,-$çÇ¢•Œ†ƒƒ€€€€€€ƒƒƒ…Œ“›±Íì\t(3$şÚ»’Šƒƒ€€€€€€€ƒƒƒ‰•¥»Úû\n'-&ëË²™Œƒƒƒ€€€€€€ƒƒƒ†Š”¡²Ëì!-& \bÜÂ¦“‰ƒƒ€€€€€€€ƒƒƒŠ™©¿Şö\"-(ëÏ¸¡Œ†ƒ€€€€€€€€ƒƒƒŠ’¢­Çê$/'âÉ¬—‰ƒ€€€€€€€€€ƒƒˆ©ºİø\t\"''!ôØ¾£†€€€€€€€€€€€ƒ—Ÿ¯Êæù#2)\råÍ·œŒ„€€€€€€€€€€€„—¨µÔğ+)&ıàÉ®“‡ƒ€€€€€€€€€€€‡“£±Áçú\a%.-$ëÖÂ¦‡€€€€€€€€€€€„•§´Íë*-&æÒ³¢„€€€€€€€€€€ˆ“£­µŞ÷\b#-0'öáÔ³ ƒ€€€€€€€€€€‡‘š¦¯Éé()-!\bêÙË®šƒ€€€€€€€€€€‡”¡ª±Õó '.)úèÔÀ®š€€€€€€€€€€™¢ª½çú**/&óÜÌ½¬•‹ƒ€€€€€€€€€‡œ¡°Ìø\b*(*!ê×Èµ¦‹ƒ€€€€€€€€€• ¨µáø -/)÷çÌÃ¶§‰ƒ€€€€€€€€€’¡®Ãæı$.%&\bòäÓÂ³¤†ƒ€€€€€€€€Œ’›§³Íë,+) şíÙÍ¾°œ‡ƒ€€€€€€€€–£®ÃÜú\t '))öçÖÊ½²Ÿ’Š…€€€€€€€€œ¤ºËæÿ')$óâÑÇ»°“‰…€€€€€€€€–¡«ÄÑãş\"%(òàĞÅ¸¦œ’‰…ƒ€€€€€€€–¡·ÊÓêÿ!íèÜÊ¿·¨‡…ƒ€€€€€€€’¨»ÁÏèş\b\fóéİĞÊ¿¶¨šŒ†…ƒ€€€€€€€Œ¡±¸ÈØùüöêà×ÏÊÁ¸©Ÿ–‰†…ƒ€€€€€€€";
int iE08 = 32;
const int N8=123;


const char Arr08[]=
"€€€€€€€‚ƒ…‹È\"CLMU_]Z\"Ó°Ÿ™’Š‹ˆ‰†ƒ€€€€€€…‰Î\"CKIJKPWdjtwrb!Ğ¬¡–‹‰†€€€€€…µ\v;EFH;-,.0<LaehmhYÄ¬£š†€€€ƒÎ FLA1\"+=RTbmd(Ü·¦™„€€€Õ!HJ>-\vşüüş3FSioc-İ·šŠ€€ŒÊDK?'óŞŞÖÔÏËÚë/GTghc*Ì©€ƒ­ÿ=GB6õáÔÊÂºµ­­¸Êß/NZfbIò±™€ŠÓ)HJ<$õÚËÄ¼³ª¢¢ ª²¿ä=R_f`'ÄŸ€¤ø7MG;\aŞÏÈÄ³¦ œ™—š£¬Áñ'FVha?Ü¬‰ÎJLK8øàÏÅº¯Ÿ—–”˜£·Û;WeePñ°ŒÚ+LHE6òÒÊ¿¸©–“ŒŠ•œ¤±Ö\v8TccPü´Ü.LHH>îÑÉÀ´¦—”†ˆ˜­Ù>UbbPü©Ü0MJI>õÙÊÀµ¦—“ˆ…–š©ÜBX]\\Dô¢Ü0OKI@1ßÍÃ¸¦š‹“™Ÿ³çJ[\\W/İ×,HJJB>õÖÇ¸­’‘‹‹•—£Ë-PZYA\nÔ˜¾\f>LKJE6íÔ½­¢–‘œ¡µå8\\\\K#è»‘†£ï3DGMNE3õ×»°§™–š£±Ø\b*J]R+Ò£Šƒ–Ñ<ELNQE9÷äÏ»°©¥©Ïÿ DSU(ß½‘€€³í\"?CMWSG@%õÙÆÄĞİ%BNK'ÿèÆŸŠ€€†˜¶ğ ?GPYXRH>-\tı!0HP?&éÉ¨Œƒ€€€Š Äò7KT[]_ZQRLABCOH3&\våÊ©–Š€€€ƒ‹¯Êá3P\\`cgf``bb^^J.\vîË¯‹€€€€ƒŠ”¯Ëì@ZilglilkiigbFîÅ®”ˆƒ€€€ƒƒ‰—«Ëï%Kfoqihkqrohf\\?ò¸¡‡ƒ€€ƒˆ—«Òğ\v)BdjeIOU[gnmjemjZ3\nĞ§ƒ€ƒ‡–­Óõ>\\`O<ÿù\"?LYZ_hpl_E×¦ˆƒƒŠ©Û1KdW> ùÓ¿ÁÁÒï3MX[flh^HÖœƒƒœÕE\\fZ;Û¸°¦£¬²³Ìê2OX_ji^F¼ˆ‰Ä@Yl]@\aØ´ªœ—•—£¯¿İ)MZagdY@ô“™î<VqkJÜ¹¦œŒ‹– °Å×ú!M[`d_Z4°¨+Qos^3ûÍ¬Œ‹ˆ†‰’œ©´ÄÕù+Q`de^MàÚLmuhMİ¶—‘‹……††Š‘Ÿ¬¶ÁÜÿ3\\Z_\\W8_urf>ùÍ²—‹‹……††‰˜¥²ºÍï$PV`a\\WJtvqd5çÁ­œ—Š†……†††š ®¶Éá\aCW``]Z`uvob5çÃ­šŠ†‚…†††˜¬´ÆÕ;O^`]Tluwq`4æ¿­Ÿ›‡‚ƒ††‡‘™¥®´ÅÓ:M[`ZMssvq`4ä¾³£›‰„„„†‹‘™©°·ÇÑ9NY\\SG`ssqe9üË¶¥•‰‰ˆ‹—¨±¹ÉÜ?QY\\P.tsnfEÔµ¬¥˜’”˜Ÿ§±ÀËë'DMXWAÌÔosshU)ıÑ·¬ š–””šŸ¥¯»Æâ0EPSL&Ÿ@prlc@êÆ¶°­£œš™£¤²¹Ã×ü&?MTTGç„“ñarrgQ.ìÑÄ·¯®°³²´ÃÏßş4EMQJ„†¤!fprhL-ùğÙÇÈÉÈÉÍáú/>LPI\"¾„ƒ†“³#dnuhP;\"şóóóóóı\n1?JPF'Èˆƒƒ€‡”µcnvjZE1\"\v\t\n!0=HMLEºˆƒƒ€ƒ†ˆ“¥ğLqsukcQ=8699<IQUTO?ë•‡ƒƒƒ€ƒ€†ˆ¡®õVvw|umkdcaYWWS>ü—ˆƒƒƒƒ€€€€€€„‰•¢¬ëPmqsj`\\P<é˜‹ƒƒƒƒƒ€€€€";
int iE09 = 33;
const int N9=120;


const char Arr09[]=
"€ƒƒƒƒƒƒƒƒƒ‰Ò(FQ[fhfR¿­”‘Š†ƒ…†€ƒƒƒƒƒƒ…‹À GRY\\\\Z\\_fsys^¿«–‡††ƒƒƒƒƒ…¬ARXUNB8357I_ru|jOó½£—•‘‡†ƒƒƒƒÏ3FMTQD2 0Maisk^Ë©—–‰ƒƒƒà6EJLC;$\r\bşüşş\a?Rajff(Õ¯š’ƒƒ‰Ô4EJHC9*ãÖØÒĞÖé÷\f0UenrgÑ­˜ƒƒ¹+FKC?7 æÛÅ½¶´²µÄÒá2Tjru^û½›ƒ—AQLF@'İÉÇ»«¤£¤¥²ºÆáCcourJé§ƒÓ=ONKJ?äÍÁ½« ¡¢£«²¸Èõ,Mcstj¸”‰(JVRLE+ùÕÇ¿³§”Š“š¡«¶ÁÖA]pvvIÛšŸ:S^PPAáÌ¼·¨šŠ‰Š‘˜¨«¶Êí.Wkxu]ûèDVWUP4ûÚË»³£Š‹’–¤ª²¾İUnttn0±0LY\\YU%ë×Åµª›ŒŠ–¤¯¸ÓJelrpMÑ=U^\\\\U$èĞÁµ¤›‘Š„ƒ†™¡£ªµĞú;^jst^ñFV^\\\\Z#ãĞÀ±¤›‘…ƒ…‹–¢¨¨´Îò*WjvxkI\\a]^]%ãĞ¾­¤˜ˆ…‰‹“£¨³Îë!Ultvk<M\\b_b_$çÓ¿°¦–’‘’—§°½Ñë!SiuvmWI^cec^-íĞÁ²§˜”‘•—¡¬°ÀÔë VjttlZ@]gfb\\:ıÓÂ¶³ —‘™¦³¶ÁÓñ)Xltrj]*[ghedQäÁ»·©‹‹ˆ‹–ª¹ÀĞà8`lrrg\\ÌEadbdY2øÊºº­¡‘”›¶ÁÌİò@cmolaP©7Vbbd_TéÈ½·©™–““–¥¾ÌÙë.Lcjmk^D–AX\\b^R7\aÖÍ¿°¤ £¦­¹ËØåø?WehkdY4¾-LTU`\\P7ı×ËÂ½¿ÅÁÄÌÕêü3GZfdf`S(¤÷4HNYa[O=ğÔÒÔØÒÔëú\v(3?DPcc``G€µ7FJS^WN9/üòğù\t !.9;1KZWZW;ø€‰¾.?GQUSF;*! ).7/!@WWYO-à€†¡½ó 29CNNMF:/'\" \b&?SUXGÍ€€…Œœ·İ (34631,'úçêú9STU;\rÆ€€…†Š˜«ÃÖè\fìÚÛÇÕç#;MTG#ñ­€€€…†‡‘§µÄÓÚÙØÚÍÉÄ¼¹¿×ò\b@OR<İ˜€€€ƒ„‡‰‹™£¦§©§¨¦ª®±¹ÊØï\v)FPG%øÆ…€€€ˆ‰‰‰‹’”‘›Ÿ©±ºÑæü0LO:ëÅ…ƒƒ„††‰ˆ‰‰‰•‘’“ ¤­ºÉÜë\a7I9!ıØ¶…ƒƒ„†††Š‡‰’–•—” ¥ª¯¼Ïåï\t BH7éÅ™„ƒ„‘™–—–••–Ÿ¬±µÅÔç\f,@6ùİÁ‘ƒƒ¥¨¥£—’”•›˜¡¬®µ¾Îãò84!ãÉ±Š†€–¦«¬­«¥œŸ— ¦­¯·ÀÉŞôş'3)öØÃ–‡†ƒ®²²¯±©££¢£«··ºÃÇÚô\b$$\rõİÉ±††ƒ‹­·¶º¶­¬©°®´ÁÅËÒÜô\t#õæĞ¸–ˆ††ƒ‡ª¸¸º´´²¼ÁÅÆÈÒÏÛö\n%øãÏÀ¦†††‰¥¶¿¿¹ÄÑÒÒÑÚÜÜğ\rùèÎ¿¬“††††œ¢»ÑÕÔÔÙÜİäêù%#\tûâÏÈ³•†††††œ ³Íèóòû\r+15.\tşôŞĞÆ¯•ˆ†††††“œ¥·Ëğ\a *<<?9+ÿùéÚÈ¼¬•ˆ††††††“œªÂØø1<=IDA4şìàÔÅ²«‡†††††††“œªÈè)FI;7#ïçÙĞÄ¶¬•Šˆ††††ƒƒƒƒ–¡³ÆİğöñêôúèĞÊ½´ªœ†‚†„‚ƒƒƒƒƒƒƒ€";


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



//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------
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
//---------------------------------------------
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
//-----------------------------------------------------------
void get_local_black(int iter, Pix* start)
{
   for(int i=iLeftDigit[iter];i<=iRightDigit[iter];i++)
      for(int j=iTopDigit[iter];j<=iBottomDigit[iter];j++)
		  if (Digit[iter][j][i] == '@' || Digit[iter][j][i] == '%' || Digit[iter][j][i] == '#')
         {
            start->iHeight=j;
            start->iWidth=i;
            return ;
         }

	return;
}

//-----------------------------------------
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

         if ( (Digit[iter][ii][jj]=='@' || Digit[iter][ii][jj]=='%' || Digit[iter][ii][jj]=='#') && (!lused[ii][jj]))
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
//------------------------------------------
bool bBlackHeight(int iter,int iStolbNo)
{
	for(int i=iTopDigit[iter];i<=iBottomDigit[iter];++i)
		if (Digit[iter][i][iStolbNo] == '@')
			return true;
	return false;
}
//-----------------------------------------
void GetNewTop_and_Bottom(int iter, int iTopDigitOld,int iBottomDigitOld)
{
	int iNewTop=M;
	int iNewBottom=0;
	for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
	{		
		for(int i=iTopDigitOld;i<=iBottomDigitOld;i++)
		{
			if (Digit[iter][i][j] == '@' || Digit[iter][i][j] == '#' || Digit[iter][i][j] == '%')			
			{
				iNewTop=min(iNewTop,i);
				iNewBottom=max(iNewBottom,i);
			}
		}			
	}
	iTopDigit[iter]=iNewTop;
	iBottomDigit[iter]=iNewBottom;
}
//-----------------------------------------
bool bExistBlack(int iter, int iLeftStolb, int iRightStolb)
{
	for(int i=iTopDigit[iter];i<=iBottomDigit[iter];++i)
	for(int j=iLeftStolb; j<=iRightStolb;++j)
		if (Digit[iter][i][j] == '@')
			return true;

	return false;
}
//-----------------------------------------
//false - êîãäà áîëüøå íå÷åãî äåëèòü
bool trySeprate(int iter)
{

	for(int j=iLeftDigit[iter]+1;j<=iRightDigit[iter]-1;j++)
	{
		if (!bBlackHeight(iter,j) && bExistBlack(iter,iLeftDigit[iter],j-1) && bExistBlack(iter,j+1,iRightDigit[iter]))// åùå íàäî äåëèòü òàê, ÷òîá è ñëåâà è ñïğàâà áûëî ÷åğíîå!!!
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
//-----------------------------------
void  get_first_under_hole(int iter,Pix *start)
{


   for(int i=iBottomDigit[iter];i>=iTopDigit[iter];i--)	
   for(int j=iLeftDigit[iter];j<=iRightDigit[iter];j++)
	   if ((Digit[iter][i][j] == '@' || Digit[iter][i][j] == '%' || Digit[iter][i][j] == '#')
		    && (Digit[iter][i-1][j] == 0))
         {
            start->iHeight=i;
            start->iWidth=j;
            return ;
         }	
}
//-----------------------------------
int get_first_black_or_grey(Pix *start)
{
   int iBegStolb=0;

   for(int ii=0;ii<Iter;ii++)
	   iBegStolb=max(iBegStolb,iLeftDigit[ii]);
   
   for(int i=iBegStolb;i<iMaxStolb;i++)
      for(int j=0;j<iMaxLine;j++)
		  if ((! used[j][i]) && (Matrix[j][i] == '@' || Matrix[j][i] == '%' || Matrix[j][i] == '#'))
         {
            start->iHeight=j;
            start->iWidth=i;
            return 0;
         }
   return 1;
}

//---------------------------------------------
bool isNoize(int iNumPx,int iMaxNeigh,bool bHasGrey)
{
	//return ((iNumPx < 10) || (bHasGrey && (iMaxNeigh < 8)))	;	
	return (iNumPx<10);
}

//--------------------------------------------
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
	
	// for each line
	for ( int y = 0; y < new_Height; y++ )
	{
		// Y coordinates
		oy  = (double) y * yFactor;
		oy1 = (int) oy;
		oy2 = ( oy1 == ymax ) ? oy1 : oy1 + 1;
		dy1 = oy - (double) oy1;
		dy2 = 1.0 - dy1;
		
		// get temp pointers
		
		// for each pixel
		for ( int x = 0; x < iNewWidth; x++ )
		{
			// X coordinates
			ox  = (double) x * xFactor;
			ox1 = (int) ox;
			ox2 = ( ox1 == xmax ) ? ox1 : ox1 + 1;
			dx1 = ox - (double) ox1;
			dx2 = 1.0 - dx1;
			
			// interpolate using 4 points			
				
				DigitResized[iter][y][x] = (char)
					
					(dy2 * ( dx2 * ProcChar(Digit[iter][iTopDigit[iter]+oy1][iLeftDigit[iter]+ox1]) + dx1 * ProcChar(Digit[iter][iTopDigit[iter]+oy1][iLeftDigit[iter]+ox2])) +
				
				dy1 * (dx2 * ProcChar(Digit[iter][iTopDigit[iter]+oy2][iLeftDigit[iter]+ox1]) + dx1 * ProcChar( Digit[iter][iTopDigit[iter]+oy2][iLeftDigit[iter]+ox2])));
		}
	}
}
//---------------------------------------------
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

         if ( (Matrix[ii][jj]=='@' ||Matrix[ii][jj]=='%' || Matrix[ii][jj]=='#') )
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
//--------------------------------------------------------------
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
//---------------------------------------------------------------
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
//----------------------------------------------------------------
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
 //------------------------------------------------------------
 bool Intersect_1_point(int iter, int iLine)
 {
	 bool bWasGrey=false;
	 int iPoints=0;
	 for(int j=iLeftDigit[iter];j<=iRightDigit[iter];++j)
	 {
		 if (!bWasGrey && (Digit[iter][iLine][j]=='@' || Digit[iter][iLine][j]=='#' || Digit[iter][iLine][j]=='%'))
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
 //------------------------------------------------------------
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
 //------------------------------------------------------------
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
		 if (Digit[iter][cur2.iHeight][cur2.iWidth]=='@' || Digit[iter][cur2.iHeight][cur2.iWidth]=='%' || Digit[iter][cur2.iHeight][cur2.iWidth]=='#')
			 return false;
	 }


	 for(int iFlagIter=0;iFlagIter<=2;iFlagIter++)
	 {
		 Get_ii_jj(cur->iHeight,cur->iWidth,cur2.iHeight,cur2.iWidth,iFlag[iFlagIter]);		 

		 if ((Digit[iter][cur2.iHeight][cur2.iWidth] == '@' ||Digit[iter][cur2.iHeight][cur2.iWidth] == '#' || Digit[iter][cur2.iHeight][cur2.iWidth] == '%'   )  )
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
//------------------------------------------------------------
 //------------------------------------------------------------
 int   VERSUS_09(int iter)
 {
   Pix start,cur;
   bool bWasRight=false;
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
 //------------------------------------------------------------
 int VERSUS_56(int iter)
 {
   Pix start,cur;
   bool bWasRight=false;
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
 //------------------------------------------------------------
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
//----------------------------------------------------------------
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
		   //printf("DIGIT=%d iCombNo=%d f=%f\n",iDigit,iCombNo,f); 
	   
	   //printf("DIGIT=%d f=%f\n",iDigit,fDid);
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
   else	
	   return iBD1;
}
//----------------------------------------------------------------
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