#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "header.h"

using namespace std;
int iE00 = 31;
int iE10 = 42;
const int N0=124;


const char Arr00[]=
"€€€€„„„„„†‰­MaXQPEó°™–ŒŠŠˆ„€€€€„„„„„‰•â8P]c_\\^`fc_2Íš’ŽŽŒˆ€€€„„„…ˆŠ½FT_R<413>^hfaCô¹›–ˆ€„„„†ˆŠÍ(BOWO- %57P]abTÄŸ–…„„‡ˆ‰Í%CTPE \r\v\t\r)J]ddR\t½Ÿ•ˆ„„‡‰¸BPZM&üäæââÙõ\r-PcehMõ°’Œ„‡‰;HQG.\fçÝÔÈÃ»»Çà8Q\\df@à¢˜Œ„‡‰Ú4HQL?äØÒÃ¼­§«±ºÔ\aEX^ke¸ž„ˆ GVU?)îÚÒÄ¹«ª£¢¤±¸Ü)WdejMé ‘ˆŒÔ<MVR<ÿßØÈ¼®§¦¥£§­µÇùC`iqe­•ˆ’GU\\N0ëÔÍÅ²¤žž‘›¤®³»ã-ZintGÇ˜ˆ­/SZ\\HéÓÃº§œžš’¨®¾ÖShoubôžˆãCRcVC\våËº¶£™–ŒŒ˜¦°ºÎõ9howt'ŸŒI\\fY6ùÚÃ²®£”ˆˆ‹”¢®¹Ëå)dpzxO¦3R^dV0ïÐ¼±§ ‘ˆˆˆŠ‘ ª±¾ß\\mxzjÄJ\\acSïÍ¶«§ŸŽˆˆˆŠ‘Ÿ¥©¿ØEiqzuâ¿O]e`QêÆ´«¤˜Œˆˆ‹”›£«¹Óó7ft{xScn_HÿÝÈ±§ ˜Š‹ŒŒŽ›Ÿ«¸Ëä5at{z:1\\in`FúØÃµ«£’‰†„†Š“œŸ©¶Èá2[t{{e@\\kpaHöØÀ´¦ ’ˆ„„Š—œ¡«¶Èá.\\txwmP`ltaCóÎ¶±¦ ƒƒ†ˆ‹—ž¡«¶ÇÛ)WqxsmXjmudCòÏ¶­£…ˆˆŠ” £«³ÁÜ+Rnxpm\\ksud?òË¶­£™Œ…‡ˆˆŠ“£§°Ãâ/Unxpmdlxxd>ïÇ³¬£™…‡ˆˆŠ“Ÿ§°Ãâ,Tkwmh`lxxh>ïÇ·¯£…‡ˆˆŠ“—š¥°Äè3Ukpid\\s{xhAïÈ¶³¦™…„„ˆˆ”š¦²Ää/Sktk`dw{xhAêÆ¹´¦™‘ˆ„„‚…Œ”š¦²Ää/Sesldgw{xb?èÇº°¤™‘‰†‚‚†Œ”›©²Çæ0PdniUg{{xeDîÈ»°¤™‘‰†„„†Œ”š¦´Íê0Nck`Id{{yhGîÌ·®¢™…„„„†Œ”›©·Íí5Kflb04v{ymMóÓ»®¢™…„„„†Œ”œ¬·Òð6KdfYù\rr{umOÛ¿°¦•…„„„†Œ”œ²ÂÚ:Sb`P¼Öt{uqYÞÁ­¢›…„„„†Œ˜¦µÉæ\n<T^`K™¿mzuqb2ê¿°¨ …„„„†Œ™©·Íê@V]Y3—£Sv{sf9êÃ·« †„„„‡ª¸×ó-AX]XŒ£pzsgJùÎ¸¯ª•‰ˆˆˆŠ“¤°ÃÙõ2FZ\\På‰£þdzokT\rÚÀ°ªŠˆˆˆ›§¶ÌÙ5LWW7¯ˆ›ÆBsrm^9çÀ³¬¤•‰ˆˆ”¤¯¾ÅÚ5O[Q•ˆ›¦aqib@þË»°« —‘’¢«¹ÇÆï'<LT@×‰ˆ¤êHohfV,ä¾¹«¡ž¡¦¯¿ÅÜ/IXM¤‡„Œ›³`oeaB\b×½³¨£¦¥±ºÅÒþ!=JP;×‰‡„„˜¥à>feaX1ÝË·³³²ÀÓÞü/OIHŸ‰‡„„™«ùQijeP&\fòÓÏÒÕÚö:MKN%¼‰†„„„˜ŸÂ\vXnreL,\bÿ\b\n3DQN-ÊŠˆ†„„„„˜ŸÆZlsoW>)#;MSQ2ÌŠˆ…„„„€„ˆ™Ÿ¼ûLnsyjI@2/4FSXR%ÂŠˆ…„„„€€€…ˆ”™ŸÓ6jstnc\\\\\\bZBý—‡„„„„„€€€€€„…ŒŽ”šž¬ëJ[[Z^X)µ‰„„„„„„€€€";
const char Arr10[]=
"€€€€€€€€€€€€€€†”Î.9?BFEIÎ¶±°¤œ’“—•““‰‚€€€€€€€€€€€€Ÿê$3/4:6=??IT_dbAôË¶§§¥—š’ŒŠ‚€€€€€€€€€Š§ò ,5:C7+0/,29Pcfbh]<þÙ¸¬ŸŽ‡…†‹‚€€€€€€€ƒ’É'/=F2*'1:J_hno`!ðÅ¦Ÿ‘ˆ…†Œ€€€€€ƒŽžê(,3D:.,*!3<B[ffgi'ûÌ® š‡Œ€€€€ƒ£ð(,7D81$%!\bùûÿù)1?H`ebd>Ï¬Ÿ™’Œ€€€€‡¡ê',BD;/%!\aüôõïéîö#(:KN^[^9ûÌ©¤˜Œ€€€„•á$,BEE7!!ýóòåáããëèø\n!*9@OUW,õÃ®ž“€€€’á$,7=D7+)þýêßßàààÛàåíïÿ#,9EFZX(æº° €€…Ÿú+:FE<,##\fþìâÓÖÖÓÎÈÆÐÓÞñ!/9GKZJÏ°š€€’à$9GF=-(%\nóäÞÖÒÉÀ´¬²ÀÌÜèñ\";?COb=ñ¾œ€†§4?KE?2#\r÷óêÖÆÆº­¤ ¦¾ÅÊàìù\b+<FFeaÀ›€Žê+8BK?6(\"öõîäËÁ²£šš ²ÂÊÍâö\"A?F`lTè¯€–7CKBC7)!ÿúÿñâÂ²¢–“ššš­¾ÈÍÞõû\f 18I\\tný´€Ç(;CKB>3(\vþ÷éØ´Ÿ“—š«´ÇÍÙïù\t+9M[nt4·€4CFI==7%õäÈ˜‰†‡¤®ÂÍÔá÷+5P_hpcÅ(;CGC?F9\rîÏ°‰††ˆ“¤´ÀÐÝñ*:P`nndÞ“5?FLGL>)ÿõâ·—‹ƒ€„ˆ“ž³ÀÎ×ìþ\n#BNableßÍ7DDHLM=$$\býíÏ¦—††ƒ€€€‡“ž®¾Ê×æöÿ(EXaafk58DHSLLA/øèÆ¤—††ƒ€€€‡“ž®¾ÊÙæðEQY^eeS3EFHOPQC\"\fïÕ¹¤—†††ƒ€€€‚“ž®·ÊÙæð)EQ[^eeY?EJPVPW?'\fûåÍ³¤—†††ƒ€€€‚“ž®·ÈÖæõ0IIW]WSR?EJVWUQC$ñàÊ³¤—†††ƒ€€€‚“ž®·ÈÖêù0GKR]]SR9EOXW_W?$üíØÇ³¤—†††ƒ€€€€ž®·ËÝìù/FGQWRRR?KQXb[V<!ùä×Ç³¤—†††ƒ€€€€ž®¾ËÝð\b2CGQTNP@LLVXeaX<óâ×Á³¤š††ƒ€€€…ž®¾Îàô\v8EFKOJL:LQ^ggcU9ÿîÝÔÁ³¤š††ƒ€€€…ž®ÄÔè5C@HRJK-LW^ggc[4\tøîÝÔËµ¤š‹ƒ€„††ž¯ÏÝóý5C>FJJK!LWlmjaR-øìÝÔËµ¤š‰††††ŸÃÙçõ8>9JGD9\r&^nqkeQ1øìÜÔËµ¤š“‰††††¥Åàèò3?BFG?*×àcsqi`N,\vúñÜÔËÀ¦š“‰††††–ªÓäéú(6A@IDK&˜Ínysh_I.ñáÕËÀ®¥“‰†††Œ›ºÝâïý0<>@FC<‹Àtsrm`I4øìÖÍÆ¸¬““Ž‰††‹¯ÐÜæìÿ872GFC7…¦7ppjYI4 \nùõÞÓÈ¸­š˜Ž‰†Š’Ÿ¿ÐÞêò(22>G@<'É­ûyobVI:$\fûüâÓÏÃ¸šš–£®Åàéì,3>?C79”€­çHjbWJB'ýìÕÑÇ¹«¡ Ÿ©´¹Íãæõ%)3CF87-ìˆ€³Ó`_WLH3&\fûöçÓÏÄ¬¦­ª°¹µÆßâôÿ\n$+>B@7-§€€³¿á:]WMJ=(üìÞÓÆ¸²³¹À»ÂÌÙêü#)5F@6-)çŒ€€­¸ÌýEVMJE1'ùæÛÓÊÌÉÌÌÏÖÑÞø\f$.;=44-£„€€š·¹ÕPQKD?2&ÿûòäÝ×àÝÙÝÛÛöÿ\t$,1A96.Ö‹€€€š«±ÁÝ MLQF:5(\bôêëèåæäãêú$3B>5-,ê’ƒ€€€šŸ°¨ºÞMRWGA2&\nøóíããéÿ\"/;B4-)ï”ƒ€€€€““¨ª®¾ßLRQ?:8.**õóý\a$3<@0'*ñš‹ƒ€€€€†’¡¢­ÁÜKT\\YWL@6+##+59<1(*é•‹‚€€€€€†“™©ª¥¶àU_kmaGA-(,),&$0A?7.-#ÌŒ†€€€€€€€†Œ“˜¢«²ºÕ\tRgffdcVFA6)&'79=:0)ì™ˆ€€€€€€€€€€†Œ•¯³À¿ÕCab_XD99946=76'è—Š€€€€€€€€€€€€€‚†‰’“–™¤¦¥¯·»ÊKRI9698,Ý’ˆ†„€€€€€€€€€€€€";
int iE01 = 15;
int iE11 = 26;
const int N1=126;


const char Arr01[]=
"  ¤¨±·Ðå\fòúóú¥ª²½¾Ñë&0\rø ®¹ÌÕì\r'?E<&\aú«¸Æåò)CLQH'õÊÛãô(<GOiL'õàÝêý1@NfwS-ÿðåäæð*CWoyS/þðÅåëø1OgorL+ÿìÊÒÛé:RejqL+øáÅÐØð6JXfxS/\nøáÀÌá÷(@QfsS-ùáÅ×æòû#<HK\\Q&\føçÕÛàæò*/CXL\"\fôÝµÅÊÐà&AXL\"\fôÝ°ºÀÊÎõ(AXL\"\føÞ«²³±¿ì(AXL&\føÞ«™˜¢¶ì(AXL&\fôØ•”Ÿ¶ì-BXL&\fôØ”Ÿ¶ì->RM$\fôØ‹‹Ÿ¶ì->RM$\fôØ‹‹Ÿ¶ì->RM$\fôØ‹‹Ÿ¶ì->RM$\fôØ‹‹Ÿ¶ñ->RM$\føÞ‹‹Ÿ¶ï+>SH$\føÞ‹‹Ÿ¶ï+>SH$\føÞ‹‹Ÿ¶ï+>SH$\føÞ‹‹Ÿ¶ï+>SH$\føÞ‹‹Ÿ¶ï(;SH$\føÞ‹‹Ÿ¹ó%;TH$\tñÝ‹‹Ÿ¹ó%;TH$\tíÜ‹‹Ÿ¹ó%;OH$\tê×‹‹Ÿ¹ó(?OH$\tíÜ‹‹Ÿ¹ó(?OH$\tíÜ‹‹Ÿ¹ó(?OH$ìÜ‹‹Ÿ¹ó(?ME$ìÜ•¢¹ó(?ME$\tñá•¢¹õ'?ME$\tîà•¤½õ'?MH*\tëß•¤½ñ'?OJ*\tìÝ•¤½ñ'?OJ*òà•¤Áñ#?OJ,\fîà•¨Áñ#?WL)\föæ•›£´Éõ#?WS7è  £´Ïõ#=WS9$\nð  ¦¹Î÷%=QX?(\rû §´ÄÕü';QcK.°µ¾×ï2<Sj[9 \fÐáçñ),2LheWJ<";
const char Arr11[]=
"€‰‰‰‹ŽŽ“”—¡©ÃÞêõãÄ¼ÆÀÔÊ»Æ‰’——–•œœ ®ÈÚòûðíýóðõäÆ—›œž¢¦®ÁÈÖõ\t\r\",(%\nÿóøõéË—˜™Ÿ¨±¸ÌÚè\r%,.@HI<\"øùñìÕ¥®µÂÄÍàï.3=GNYT> ôôïçÌª¼ÃÄÌçò\t%5BGLceS=$ôôíÙ½®¿ÉÔêû\v!0>M\\eeYA\"ôñãÆ¸¼ÊÎÏØèôø\"1FMUbo\\D$ôçÖÀ³ÁÆÑÛ×âí÷þ*>ISblW<ôçÒ¹®ÊÊÇÂÈÔÝëð(7FLchX>\féÚÎ·ª¼ÁÁÍÓÙåëö*<Lfe[A\fûåÓÃ¶¥¥¶¹º¾ÉÓßæô,=Ubc[A\rúáÓ¼² ª·º½¿Ë×ÛØì/8Q_f]AôÜÑ¼² ¥©®³¸¾ÈÑÍä\b*>Uch^?í×¿¹­ ¥¥¬³³»¸ÀÆä)AN`h^?ûìÓ¼¸­   ¦¬­°³½Äß\b'?Sej\\9\fõéÓ¼¸­ œœž ¢§¬¹Á×/BSij[6\aòåÂº³­ ———š¢¨¸ºÔ\a3D\\ijX0òåÂº°ª “–—š¢£¬°Ö\v4JXeeW-þì×¿º°©œ“———–—™¨²Ø8M\\eeT+ïÓ½³°©œ““Œ”˜£®Ü<M_igQ&ûçÐ¼³°©œ“‹Š”¡¹å<QZdcO\"ûçÍº¯®©œŽŠ‰‰Š¨½ë@QZd`M÷äÍº³°©œ…‰‰‰Š‹“ªÆë?QUa^JñàÊ¶³°©œ‰‰‰‰†‹—µÌô AKUebFîÖÈ³¯®©œ‰‰‰…†Žœ»Ìô$AMU`\\EëÓÈ³¯®©œ…………‡“ÀÏô!>MU`\\EãÓÃ´´±ª…………Š™§ÄÕö$:MU_XAãÓÃ¸´±ª …………Š™­ÈÕö%=OUXW<àÑÃ¸´±ª ………Š™­È×÷!=PUUU8àÌÀ¸´°¦ ………Š•¨´É×û\"=OQTQ6\fÝÌ¿³³°¦ ……‡•¨µÍ×û >PQTQ6\fÝÌ¿³³°¦ ……‹Ž•¬µÏÚû @MLPQ6\t×Ì¿³³°¦ ……‹”ž¬µÏØö?HLNG2×È¿³³°¨¥…ˆ•§°¹ÑØö\"?GLNG.×Æ»³³°¨¥…Žš§±¼Ñ×ó&>JJNG-ý×Æ»³³°¨¥…“ž§´¾Ï×ñ$>JJND)û×Æ»³³°¨¥‰‘œª¯¹ÄÏÓò<CGIA)ÿØÇÁº¸´­ª““£¬³ºÄÏÓò\"<CGC?)ÿÓÇÁº¸´­ª“—¤¬³¾ÉÏÓø%<CEA<#ÿÔËÅ¼¸´­ª“ °³·ÁÌÎÕ÷$7ACC=\"ÚÏÅ¿¶²­ª—¥°·¹ÅÍÑÖõ(;ACFA&\aÛÐÈÄÃ½²ª¥®·ÀÃËÒÚå\n,>CCF?1íÖÎÉÃÀ»´¸ÉÓÕÙáêð!5AA@F@?'üëçÚÖÒÍÆ®ÕØÙâéø,:A=>F?>.ÿùíéäÙÏÁáúÿ\n-:KH<<<>B6%\bÿòâÊó *6<BKC7540152.(þÏ÷!#*,461&%\"&*,000*'$\b";
int iE02 = 29;
int iE12 = 40;
const int N2=122;


const char Arr02[]=
"€„„†ˆˆˆ‘£Âù6ZeinhP\r»¡•ˆ„„€€€„„ˆ‹“©»à)W]bginpuzr^7ð­—‰„„€„ˆ•£¸ÎI^_VRSTWahmrvmT&Ú¥‘…„€„šª¼é(Q[SFE:639AJVbntlT.ï¬‘…€„¨½å&RQL@-%# +.02E_pslL ä¢‹„„°Ø\rNR?3$\aóçáÝÜî-?XjreFÕ™…Äî*=1\bïÞÒËº·¸¼ÆÜ#@UkkR1­‰¢Ê\a4.òáÎÁ»­£§¥´ÀÚù&JcraIà“¦Ö\t$\röæÐ¾°¯™™œ£°ÁÞ+XokN)ø ¦Ó\vï×Å¹¯¨˜““˜ž£ºÑîIdqZFÁ¢ä\t\bòßÈ·°«¡—–“”ž£¯¿ß\v,Zp_Iæšï\f\aõÜ·®¬¤¡’‘“”ž¢«¼Õþ)RqgPé©ç\nÿðÑ»³¨¢ž•‘Ž’ž¢§·Ðþ$NqfLð©ÆìóéÝÆ·²±«œ™“¢§·Îþ'PsgLðž°ÔÛÚÓÌµ´²ªž˜Œˆš¥§¸Ô\a(MsfBìš©¹ÈÏÊÅ¹µµ§Ÿ‘Š‹Œš¢¦¹Ù\a(Vqf9âš¦­½ºÀ½·®§œ‘ŒŠ‹ ¢¥ºà\a.Wpc1Ú—ž¤«¯ª©¨žš–ŒŠ‹ £¦¿îF_nRñ´‹“–˜¢ š–Š‹˜¡£®Ôû)KehC\fÙ—‹“““•œšš““ŠˆŠ‘ £§Âå=Pc[.Ô—„Œ““‘——““Š“ £¯×ý$NZb@á¯Ž„Œ‘“““”———’”š©ª¿íFWb[1ñÑ›‰„ˆ“’Ž‹”§­¹â.KW`@×«‘‰„ˆˆ‰‹‹‹‹‹‹‰‹’œ¯ÀÐõDT]FãºœŠ„„…ˆˆˆ‹‹‹‹ˆ‰“«¼Ïñ4K[M*øÁ¢Ž‰„„„…ˆˆˆˆˆ‡‰“¡ºÐâ\n#FTJ-\aÈª“‹„„„„„…ˆˆˆˆŽ’œ¼Ñà\bATI,\rÒµ™‹„ƒ€„„„„††„‰‹‘ž­ÆÚ÷7G@,\vÜ¶˜„„ƒ€„„„„„…ˆ‰’ž¤¼×î\n 6;'ìÀš’†„„ƒ€„„„„„†‰”¤·Ñå\n15#ôÌž•ˆ„„„ƒ€„„„„ˆ‡ ¦µÄà/6!÷Ëž•ˆ‡„„ƒ€€„„„ˆ‰“¥®Âäù'\vúÎ¢˜‡‡ˆˆ†ˆ„„„ˆˆ‰£©¸×ð!$þÑ¨–Žˆ‡‡ˆˆˆ‹„„„ˆˆšž¡¶Øð&É­–ˆ„‡ˆˆˆ‹ˆ„ˆˆŒ¤³Õð\v$\bÎ²š•ˆ‰‹Ž–“„ˆˆœ¢¸Óú##*\aÔªš•‘‹Ž’•¡„ˆŒ ·Õì\t (Ø²¦ š—“‹‰Œ•£°·ˆˆ¤¶Îê\r#)Ö·©¤žœš™˜ššž¦©´Ïºˆ°Îð\r+Î´ª©¤¦££¤¢ž¡°¶¶¿Ö¾ˆ¡Åô\"$9*ÝÀµ±«¦©¦§¨¦¨±·º¼ÌØ°“¶ì$-A9 ïÊÀ¼º¶µµµ¶¹¹µ¼ËÏÕçë´¢Û\"7RM6\nìàÞßÙÖÖÙÝÞßââêñòöýëÂÄ\v<XeW1%\"!%%#!!! !\"%#%&)\"\r×â;Thmd]ZZZZ]]][ZZ\\]][YTOQP2õ2Qgmmlmppppsqrplikljiga`ZB-ý\aOcfeeehgjigeiiiioojiidZ_NC!ûJJNQRNLNJHPRRRXZ]Z\\[PPKIE3ð);44578<:8469<;@FDAB?>890-'\fã";
const char Arr12[]=
"€€€€€€€€€š±Ì14;DKK8&ôË¿±¦§¦¦š—‰†€€€€€€€…Ž›°Æí\f!643?CAJNRReigaK.éØ±¦¡žš‡€€€€€€‘¥·Ëç.4--5<58BDNZ^iptxq`Q4ïÔ³¡ž˜€€ˆŽ–£Îò%!$ '*9<DVaifiklhR@.áÈ«Ÿ–€ˆ–ž¯Òó$0BICM_\\fjmiXC.ïÅ¨ž€—¦®Ïô#%!\"%\f\b\a)--:CGTY`\\_ZM=.\nêÁ¥—¦ºá'(\"&ýôñ\n!% $%.4CKV[_ZJ;úà¹Ÿ­Ñ\a%üóðéñúü\r\r ,@FDPQQNA1ðÌŸ¦Ëï\b\f\r\vþøîéèæïïåÞåôó 2?CKPXSK7)\bçµ—ÑûöþòõåâçÞÓÈÄ¿ÈÕì\b *<>CPXSMA=ëÄÐõ\vûòöêÚÓÌÔÏ¿±­±µÀÚ 9>CLSZYIMüÚžÝð\nýøðêÚÎ»®¬¥œž¬µ¹Ôÿ9<=LSa[VO1ÌžÞõøþþööðäÚÄªžœ”–¢©²Î÷\v3<8P[hcVJ0Ìžå÷÷óû÷øü÷ïééÙ½¬žœ”–£³Òð7@=Qdpc]J0÷Ë¦Øõ÷ííôøüùïâÓË½¬žž›––¤·Ïð>C=Uhl_]J+ì¼¦ÊçèÞâåéïðïâÙÈ³°°«¡–šŸ¸Þõ'>>N^kldV>ë®ž´ÄÑÚÚÚÙÞ×ØÊ½·µ´²«¤ž—˜©ºäû6HJaepeZR5ÛŸ¤·ÄÇËÊËÑÐÄÃ½·´¬©œ–—ž˜±Æé\b@MWad\\aXEü½—¤®·³±±®³µµµ«¦¥ž˜™žž¥®¿Úõ6FQ^_ad]P3ì±ˆ–¤ª²¯¢¢ªŸžžžž —”™¡¯­·Éê\r.DM[ba\\aS>ùÆ¡€–—¡ §—˜ž˜———Ž—¡°°±Ââ\n#@NT^f[aSE.\fÞ©”€ˆ•—“ž™˜—–———ˆ–©¯°´ÀÜ4?U_e[a]G*è´£€ˆŽ•’‹”‰——™ª±ºÅé6DR[c^VZF2!öÃ§”‡€ˆˆŽ‰ˆˆˆˆ†€€†Ž”Ÿ¬¹ÁËì\a '<RVai[TA3 üÄ¥—Ž†€ˆˆ…ˆˆˆˆŒ“™§³¿Æßþ%(;KU^dXLB.\vÁ¤—”‰†€ˆ€€…ˆ‹“ž£µµÅà\"%<JT^bQKB/#òºªŸ“‰†€€ˆ€€€ƒ‹“¡¨²·½à !4GT^^LI6\bí·¤™’‰ˆ†€‡€€€€‚ˆˆˆˆ‹ ¦²·Àê(JSZPCG;þÞ¯¢˜‘‰‡†ˆ€€€‚ˆˆˆˆ–£¦²ºÌé\v(NVH<;=&ûÑ²š—ŠŒˆ‡ˆ€€ˆˆˆˆš¦¦«»Óè'EFG<1+%äÉ®š—Žˆ‡ˆ€ˆˆˆˆš¦¦°ÇØò,BD=)$+ûåÈ¨—–’’“”•Ÿ€ˆˆˆ™¦¦±ÈÜó\"9?,%%éãÌª—•‘’’”•¥‰€ˆˆˆ™¦¦³Éßö\b#:?'+\"ýéâÆ©–‘—’‘—””¬—€ˆˆ’£¬»Öèø\f=91(ÿñâ¾²¥—‘•“™ž›¢¦«µŸ€ˆŠ£¬¾×êø\r#8G:+ \räÂ´­­­¯­­¯­­±±­¯Â¸µˆˆž¾ÉÛó\v$><0\"%\týåÌÂ¼¶µµµ¹»¶±²±±¸¾Æ½µˆ—¿Äç#+FC610%\nóÚÐËËÑÓËËËÈÇÀ·µµ½ÑÌÅÃÁÊã %4?=57& \vòéíééééåâá×ÓØÔÆÄÎÜßÜØÓµÊß%39=E<@460)\f÷éòûýáÚµßû/@FIVZKCC=0344444442--*%%\býáÓËþ\"-ALZZ_[ikbZNKICCFKKKKKKF<<<?<4'*&äêé6CLWaaiigZRRRKKKKKNRRRRRPHCFC<B<1-'øêñ$<CL^aidaZZZZRZZZ[aaacaaah_Z]RRRK></üùø+CLcle]ZRRRRRRRRRUZZZZZ^]a^]ZRWTQF<-\tùêø$Aikf^ZRRRRRRRLKKKKKORKKKCFKKRXZYM?*þöêéYa^ROKKKKKFEKKKKICCCCBA=<<</:CK>=0øõâø:PICC@<5/41'*'%%%%)--&%%%'%%,.,)ÿêõê%(&\a\rþüñåË";
int iE03 = 29;
int iE13 = 40;
const int N3=124;


const char Arr03[]=
"ƒŒ“œœ µÊèIXY`eaIÆ²¬¤Ÿœ““’‹‡‘¡±Ê×íF^`begijrzxlEýÃ´¬§£–‹Š¥½Ìé:W[UOTRRTbgluxxe$ã¿²¦œˆŽµÍà<SUMGD41237EZdhlr^:ðÂ«›…‡¼Ù\a7KJ=+!6GV[jn`/ã¹š‘ƒ¿è;=.çÚÑÌÐÑÛñ\t)8KUksVÄ£–‡¼ã2+îÛÏÁº«¨­±¹Íö@RbjbAæ®™Š·õîÕÆ³¥¦§¦¦¤§°Æõ/FTcfM¾–Š´îòâØ½£ ŸžœšŸ ±ÛAP]aR&Ù Š´ëúìãÕÈ¨š•’•–“”™ªËû2EX\\T7Û ‘³ßæÛÓÌÆ¬›—••”““‘š¯ÊöBSZM3Û‘¯ÏÐÎÌÃ­¡–œ—“‘•Ÿ©Íî@SSF3Ô™Š›··²·µ¦œ–‘ŒŠˆŠšŸ­Éí=QOC'Î•Š“Ÿ¡£¥¦Ÿ’–‘‡ŠŽ“¢¤¨°Ñö DLE:Ç’Šˆ•˜ššš–Ž‡“š¢¡¤·Þ)FHC)\aµŒ€€‡‡ˆŒŽŽŒ‡‡Š‘— £®Áî5IB0á£‹€€€…†ŠŽŒŠ‹“™Ÿ §±»Ý\f*D=/!\f¾”‹€€€ƒ…Ž‘‘“’•˜¥¯·»Ô4?,ã£ƒ€€€ƒ‰ŠŽ“œ¢¦®¼¾Ãä\b3;%í¬”‡ƒƒ‚ƒŠ‘—¥¬¯µÊÖÞü6=@5* õ»œ‡‡ƒƒƒ†Œ•š¢«ÁÝö!-?IEQQC)È£Ž‡†ƒƒƒƒ†™²ÆÒê\n5FPV]`d\\@+âÂ¦–‰‡„ƒƒ„‡£¸Íá >LQV\\_\\[C,\tóÛÂ¡•ˆ„ƒƒ„‡±»Õö,458;BMae]Q$àÇ¤Š‡ƒƒ„‡–¡­¶Îãøý\n\":[licMíÀš‡ƒƒƒ„‹’–›¦¬¶¹º¿ÇÒÜý+Ngnn`(ë³‹ƒƒƒ€€‡‹‘‘—›¡«»Ñå\b3RdpsaÍ—ƒ€€€€€ƒ„‡ˆŽŽŽ“•—ž¸Ø4ZnsqUö¥ƒƒƒƒƒƒ‡‡‡ŠŠŠŠŽ•™Ÿ±ÞSestfC½ƒƒƒƒƒƒ‡‡‡‡‡„‡Ž’˜™¤»ð2_lxlVâƒƒ„‡ˆ‰ˆ‰…ƒ„†‰ŠŒ’•˜¢´ß]lvs^$ƒ‡—š’Ž‰‰‡‡‰ŠŠŒ‘”œ¬ÓüIjoseO‡’œ¢¡š‘ŽŽŠŠ††ŠŠŒ‘”š«ÊøIgkscV˜™£©¨”‘ŽŠŠŠŒ‡ŠŒ‘”š«ÌùGbkuhVŸ´»¿¾¯‹Š‹ŒŠŒ‘—œ¶ÎûHekueLÌÝÝØÑ¼¬ž–Œ‹ŽŽ‘™ ¹Ðû@cms`5ÓñçæÛÍ¶£˜ŒŠŽŽ—›¤¼ÖýAeliSçõùìáÓ»¦˜”’ŒŒ•›¤¯ÇåZgp_>ïÏõâÙÃ£œ–—Œ‘œ£©¸Òñ;_hiK ŸÝ\nõá×Á°ž—••˜˜–›¡§·ÇçSbeY6‰Úå×Ï»«Ÿ››˜™š¢¬¹Èã\n>Y`_HÈ…Ìû\t÷ÛÎÀµ«¨¦¬°·¿Îç\n/Y\\]O*õ•ƒÖ#8&\tõðäÏÏÉËÏÑÝë/K]`U,ÿ¥ƒƒÚõ1B+\bþüüþÿ\t2NW]R%µ‰ƒƒÓì&>RD-(\"+HLWS<ü¯Šƒƒ€ÈÝû\f#D^\\K;10767ANWVI&\rÚ—‰ƒƒƒ€¦¹Ôê ;TifbaYTTYVG(ç¢Š…ƒƒƒ€€Š˜›¦¯ÂÙó4Tbc_I*\fá®ˆ„ƒƒƒƒ€€€";
const char Arr13[]=
"‰‰‰‰‰‰Œ•šž¢´ÄÛÿ/;;@DDQSE3\aØÊÍÍÄ¼ªš–Ž‰‰‰‰‰‰‰‰—¤°ÄÓæ\t&03,*+5DPUWhnzzqZ3ñÓÄ»¯«¡˜‰‰‰Ž•¦»Ïî\f.-*')-33.CUafintqkbY>ðÔÇº¯Ÿ‘‰‰‰’©Åæ\"+31''*.*#\".;LU`ff`]ae]YI\rÕÏÁ°–‘‰‰ŸÀë\a&*)*%&\" .+.?>LO[]]WOUUOF#àÖ½¨“‰‰˜²å\f/+(\"*(*+%*#\".;DLLSNINUW]]VU.ìÊ±£‰¢¾Ö\v&31!!*,'$ %:;3>IDDGLMUPTPÝÎ«‰’Â÷)1&\b \aø÷ó\v#/2;:;;;ALV[T>ûÔ£‰›Úû\b\b\vñöìî÷ùþ$-7C;=QURMIà¼‰¢Ô\v\r\bôïÿ\bôëóðàÕÏÌáçêù*8<;=QUNKT:à¼‰ªÒö\bûíÞÞæáÓàãâ×ÊÇËÈÌÚîü\f$'-5<IMJRT6ç«‰¹ÌâæïìâÕÕÏÐÊÊÍÊÁÂËÄÄÄÎßô\b!*6;<IRJKK-Ù«‰©³ÃÍ×æâÕÍÏÅÀÇ¶±¬¨º¼·ËÏæ\r,12=HIANOBÌœ‰‰™£·ÁÄÅ¼¼ÈÅÀÄ¨°©°´­ÀÌÏë\n/3;CEJKPF@½›€€ˆŒ“š¦³««­±«¤Ÿ¤ªªµµÀÌÙ2;IUWJNF;+õ²‰€€€ˆ‰‹—¡šš“™šœ¡¥ §±«»Ýí\n5>?S[ISYE0Ó¬€€€€€€€‡‹Š‰‰‰Š‰”¥ª³»ÄÌèö&2@T]_NTI;âÀŸ€€€€€€€ƒ‰‰‰‰€†Ž™¥½ÉÞæÿ .AK`aTP@1íÒ©€€€€€€€„‰Ž‘‘‘‘–š¨ÆÇÜÞã÷$4<DK]XTTH7#\fýàº€€‰‰€€„‰Ž‘˜š£º¼Ûú\b.>A?O]]]]LA.úäÎ¥†€€‰‰‰‰‰‘˜¥²µ¿Óî*:DLL]]aUQM8320\n÷Ý±‘‘ˆ€‰‰‰‰‰” «²µÉä÷*ESMPUYc]YNIDD=ô×¹«¦˜€‰‰‰‰‰™£«¹ÊÚú#EOLPOLJLPM>&\"$\bç¿®««‰‰‰‰‰‰™£°»ÄÍäæð\a#%&=GLLKDDJ:ïÌ´«¡š‰‰‰‰‰™£°»ÊÍÓÕßö!)<BLLLLMLF=îÖ¸«¢‰‰‰‰‰—ž°»ÄÌÓÕßöõ÷ý1=FDILNPXSE4íÐ¯š‰‰‰‰ˆ—œ¢£«©«³½ÎÐÔÕÕÝñ\n1?FDDKNQ_ZN=òÅœ‰€†‰‰’š¡•‘‘‘¢®«©««³ÔÛáþDFDKURZZZK>Ý¥€€‡‰‰ššššš‰‰‹˜šššª¯¾ÄÙß\f:HEURZUWKH,½€ˆ‰Š–šššššš’‘†€€ˆ‘‘‘ž²µÄÜð%8BY][ZWOH<Î€ˆ‘— ¢¨°³³¯£›š‰‡‹‘‘žª´¼Òé\b!=G]][ZQNH=2€ˆ˜¬·º¿Ä½»³«˜‘‘‹’‘‘•ª«´Õî!=GWd]bTNH=7««»ÎÙÛÖÍÐÌ¼´£—‘‘‘“š–•ª³»Úó!8KPef[LNH:.³ÌØãëáÛÛÞÚÏ½²œ‘‘‘“šš¢³³ÁÝó!8SRl`XLNH7'ÄæþôïíïèÞÕÀ¼°Ÿ˜™œ¢¢¢³³Íëò\b7OYd[RGJ:'!Þö\b\b\f\nõèÞÕÀ¼Á¶¢›œ¢¢ª²ÀËíø\nCUY\\SLG@1'!\tÕ÷öèÕÎÍ¿ª›œ¢›ªÂÑåðÿ ;J]_VSLA6)\"ùæ!\bùâ×ÕÒÊ¬ž£°»Ôàíþ'AL^WUS?<,\" \fÈæ$&\výìÛÒÍÆÃÉÚÙæè :O`ZWSD82)\"ø“ï243.!þóìáåáæäÞæ÷\t 0ITTTLD68+\"ÜÍ*@AE;9'üöøúíìô'1HOZOLD48*\"\"ö™€Í=JDB7*#\v\v\v\b\b\b$*,9S]LD<;7(\"\"û¬€€Õö4>PJA:,#\"' !*/CUSDD=>9(\"ÇŒ€€¼ó(-FOC;;5%!\"\"!BCESD@DB5\"\"ñ­Š€€€šÝ *;DLI;3&\"\"\"\"*33LWUSG?>>-\"\bâ¥ˆ€€€€‘¹Óë÷\"+@RUPLIDDDILGPLEA>;$\"í¯…€€€€€€š¡œ°Éäí*?XWOOUUNRFD;?6%\böÕžƒ€€€€€€€€‘‘‘‘‘¦½ÐÝæ\r*2BZSFD:*\"\aïÔ¨€€€€€€€€€€€€€";
int iE04 = 31;
int iE14 = 42;
const int N4=124;


const char Arr04[]=
"€ƒ„„„‚€„„…Š”œ›™œ°ÀÍì\f!\rã´™–ˆ„„„„ˆˆ‡€€‚–ž¦¨¤±½Îò'6\"ô»Ÿš’“ˆ„„„ˆˆˆƒ€€‡”œ¢§ª±¿Êì 17?*ú»¥““ˆ„ˆˆˆ„„ƒ€„‹—ž£¨­¼ÍÜ-:@F-ûÃ«›““ˆ„ˆˆˆ„„ƒƒ†•›ž¥¨´ÊÜ$6@GG*ÿÇ¬ž“…ˆˆˆ„„„ƒ‡Ž˜£¨­ÂÜð#.?HHM0Ê®ž–Œ„ˆˆˆ„„„ŠŠ•ž§¬·Îç-6;EJL1Í± –†„ˆˆˆ„„‡‡‰šŸ¥ª®Êã\a+99@DKP2Í® –†„ˆˆˆˆ„‡ˆŽ¡§­ÁÑö#44/8IQP2ÿÍ® Š„„„ˆˆˆ‡ˆŒ–Ÿ£ª·Çï#7!#,LTM/Í® Š„„„ˆˆˆ‹‰Žšœ¨¯¹Ü$8%\a+OPN3Í®›…„„„„„‹‹—š ©¿Òû +/ø*MON3ÿÉ­—…„„„„„‡‹‘™›¨¸Àá(,\rìâ)GOS3Í¯‹ˆ„„‡ˆŒ”š °¾á)+ýÙÓ÷\"CSW7Ì¬šŒ‹„„„‡ˆ”ž©·Æ÷#*úáÊÐî@WY7Êª—‹ˆ„„„‡‰’œ¥´Áè(%\bßÈÃÉêJYZ;Ëª—‹ˆ„„‡ˆŒ“Ÿ°»Ù/ðÊ»¿ÈêJ[[;þÆ§–ˆˆ„„ˆ‹˜«·Îÿ2#\bÑµ±·Àï\"LY[9ýÅ§–ˆˆ„„ˆŒ“œ³Àë+)ã¾¦®±¾ó-Rc`<ûÅ¥•ˆ„„„‹Œ–¥ºÚ%ïÄ©¢¯²Æú,Vga;øÅ¥’ˆ„„ˆŒ– ±Îú.'\fÒ´žª²Îú.Vg_9ùÃ£’ˆ„„›¨Æñ1,êÁª˜™¤µÏý.VcZ6õÅ¥•‹ˆˆ“ ºÛ-&$øÌ§œ”–¤¸Óÿ.VbZ3õÃ¥–ˆˆˆŸ¨Çü(97Þ¼ž—““¦¹Õ2Zca=þË¯ ”—¤Áç81,ý×´¨£š£´ÆÕ2ZdfCË°¢˜žž—°ß111íË¶­¨¦«·ÆÔ6^hgCÏ²¦žž”¦Àö%7<(ýÛÄ¼¸³´·ÆÓà\vAdigG\fÖ½³ª¢›®Ý;H?úÒÌÄÃÂÀÅÙãî=`hgHàÊ¾µ¾¼Åù3LS9êàÛØÕÔÐÖëòýHdljU&øã×ØÚÔçB`^<\tþ\v#;Oahi[<úôç)GP=*\t\büüû\t 'AQ_deL,\nþùýìò%?4%\n\t\r*+0IQ[^^F)\bþúèî'$$! %/8>?MPW]\\F-'ûò\r%'0<@=PX^b]I3*\f\aøßêëððëñïîíéôùû\a4J^`W8öíîêàÁÐÑÐÌÌÌÌÌÌÐÕÚÞìúüAX_Y1ëÙÒÐÐÌ¦§ªªªªªªªª®³½½ÇÖÚè;W_X*ìÌº²±µ²““““““““–œž¦ª´Á¿Öý0Q^S$êº£›—ž›‹‹‹”˜¡¤¨³¼Öý2OXOå·¢—“——ˆˆˆˆˆˆˆˆˆ’—ž¡¤¬¶Íú0KTKå·ž’‹“„„„„„„„„‡Œ“šœ£®ºÍú0KQG æ·ž‘ˆ‹„„„„„„„„‰Ž“šœžª»Ïú0KOC!é·ž‘‹ŒŒ€€€€€€€€…ŠŽ”œ¢²ÅÕ0IOC#ðÁ£˜Œˆˆ€€€€€€€ƒˆ‹–œœ£²ÅÕ0IOC#óÃ©›‹ˆˆ€€€€€€€ƒ†‹’–ž£¦³Çä\a1KLE0É¯Ÿ’Žˆ€€€€€€€ƒ†‹’œ¢«±ÄÜô5MLF0\vÙ¶ªŸ”‹€€€€€€€ƒ†‹œ«·ÂÐÝéû\v(FGE9áÈµ¨Ÿ—€€€€€„„„‡‹ ª¹ÉÔãëñø<55&ñÔÃ´§Ÿ";
const char Arr14[]=
"€€€€€€€€€€€€€€‡ˆ””¯¶ÌÐàùÿúëùóäêéÁ©¦Ÿ›™Ž€€€€€€€€€€€€€€‰”š¨­¼Äáü\v\r÷çÏ¹¬¤ ”€€€€€€€€€€€€€€‰”—Ÿ­·ÃØõ((\"ûàÁ¨›”‡€€€€€€€€€€€€Š””œ¬²ÃÑð#*(%#\"+6,åÁ¥›—‡€€€€€€€€€€€€Š”›¨²½Ìï\b!.=0(!)9=.\aå¾›—Œ‡€€€€€€€€€€€€Š”˜¥¯³Ïõ*.9;/*:C=-Þ¶‘‘€€€€€€€€€€€€…””¤¯´Èçý *0@<97IOI4ú×²Œ€€€€€€€€€€€€…”¡¬·ÄÛøö&88=?DENTK3ùÅªŽ‘”””€€€€€€€€€€€‘™¨³½ßù\v$45.9CNNWL1'îÆ®”””“€€€€€€€€€€€”¨¶ÄÙñ+(1,<OVNI61'ôÍ©”””‘‡€€€€€€€€€€€¤²¿Óî\a\r\f$))HTV@DB3(ûÌ¡‹€€€€€€€€€€€‡˜³»Îç\n$6KMDE<>9)ùÂŸ‰€€€€€€€€€€€‡”´¶¾Ù\"'3OIACB<7)óÁŸ‰€€€€€€€€€€€©µ¼Û\v\rþ#/<C?IB69-\fîÁŸˆ€€€€€€€€€€€‘©±¾Ô\r\v\v%@C@@=9;'\aîºŸ‰„€€€€€€€€€€˜«¿Ø\r\nýõò\n @9>CF=;!\aîºŸ‰„€€€€€€€€€†•ªºÕû\t\b\a\bìÛèó\n\"<?HCF:5\aîºš„€€€€€€€€€†–¦·Ñë\n\béÊËÔê\n<FICI:.\aî´˜„€€…‡€€€€†‘œ­Ïê\a\r\v\vñÌ¸·Êæ\tCAKCE0.\aî´”€€…‡‡€€€†‡›´Íè\tþñÔ²¥®ÆãECKC?0.à³”€„‡‡€€†‡´Ìã÷\r\rìÔµ¥›§ÃÝ\a*FNMI:/.à³”„ŠŽ€‡‡•°ÇÝõ\t\fôß¸¢œ•§ÃÝ\a+LFHE7-)\fè¼¡”š •‡‡©ÁÚõÿðÀ©”“¡Æê/ORPG<3.!\rêÀ¥—œ™š”‡¥ÃÛÿ\nöÈ«›ž˜¨Ñó/MOD<<3.\bê¸ª¡š–¢¨‡›ÂÚ÷\vÒ¸¨¥££¨µÞ1MOD<<0)âÀ°¤Ÿ¨®©®×ñ\"&ã¿¯¨¥¢¨¯¼ë\r,>UOA<?:70êÍ¼²­±µ£¨Áç\n$-) õÉ¸³´°¶»ÃÊõ->UCFLLDJ8øÞÇ·¼¼¶£¯è\r$-0.1%(ÚÌÆ¼ÆÊÊÊÊÐÿ+>UFKPLFHG0þç×ÏÆ»¯Ãõ!04<A<@\"ýùóæåçëëëë÷ 2BTM[[iaaJ6\"æ×ÑÊÁ¶×+,5>BF=$üøòòôý\t!*:E[W[]ZNF>/ \aþîãÜÒÑë\"*9CQC-\r\r\r\r\r2?HN[W^RIDA<00\a÷éÝÖ×!.:BI>2!\r\a\r\r\r(?PZ[WZYLD=B<5.øùôõñ %3%\n\t\r\"?RZPWSG:550' \bþ÷õééå!#\r\r\r\r\r\r\r (-2FX\\^hSE3.),(()\rÿøøòë\f\f.IUbbdMD75/3-!\tüöðìò\".0@IYbbbMD3.)1)üùøò×Þèéëëòòòòòòòòòô\a29RYXP@6*(\"\"ýúõæÞÜßÞÃÂ¼¼ÄÊÊÊÊÊÊÊÆÃÃÆÏßëñ+99G=3((\"\"ôÛ×ÐÃÃÄÏÊ›§¨¨¨¨¨¨¨¨¨¨¨¥¢¤°ÏÜåø\r%--GC0!!\açÊ³¬¨¨ª®®“”””””””””””–Ÿ¶Ì×ßñ0/H=/!!\açÊ¬Ÿ›››š”‡†€€€€€€€€€€€€‚•¯»ÃÓéù$2H92(!\açÊª•‹‡‡Œ‡€€€€€€€€€€€€‚‹™²»ÇËìù&5C82,#\açÊª•‹‡‡‡€€€€€€€€€€€€€…–¥²»ÁÌãÿ&/G92*&éÊª•‹‡‡‡‡€€€€€€€€€€€€‹”›¥²·½Ëä&*6.+(&\rëÍª•‹‡‡‡‡€€€€€€€€€€†‰””›¥©°¹Ëç\n!*</+,*îÎ°š‹‡‡‡‡€€€€€€€€…‡ˆ””–™™©°²Èá2#ÿí×·ž‹‡‡‡‡€€€€€€€„‡‡””—–Ÿ²¼ÆÖî\n\f\r\f$\fúáË®Ž‡‡‡‡€€€€€€€„Œ”Ž’›¤¢¢°ÌÜÚçÿõþ !!!íÎ¶¦›››";
int iE05 = 29;
int iE15 = 41;
const int N5=124;


const char Arr05[]=
"ƒ“¡½Úê\a\t\f!&#\nïÊ‡–¥¿ä**09:8<==>@<974>IQJ9¾ƒ–«Èù7AIQ[\\^aaaa`^_aahjj\\=÷®ƒ–¯Ì,CGL[a^ceaaaa`^^^bh`Q*Ü ƒ™¯Í*<<EORX\\PMMMMMMQW\\`WGÈŸ‡™¯Ï\f1;/*0**.*!!#&&'-0/+ýÚ®ŽŠ™¹Ý7>&ýóñèãåçèêéêíáÑÃ²•‡Šœºê92#ïãÙÑËÌÌÌÌÍËÆÃ½¬¥šŒ„ŠŸ»ç8/\aùåÙÒËÂÂ¿¼¸¶³°ªœ˜™‘†€‡Ÿ»ì1!\féÖÈÀ±ª¥¤¤¢ŸŸœ›—–—Ž†€‡ ¿ï#7&æÍ¾²¤œ”’‘ŒŠŠ‰ˆƒ€‡£À÷&<+åÎ½´£—–”’‹ŠŠŠŠ‰ˆƒ€‡£Ãû):'üÝË¹«š’‘‹‹Œˆ‡†‡ƒ€‡§È07ôÚÃ·­ ™ž—•™•”“‡ƒ€€€‡§Ì\f6?ùèÐÂ·¦£¡¡žš–””‘‹ˆ„€€€ƒ§Ï8C%ïÒÊ»¶ÁÀÂ¾¸¶¢–”‘‘ŒŠ…€€ƒ«Ï;G+\nõâáÝäçíêêçÝÎ·¤“’‘ŒŠ„€‡«Ô>G/\n\n\r\v\tþüúôïèàÍ¸—‘‹‰Š¬å=9++4A:.0463,&\bòèàÃ‘ŽŠŠ³ñAEEATPKE@B>GAA>91õåÆž‘‹‡Š­ð29FLM>4&&+7?LKJA/ìÁ›Ž‡Š¬è0?>=.\r1>KZWM:ñ·‡Š²í$#öëíâÙØàô\t=Pa^YEæ ‡Š©ÙïõîáØÒÇÂÁÀ¿Ìâ9QfgYC\t·‹‡œ³ÈÓÕÉ¸¶¬«­¦£¦²ÅÖì\b@aljV=í‘‡•¢³³«¤ž™–—•™›Ÿ ¯¿Öç.JamdD¡€Š‹’Ž”‘‘••’’–™£±¿ÕöC\\mn\\7À€†„Š‡‡Š‰ˆŒ‹”›£³»Úü0RglgRïƒ„‡Š‡‡‰‡‡‰‹ŠŠ‹‘™¡©¸ÃîIdklV‡‡ŠŠŠŽŒ‹Œ‹‘—œ¤±ÇÞ\t>_jlX)ƒŠŠ‘‘‘‘‘Š‹‰ˆ‘—œ¤¯¾×ÿ7_jl]=ƒ‡•—“““‘‘‘ŽˆŒ‘—Ÿ§±½Öü4]hj\\=‡‘—šž—‘‘Œ‡Œ‹ˆ—Ÿ©±½Õö7aim\\:ž£¡¤ š‰‰Š‘‹Œ–¡¨°»Ë÷:bhj\\0ž²µ°­©˜“‡‰’Œ— §±ºÌ>bhiR¼ÅÍÒÏ¶›––‹ŠŒ’‹Œ‘›¥¨±¹Ñ\tGfjjKýÌã×Ü×Ä§œ™‹ŒŽ‹‘ž¤ª²Çè!Wclb5²ÖðóèßÇ³¡žŽŽ‘–£¨­µÏö0\\ejV•Æ÷ê×¼¢œ’‘“—ž£«°Âå\fE^lgEëŒÝðØÅ« ™˜™—•š¡ª¶Ãßü1TbgM°ˆÖ\"úëÓÂ­¨¢š™¡¤¨¶ÈÝõ B\\f\\/ß”ƒÌ\t)'÷ÞÒÉ»·¶®²·»Ëæÿ;[`^?§†ƒÆ\v.:.ÿôëÙÔÏÐÓÜä9Waa@¹ƒƒÖö\">D?,üþ!>Tdb>\v¾†ƒƒÏç2OXUC9/  $6I^_T9µ†ƒƒ€Éáõ\r.Je_VKC<8>FLZ][Jï¤‡…ƒƒƒ€”ºÏì#FfpliaY[__UI\"ó³…ƒƒƒƒ€€‡“•¡¶Éß%7^gbXDðÅ•‡…ƒƒƒƒ€€€";
const char Arr15[]=
"€€‡‰¦µÂÔÓàêìíúóòöûûü\r\b\r\r\r\a\nöÐ€€‡ŽªµÂÔßëûû\f\a\t\a'*''''''')=AAC;ICýØ€‰™ ¼ÊÞñù$'\",0>AJMJJSSSSNJS[\\\\TVOù½€€‘ ¼Ïâñù$)05GJBJMJRSU\\\\\\\\e]de]ZOä½€€‡Ÿ¿Öìô!'-399ES\\]a_jmmmmmmimmml]N3Ê¥€€‡Ÿ¿Öì÷\v!'-39@JX\\]fj^\\\\]b\\\\\\eeecS:ñ¯¤€‰·Ìê\r!'('-0ESX`\\SSOJJJNSSSSNA8ûÌ›’€€½Ïê\"'!!!-AAAEJA>92000002)\rôß·‘‰€€‡½Ôñ\"'$!.9AADB9,'' \vüîÙÄ¢ˆ€€€‡´Üò ',''1AA@D9'\rõòòðêêäÙÏÅ¶¡ˆ€€€‡´äþ\r'$\f''\bÿëâÉÆÆÆÆÄÆÀ¾¾¶¬²­š€€€€‡´Üþ\r#\f\t\rüñãÎ¹µµ®¬µ± £¬¬¬¬œš•—‹€€€€Ž¿å\a\tøûñÚÁÂ­¬¬¢ššššššš££šš”‰‰€€€€Ž¿å\aïøûæÐÅ­¨›šœ“’’’’’’’‰‰‰‰ƒ€€€€€€•Ë÷ÿøïÔÒ¾³±¬©ššššš•’’’’‰‚€€€€€€€žÓ÷ÿ\n\aûøòéÏÈ¾¼º½¾¾½µµ¦š™‰‰‰‰€€€€€€€€žÓ÷ÿ\n\n\t\aöôòü\t\rëÏ¾¶«’Š‰‰‰€€€€€€¯áþ\f\n\n '1AA=9920*âÌ¹ª“Œ‰‰€€€€€’±áþ\fÿ !EB;:AS\\\\\\TSSG.#\aåÏ± Œ‰‰€€€€‘²ëþ!&%)00GRSUQJS[edde^YSJ6øÚÆ¨‰‰€€‰ªÉéþ\v,049AKVS@0*-9@FRSQL^e`M-\têÒ§Ž‰€€€¡Éïù\v$4===B;90*!,49@YZSV_m`F(ôÕª‰€‰¡Éø\b\f-03+\"!&0;KZ\\YZ_YS>,$\bÜ¤‰€‰¢à÷\f\r\r\n \tÿûý\f\r\r 39<LPKX\\XC2'$Ô€‰¢à÷þò\t\r\n\rÿöúðçèêöû)3AKNS\\XB9*'ù¯‰‰«Øïòêç÷ýûòòìäàÔÅ¾ÆÏÔèý)26DJTXB0*'!\fì‰‰«ÃÆÌÚáèîâÏÏÈ¾»¾±´µ½ÇÓãâû%06;TXB<'''!ø›‰¢³¬¥—’’“©®­¬¥›–’ ­µËÓØäí *>?MXJ<'''!ÿÐ’š™‡…‰‰‰’˜š”’‰‰‰’ªµ¾ÎØÐãö!0>GQB<''!‰‘‡‰‰’’’™‹’’’‰Š¢²¾ÂÈÏÞú\r'3CEJB<''!‰‰‡‘’’˜šš’‘’’Œ’“šš±½¹ÀÍà'2CED<8''!\r‰‘‘šŸ£¤­§££›šš‹—š¢±¾¹ÀÍà-2E?=<8''!\r’¢¥²¿ÁÊÇ¸²¬šš˜•’—¡¤¹ÂÀ×ð\f-2E?=<8''!\rš´ÅÌÏÒÖËÈÆÆ´°¬£™’Ž•µÅÆàú-/6969&!µØéæéñêèâÏÆÅ´¬ž“‰ ¹Ëãú\n-0,069&!ûØ\ný\rúòòæÏÏÇ¾²£‘‹ž©Âìòú&05.691&\"\r¾á\t\vþøòöìÝÑË¾¬Ÿ ¡»Øäú\f)'\"&=9- \"ö’ò'þûûûï×È¾Æ¶µÈÕîò\f)-$*9-ãá.0).#\r\rìïÛØÖÛÛãòÿ*7*-,3,#´Ø\n,62?0'$\r\tûýôáíò\"62--+*#\bÛ€Æ\v3PDA9,'\r\aÿö\a+,%8@/') $å©€€Ø\aò2PLA950+'\r\a\t!00/8:.'$%å²‚€€¬î\tER\\J<*#\r\v#'++8:.'&&í¾‹€€€£ï\r2NTH92\r'%%\"0/\"''$'\vß©Œ€€€€¾Ñù&+DO=4'&\"2999/080+) )'íÐ—‰€€€€€šÄÛòû&\"FY\\VSJJB>*$0/(') øÝŽ€€€€€€€€¡³Ìîû÷üIWUSD2692''(!úêÏ“€€€€€€€€€€ˆŠ—¡°ÄÒèîôü520+þòñÆ´’€€€€€€€€€€€€€";
int iE06 = 27;
int iE16 = 38;
const int N6=123;


const char Arr06[]=
"€„„„„„„€ƒ‡Š ­ÆÓèø\t÷èëìÍµž–‰„„„„†‰Œ‘¡µÉÓç 0CI5ûß£“„„„‡ŒŽ ³ÄÎàí\v&AOK='ëÌ°œ…„„‡Œ‘Ÿ¸ÆÔáý\f%BFD5 ü÷æÐ¯™„ˆŒ‘·ÉÒæù\t\f1>:, öæáÚÊ²”‰„ˆŒ—²ÈÑêþ\f\v(ïèÖÌÊÍÖÐ¹Ÿ‰‰–ªÃÏèÿ\tíØÌ¿ÁÀÁ¾¾Æ¾¡‰‰Ÿ¾Îßþ\r\f\tþÝÎÅ°ª©¸¾¿º¸±š†‰”®ÎÛ÷úáÉ¿°°Ÿœª»¼º²°ŠŽžÀÝî\r% \tèÆº©®£¢™ž³³±²¬¤‹«Ðæ$/\fôÍ½«¦¢œ—˜–œ¯¯¬©Ÿ‹”»Ûü :%æÊ¯¦ ˜•ŒŠ“”Ÿ ž™•ŽÊç4E øÑ¹© ™”‰‰‰‰Œ‘‘©Úü)G.ÿÏÇ±£ž•Œ‰‰‰†„†‰‰‰‰‰ÅåFS0òÎº«¤˜‹‰„„„„„‚„„„„„Ó÷/PO+ØÅ¸¬š“‰ˆ„„„„„€€€€‘ÚFZJ(ûÌ·µ­žœ—ššžž“‹…„€€€¢ä&T\\;ôÐ»·²ÁÈÈÈÐÏ´¥Œ†€€€¯ú=X\\AàÁÏÙÑîùùÿîÓ±£•Œ‡€€ÍQ[b?ÕÙø\b\f '+'ÿÌ¥–Œƒ€Õ.\\`_;\r  ,-0A:0Ü¥“Œ„ÞM]`Z2'%)#\")79;GHB(Þ¡„ïQci`B'#*#þæâçÿ3FTTSH$Õ–‰\fVfpaN51\aîÈ»º¹Åãÿ0@NWOJ»3ZjobT5ûÏ¸­¦¦¢ª®Áç1DP]W@Ö”LeopcS0üÅ²¬©¢ ž¡¨«·ú=KWbR%£Peso`CÑ¸©­¥šœ¤««·Ç!OXeeL¼Ynss^0ìÃ­ž¢œš’“œ¥¦­Àø?QbiXàansw^\"Í¶ª¡ ˜Ž™š¢¨¶Û4\\dgi(fnvt]É¦¡£ž•™šŸ­¸ÊZfglKarwu\\Å£ Ÿ¢™‹‘šž ª¶ÀÿNdqp[]vwxWÃžœŸ¢™•‘›ž ©±½ÿLdqugDrwy[À˜—¢™‘‰„’œœ¥­ÀûF`pqk&uwyb\nÁžŸšœ’‰…„•œŸ®ÀûG`pqgûtswhÁ¡š•—”‰‰€Œ””Ÿ©»÷GbmqcÙhwwh2Î¤œ˜•‰‰„Œ‘’œ¬¾ÿGbmlR¦Vwwh?â§——’‹ˆ‰„Œ‘–™«Ã\rJ`nm¦<ssfL\t­—•—‹ˆ‰‰•“ž´Ô#OfraÁžübwrb%¼š••‘ˆˆ‰’•—Ÿºò/UgoI¨šÅSspb?ó¨••‰‹‰—š¥ÌC[g_–•²aohP Ë¥•’Š‰Ž”—½ò&DekMÇŠ‘¤ÕHkjcBÈ®–”¤ºå6Ne`‰š¶\r_hmb>øáÄ®«­³Çñ\f2F_`<ÂŒ„‘£Â bmr]>éáàäçû1J`aLà“‡„„’£È(cnp`Fþ\f3R\\`Uì•‡„„„„•¥É$_qoh_C?;@N^^cIÚ†„„„„„‰Œ’ ªîWrxvnlhgca^¥‹…„„„„€„„‰‰‰‹’Î*[oriaPò†„„„„„„";
const char Arr16[]=
"€€€€€€€€€€……‹“²ÀÜåðþ*(÷ãßØÁ¼²´³´­¥€€€€€€€€€€’°Õìð&./21>7&ùÙâÛÌÃ¼° €€€€€€€€€Œ«Êïø,' */65359ðÑ¼®¨¦›€€€€€€€€‘µÞô\n()$(/0# \"-0\"×¾­¨¤›€€€€€€€”¿ì÷&%!$%$%\f\"ðÉµ«¡€€€€€œÇíø\n # (&\býô\b\bÿü\nìÎ¸§›‘€€€€€™Ãâõ\n(#!/1ÿõîèòûûøýüïððæÛ³ š‹€€€€—Áä÷'\"%-(ùóèÜçõòïññæßÙÕãçÜË©‘…€€€†¯Ûõ\a'&&*ýôçàÜåãÚßßÖÓÑÐÕáäÛÏ­‹€€©Ïð('*,\vößÛÕÕÊÑÔÌÁ¿ÇÅËÔÖØÖÌ³‹€€†¹éþ &/.*\rùçç×ÐÇÄÆ½··»½ÀÁÎÕÖÏÅ±’€€€®Ûö)/0*\aëãÝÙÅÁº©¬³°®°µ»ÀÑÕÊ¹š…€€»ò&/90$\bóãÜÎÅµ¨˜™¥ª°µ·¼¿¹·°¥‘Š€€’Øü&.6>-(\t\tÿíâÖÄ¸¦–—œ©¥§®±°´©¤›‡……€€´ð+5;2(\"\f\t\fÿíÜÉ¶¥˜’—ŸŸž¤¤¨­©›Š……€€Ì*49>5(!êÝÂ¯¨ ›¢«¬««®­¢•Ž‡…„€€€Ü\r2:=A/) ýë×¾ÃÀÀÂÆÏÐÕÈ¶°®£“Œ‹ˆ……€‹ð'5>?D.($\bÿîÛïîõÿ\n\f\nùæßÄ´¨šŒˆ……€°\v%7ABDC/-\"\v'0AJJGA(\tíÞÄ±‰……Ð%7CEF==424<;+(**%\"2DLSZZOB6çÒµ›Œ……à /ABHJMHFETF<+## 2>IMQYZO=0øÔ¶•‰…(9BGL[XSV\\QA*+$ûù'=S__b_NF3ýÖ·’…%AINUabfj\\?80\fýïëõý\b,DSZab]QI;%Ëœ†4BMTennn]F9$ûåàÝàäèñ!E\\[^hcQA8÷»’%>HZhkopkS='\vðÖËÐÐÑ×àðF[^ei^SC3Ô˜%CObpvwldE4\"\bóÏ¸¶¸µ¸¾Ùëìú&CLY^cVL<*¬/HWluzwiS?,òÖµ¢›š•–§½Óáñ\v6E[_aWTC4Ç?N^t{ztfK0êÛÅ¢’‹ˆ‹Ž”²ÈÜáõ=L_\\UTF:)Ü?Xg~{zw`;$ùâÎ°œ…ƒ€‡“¤¾×ãñ\r1K_\\UTH86 J^p~{wr\\1\"\fëÛÈ° ’‡ƒ€‚•·×ãï\a'DOVRRH87/%cz~{wmR0\fçÔÈ®œ’‹ˆ…†‹“´Ñàí%?KVRSJ=85mz~yrlF*þâ×Ãªœ’‹ˆ…†‹“«Ïãó':FRPPG=85vz~yoaD!þâ×Ãª¡’‹ˆ…†‹•¨Ëáõ'2=ROKG=7/Úry~wkaF%þäÛÇ±¢—ˆ…†’š®Ñëø\"2=RFDD97!ÕIyxodcB$üèÜÓ¸§ˆ…Ž—ž¬Òìý .:KEAA95Å5rugd]D)þïàÕ¿®§Ÿ‹“›Ÿ·Ýó\b&.<@?@=83òÀ\\ugd]F-þèÚÌ³¨¢–•›¡®Áæü\t+:GBBBA7žµÙ@ma]^TA'úòåÑ»®«« ¥­¸Òìý\f +:FD=;92\fƒ«É\aOe^_XA0\aúõÝÌÄ¿¶º»ÃËã÷\a'-9@?;76×¥ÃØ$Y\\_YF:,þõâÕÕÑÐÔËÓè\t%8CB>74+ÿ‹€ ¯Èé0SXZTG6!íàçàÕÚð\n$2@>>;20É€€¤ºÅð5TV]QD4&\tÿ\b\vøúö#\"5AE@;40#Úƒ€€…¤¬¸Âú<RUTSE=3,\t\n$%3CE::61#×ƒ€€€€•¢¦¸Éø=VZUXVQF=2##'+;F@?B90#Õ‹€€€€€‡•¡¤²Âè8[dc`_]L<2--1.*>A<D?50¸€€€€€€˜£°¼ÏVpnf_RF86/-3BBDE@4í™€€€€€€€€€ƒ‘•–ž¥³ÂÙ UdjheKA?@HCEC@ä›€€€€€€€€€€€€€†‘•–ž¨¥©²Ãô3RQIBC?8%Ó‘€€€€€€€€€€€€";
int iE07 = 24;
int iE17 = 35;
const int N7=122;


const char Arr07[]=
",<BHPNLLEK>;;3333333<HS,Egmnnnknl\\UUUURLLLRU[J+Ifhnnswuoia]]]]]]]]bb:;Qhnntwwuonne]]]]]]afY\b6R_eefffff_]]WQLLT]acJÞ\f%,2+(\"\"\"\"\"\t>]b+ÇÍã\a\r\fÿìæææææææéöô$AgLþ²ÄîýúÝÉÄÄÄÄÄÍÍ×àíñûS`;ç¨ÄîâÕ¹¢œ ¥««µÀÒÞæî\a(ZhÇœÍõÛÂ¯“‘‘‘‘ž¢³ÄÅÕü*c;î¸’ÕÚ»¥œ‘‹‰‰‰‰“¢ª¼ÊàRh*Þ­‘ÍÀž–‘‘‹‰‰‰‰“¦¯ÅÐú%T:\fÍ£‰¼¸ž–‘‘‹„€€‰‹¦¹¾Ø\v3[6î¹š‘«ž‰‰‰‰‰„€€‰š¦ºÆêB;â³–‰š‰‰‰‰‰„€€‰šª¿Ýú'GCûË¢–‰‘‰‰‰‰‰‰„€€‰¡³Çñ*20ñ·”‘‰‘‰‰‰‰‰‰„€€š­»Ý.8Då¬”‰‰‘‰‰‰‰‰‰„€‰š³Èí3A5Îž‘‰‰‘‰‰‰‰‰‰„€¨½âþ&5A$ìª’‘ˆ€€€€€€€€€€ ¨Äæ\t+/5\fÛ¢‘‘ˆ€€€€€€€€€†¡¨×ÿ'018Àš‘‘ˆ€€€€€€€€€”¤Æá\b010-ô¾‘‘‰ˆ€€€€€€€€„Ÿ­Ñõ%,6ßµ‘‘‡€€€€€€€€€ˆ¢ºß\t*'%,Ï¢‘‘‡€€€€€€€€‚Œ¥Âû*+)$¾“‘‘‡€€€€€€€€‰–¶Õ%.%-&æ¾“‘€€€€€€€€€‹¨¾è\"*&-Ï´‘‘‡€€€€€€€€‰‹­Ïê3! #ó¾¡‘‘‡€€€€€€€€‰—°Ø!5&,&ç¾¡‘€€€€€€€€‡‰ Àé4*!%ß¶‘‘€€€€€€€€‡Œ­Õ÷2*!!õÙ«‘‘€€€€€€€€‡µÝý46!*óÙ«‘€€€€€€€€…‹¦Æí2.\"&\tîÑ¢‘€€€€€€€€…‹®Ñù$;(ùëÄ¢‘€€€€€€€€‡¢¶Ùø-;-%üò¾œ‰€€€€€€€…‘©¼ñ5,-,\f÷ò¶¥‰€€€€€€€…–¯Òî5$.'\böä¶¢‰€€€€€€€Œ¤°Ûû#2-\"ûëÔ´¢€€€€€€€Œ¤»æ,0+óëÌ´¢€€€€€€€Š˜°Äî.0*\"óÙÄ³™€€€€€€€Š¡µÇ\f)(÷áÆ°”€€€€€€‰Š¡»ß\b)!(ÿóÕÅ±š‡€€€€€€‰Ž®Â÷'-#÷êÍÃ±Ÿ†€€€€€‰–·Ðó\t&'û÷âÍ¹ª¨†€€€€€€¦ÀÝú/÷ÝË¹²¨‘€€€€€€­ÎÝó\t&!\aôÙÅ¾¬Ÿ‘€€€€€‰­Ëáóü\aéÑ¿¹£‘‘€€€€€š´½Ûåîûõã÷ýÔÄ¸¬›‘‘€€€€€";
const char Arr17[]=
"Û\r#-2/'(&)$(+++++++)()(('\"#%,,+ë*:@JQSLJMMRSPOMMJFFFFFGHFEFHIPOB%ò<HU`bdejmkkkkkkkklkkjnnnhhjhjljRõ\":JZbijknrrqprrrrqnnnnqrronruvzrLõ!AKW[^adejgghhhhhhdddeddhgjnruqX3ýë/;FGFGIJPNJLIIIGGFFIFGLGKZdqsgC\nÑÞú\r!ýýûù÷øøùùùùùùûúû<_slOë³×úøêàãáàÞÞÞÞÞÜÙÞÞÞàèìùþ=ac[4ùÑ©Ñìÿ÷ïÝÓÑÔÐÍÍËÈÇÉÆÃÃÃÆÈÔãî\a'O[X<\aÞº˜ÆãøèÚÏÉÄÃÂº¹¹º¼¼¼¼¼¼¿ÈÒçû<NQI%ïË¯’ÃãìÜÍÃ½°®¨¨¨©¬¬¬¬­¯²·ÆÖç\a'CJG5ØÁ„²ÓÏÁµ®¨ ¡›››œž ¢¢£¥¬·ÂÚ6KA?èËªŽ„¶ÏÁ¯ª¢Ÿœ———˜›››™› ¥´Êî\f$CA?+ùÚÁ™…ƒ¥¸­Ÿ––’“ŠŠŒ‘–¬Àâ\b8EA8äÄ¥’…ƒž«šŠŠ‹Š‡„…‡‡‡Š”›³Óö*7C=ø×»˜†ƒƒ‘šŠ‰‡‰‡„€€„‡‡Œ‘™¯Êí4E>3ÝÈ¤•…ƒƒ”ŽŠŠŠ‡…ƒ€€„‡‰‘—¥ÆÞ÷0=?0ëÓºœ„ƒƒ‡€ƒƒƒƒƒƒƒ‚…‡‰•š¹Ûò\v 7>7)âÊ£•†ƒƒƒƒ€€€€ƒƒƒƒ…†‰‹’˜¦Éãý1<9%çÓ¸Ÿ“…ƒƒƒƒ€€€‚ƒƒƒƒƒ…Š‹‹•¤Ääý&4;2\"\vçÎ©˜ˆƒƒƒƒ€€€€‚ƒƒƒƒ†‡ŠŒ’›­Òî\b480 ñÖÄ •‡ƒƒ‚€€€€€‚ƒ„‡‡‰Œ‘’›¬Éâ\b(40*!\båÏ«œ…ƒƒ‚€€€€€€ƒ‡‡‡‰’”¡¶Úü,4*!øÞÆ¦™Š‡…‚€€€€€€€„‡ŠŠ“®Ìñ\r%/3.çÕ²¢”‰„ƒ‚€€€€€€‚ƒƒƒ†Œ‘—«Âáÿ'8-÷àÉª‘‡ƒ‚€€€€€€€‚ƒƒƒŒ’—¤¸Õõ(0-%\bíØ¾§—‰‡‡„€€€€€€‚ƒƒ„‡Ž— ±Ëè\"5-$ùàÍ³¡‘‰‡„€€€€€€€‚ƒƒ„’¬ÄÞý\v!00%ìÚÆ¬—‰„‚€€€€€€€‚ƒƒ…‘™¤µÊê'6-!úèÑ·¢‘‰„ƒ€€€€€€€€‚ƒ…™¢²Ááý\v#+0'ñÝÅ²ž†ƒƒ€€€€€€€€€‚†“š¢¶Ìèú'51%ÿé×À¥‘‡ƒ€€€€€€€€€€€‚‹“š®¼×ò\r$/2*ôåÎ´‹†€€€€€€€€€€€…˜©¹Ææÿ*32'ÿìÞÈª™‹ƒ€€€€€€€€€€€‚Ž”°½Ïë$23,!\rúëÎ¾¨•ˆƒ€€€€€€€€€€€‰‘šª³½Þù'35(ñêÈº¢“‡€€€€€€€€€€€‰—¢¯·Ïéû/3/#ûëÞÆ®Ÿ‘‡€€€€€€€€€€€‰’œ©²¹Úö\f$.9'ùçÓÄ«žŽ„€€€€€€€€€€€—£«¸Ìéü!025)ýïáÐÀ¨—…ƒƒƒ‚€€€€€€Š‘ ¤®½Ø÷#-1.\aúêÜÊ´¤”…ƒƒƒ‚€€€€€€• «µÅçù\f+30)ÿöÞØÆ·¤”…ƒƒƒ‚€€€€€€”¡¢­¼Ñç÷\v2,,&\fÿóãÖ½²£“ˆƒƒƒƒ‚€€€€€Š• «³ÂØë*11+\aúèÝÑ»¬š“ˆƒƒƒƒ‚€€€€€‘˜¤­½Òâï)*/)øèÝÎ½°ž–‹…ƒƒƒ‚€€€€€¤©·ÇÖêù\f).,\tòäÛÉ½°ž‘‡…ƒƒƒ‚€€€€€—§¬ÀÎÕâü\r!0*\tÿðãÛÅµ§œ‡…ƒƒƒ‚€€€€€—¡·ÅÐÙçý\vûóéÜÒÂµ§šŠ‡…ƒƒƒ‚€€€€€›«·ÁÈÔèûùïçàÚÏÀµ¥•Œ‰…ƒƒƒ‚€€€€€‘¤¯µ»ÈÜôùóùçâÙÙÚÍÃ´§ “Š‡…ƒƒƒ‚€€€€€";
int iE08 = 28;
int iE18 = 39;
const int N8=123;


const char Arr08[]=
"€€€€€€‚„‹šHSVcibLð²˜‹„†‡…ƒ€€€€ŠÓ4QUQSVXbirog+Ô©–Š‰‡„€€‚„ˆ¨HQOI4'+,8J]`jdR\b¼¢™„€ƒ„‹´MWB-\r\r*BO\\j[Ïª™ƒ€ƒˆ¯OVA)þøøúùú$?OegV\vÍž‰„ˆ¡IWJ'õ×ÑÌÊÆÇàù CSbaP÷´‘„Ò/RK:âË¿´¯ª¦­¶Õø&L[`TÈŸ„šþHUL!\rèÄº°¤Ÿ˜ž¢§­Ö\b:O\\`Eä¨‹Ã STFÊ¿º¬—”‘“—ª¶ë'JYaWý»–í>XVBìÇ¼²¨–“’Ž™ž¤°ÓBYb`ÀšõDRL:\næ¾¹±¤™“’ž¥®Í\b=Va`ÄžöGRNEá½»²§•‹ˆ™Ÿ©Ñ\vAVcb»žöJUSEæÅ»µ§–‹†Œ™›¤ÍH\\^V\a´žöMZSD*òÍº¸¨–ŽŒ‘žŸ©ÜQ`\\Gñ«žòHTVG7áÄ¸®›ŽŠ‘ž›²ø,]]V á¦šÖ/TVM=-Û¾«ž“‹—¡©Ö=`YAþÇš¸MOTI:$õà»§ž–”™¡À÷&MaIä°‘‡¨ð5NSOH;)úçÆ±§¢ µì>UPôÍŸ„›ÉBKPQI:1\aïÑ¹ÀÑé:NR#øÛ±”„Œ¨ØANNRNH62ÿö\b#>QE#áº™‚€„…”¶æ8OTTTUIID7CHQ3&\nÞ¿¤‚€„„‰šÆã7SYZZ[WX]__R;îÅ¬•ƒ€€€„‰“¥Æï#Nei`adiihhgLïÅ¦†€€„–¥Æõ\b*Njpjjnrsjg[@ç³ž…€€‹”¥Êð\a%Cb\\RCSafmlehhU'ô½ž€„¤Çï5ZX8%÷*JW^[gleS4õ¹“„‡˜¼ñA`O.ãÂÀ»Ñÿ$I]Z_iaR/ìªŠ‹¦í%UbR/úÄ­¨ ¤¬³Ûü2LX\\gbT'Í“’ØPg[=þÅ¬¦œ’‘˜¡·Éí\"H]ccaNŸ¡üHemNÏ°¤™’‹‹’š¨¶ÈæO]bbaDÆ´4_sa9÷Ä§š’’‡„‡’¢°·Ëè%VehcZíëVuoPÖ±Ÿ™’„„„‰™§¯µËò9`_`]7gwmJÈ²¢™’„„„‰”Ÿ®³½á*X_faWKwvjGù¼ª¡™„„„…”ž¨±½Ó\rO_fb[axwjGú¾­¢œŒ€€…”š¨°»ÈEXfbXmxwiEú¼­¥œŒ€€…—š¦®ºÊCWd`QptxkEú¼­¢ž‘Šƒ€€„”©ª¹Ç\n@WbYMavvlOÎ­£›”’ˆ†„ˆ˜©®¹ÔGWbY+5vujWÛ¯¢œ–’ŒŠ‡‹˜ž©¯¾ç*HV_Mâàswrc7Çªž—™ŒŠ‡œ¥­µÔ1IYR>¢¥MwukL èº¨  –‘™ ©³Éô#?R\\R–lvp].\fæÄ¯¢žŸ¡¢¬¿Ïõ/EVS;µˆ‡µ=qxoL+ôáÀ·¹»ÁËï*<RT@ë‘„‡—ÊGoznM-üëêóôö)>KTEœ‡„„‰šÓKlxjU9\"\f\t\v'7GLQGÿœ‡„€€‡‹™Å5ntvhZ?2378<KSQVBÛ’†„„€€€†‰˜¤ãUuzzrpji^UUXK\a›Œ„„„€€€€…‹“˜ª\ffsyni_S%²Š„„„„‚€€€";
const char Arr18[]=
"€€€€€€€€€€€€Š¥ñ,:><?MQTGÕ°¦¦ ™—Œˆˆˆ†€€€€€€€€€…•Û,><B@90<Uderxx|vNôÄ­­ª£œ‰ˆ€€€€€€ƒ¦é089CI?84?CFM^idhpppw[ù¿³ª£•ˆ€€€€€’¿þ1:8CC>;=;768?=;HOXYV`exk í·«¤•€€€‚œØ\f04?JC>E>02 \"\"4<HKX_ee=ðÁ§œˆ€€€‘Ù0:@KA77>2(\a\n\f5EKW^mi?ì¯¥€€„É\a,?BPEA264%$\tûôíæìüøø\f8CIU^naÍ˜€Ÿô+>?ELJ:82\nþéÕËÄÄÆÝìòû\b-=IZnmH÷ª—€ƒÚ\v2?9DJH>0ùüé×ÊÄ½¯´¼¾Ñßô.9WijU¿—€Ÿñ4?>FKC964öòà³ —ˆ¯µ·Éä.CUbe\\2ß§€´6?:>FI>/ \füçÅ¦“ˆ€‡š§µÃØ#3FTR_\\6ê €É7A>>FLD/ ðÙ½¬¦–„€‡™®¾Ý):FLJ[\\6ð €Ð7?3=FNI>#âàÃ³¦ž—…‡–©Æá\r0:ABE\\c-â‘€×\n78/9FOP6!\fåàÊµ®¢——”—¤±Ðí86ABBUIÜ™€×\n7844>PXC0åÕÇ·µ¦¡ž¤ª¨ºë261:QP+Î€Âõ18.=PYMB(è×»¨­­¦«»½Êó\f/'1:BT7è­ˆ­í'84;JZZOM;ýáÖÔ¿±²ÄÓØ#-8CS>öÐžˆ€ŸÏõ'54DOZURM;ûïãÖÓÏÒÞ*,<<JJ9ùß·Ž€ˆÂë+3@P_ZVWSJ5øõø&7<BJG6 \t÷ß»™ˆ€€€¦Ëäþ3;EL_acc`QA@F98&52DTREF$÷ã½§Œ†€€€‰¸Òê7BLSgnpoohaaRTPFFO\\[E5\v÷¾¦’…€€€€ˆ”¾Ïá÷\b+J^bimvvpk^]^_Z^XW>-ôÎ«˜†€€€€€ƒ°Ìä÷9LXdopqp`ZYWZa^^aTCìØ½¤Š€€€€‚Š¥Ìñ\"7MgpmpdZURUZ_a^ZicZJ:\bæÐ¹šƒ€€€‰Ÿ¾Ó÷1?PakxrZBLA;;HLKKTahi_LC1Ö¸™‚€€ˆ™´Êñ\f<RZY]dkM7\b\n#,48CR[eia\\E1åº‹€€Š³Ôú8D_bihc@úòøøøò\f+:FOXZX`YO=ê¢€§Êÿ$?IUYYZI0\fýéÞââÞßñ6CJMRRZTK@Ð‚ˆÂ\n.?HYZ]H0óâÕÔÇÈËÏÒÔë\"/HEKQSSKK<¡žó+7QZRS@3ùãÕÀ´¹°¶ÀÇÈÉÖò(5CDKPMKKH+¯¼&4S\\XUM6ýçÕ¼¡ª±­µ±´¼ÆÎãü.;BCJJNPK8\aÓ4PWSY\\G'îÊ»ª¢¥¡­­©°¼ÉÝê/<BJDFPKC<%PWRSVS6!ý×À³™–Ÿœž¥­ª³ÇÎÛó#5<D@FPKEC<XRWXZM'ïÕÀ³™‘›œžž¢«½ÉËÖñú+3CDFKKECRXRYieN!\aëÏÀ³™Ž‰”žž©¼ÌÈÎéò#1CDFKKECZYSdk]DíÏÀ³›”Ž†ˆ—ž¦¨½ÌÕÝîð#':@FKKE<ZZane]AýïàÎ¸ª–Ž†‡—ž¡¦ºÅÓóñ\b#'?CCFFA'-YgnbU@÷íÏÃ·¦”†—›¥¨³Ëßçñþ &(=EHFF8Ïñ]onbRA$÷ïæÙÄ²¨¤œžž©«½Õãâý &;>BHBC$™­SqZ^Y?0øìâÜÛÒÈ½¼¼¿ÂØÝãôý%'/:=DGG6çˆžf`YWK?.þ÷ôøøõÝËËÈÒÜä÷øøû-<=;ECDC—€žÖ@`_WRF:1\a\a\b÷ìèñôéðøù\t7?H8@A?,Ø€—¥æ?X[ZaXG9-\nÿûññ÷7CCAB@,Ù‹€€ˆ²Ü8adfaXNQE@/\nÿøú\t#*9?EGC5!ÓŠ€€€€Žœ°Ò'[jpm_YVRD?3 \"*-.9:JIA6Ã‰€€€€ˆˆ•¥¶÷CjrppbRPK;4/-,-6?;HKND=½Œƒ€€€€€ˆ‡”¥²ÄØ `opux\\RPA<?EIPOOC;®ˆ€€€€€€€€€€€‚Œ›ž›£²¹Ñ\"QWaa\\QNPH4\vÈ—Œ€€€€€€€€€€€";
int iE09 = 24;
int iE19 = 35;
const int N9=120;


const char Arr09[]=
"€€…‰‰‰‰•ñFW_ffQè°œš•‰ƒ€€€‡‰‰’ŸìKWTDNUcmo]øÀ¢š–†€‰‰‰–ª)UHF4;<DLZgwjÄ¬š•‰‰‰—´$SRA$!\".<NY]taË¬ž“‰‘¨PI.\t\b\f\"5OVhgË§“‰ ìHS9!ôàÛÕÝÿ\v0Q_qMç´›‘¶0UC!ôÔ¸¤¢§Ïí9chgÅ‘áMU<)ôÕÄ Œ•§´ËñAejMèŸ¢2UK9!ûßÄ­“‰ž³¹Ò\a9Wqd°¢GUA.!îÐ³«“‰—¯¯Äè5Vqk+ÇïTUB.ê¿«¦‰–¢¦ÁæKqsTå*URH.Û»«¦‰‰Œ¥¯ÄáPqx^îLUWL.öÓ¶«¦€Œ¥«¾ÜSowhLV`Q4ïÍ¶«¦‰€€««¾ÚIcwo*U]cQ4ÞÍ¶«¤‹€„««¾ØB\\wqQUfiX4ÞÍ¶«¤„‰«­ÄØ2\\wtYUfi\\0ÞÍ¶¥¢™‘‘—¬³ÄØý+\\wtYUos`5àÊ±¢©™‘‘˜³³ÄÜý,awwZLws`;ñÈ¶««™‘šŸ³³ÄÔõ+hwrQ3wwiC\bÑ´««˜‘³³¾Ñõ5twjP\bmwmS$Ù¶¥¨–‘•Ÿ°®ÄâDtsaOæUqwW<ýÕ¶«•‘•›¢¶Çí&Tws\\M³,iwa1\nìÒ°žœ¢¢³Àà.kunS6«\fYmnQ0\rïÜ»®³»Ùô%AeqZL(«Ö(WfjJ0þâáæó\f*9[^jZI‰ºù/SfhE5(\f,0?NT]MF\v€œÅ2KaNA/\"-//*NLRK9ñ€“£¾÷\"/532ù\r 7IIB)î‰‹¬Ãè$\"ÿæïìÿ0IIBë‘‹’šªºÊä\bûíæÛÜÞú(<A0Ú‘Š‹“š£«³ÁËÈÂ«¶ÃÓC<1Ñ‰‹‘•œ©°³­šž¯Åæÿ<8ëÁ‰‹‘‘‘•Ÿ¢¤’‘§Íê(6-\tå§‰‹‰‰‘•Ÿ¢™Œš®Ûòÿ8üâ§‰‹‰‰‰‘œ¢ž•”¦Àæðÿ7ðÇ¢š§«¦¡šš¤¢š˜œ·Æìë\b.øêÇ¢š§«¦¡šœ¢Ÿ¡žª·Ïìó#öÜ´šš°³¯©¢œ¢¥ª·µÄÜîú\n÷ìÉžšš°³³¯¢œ¦­·³¼Ñà÷\róôåÄžšš°¹ÂÀ³·µ¼ÈÀÇÑã\a\nýóíÊ¯žš‘®ÃÄÀ´ÀÇØØÓÌÝ\v\víêÜ¾¢ž’¢¹ÉÍÄÌÕáæéØç\b\béãÙÄ­š’¢ÁÒÔÔÓ×çôð\n\"üæÙÀ±¢’‰¢º¾Ûçà '*øåÕ¿³¬›š’‰¢¹Ãåýú30.6/óáÏ¹«¢›’‰‰š²Êð*CGI8õÖÆ¶² š’‰‰‰‘Àñ%?=0\f\bîÊ¹µ¨ž•‰‰…€€‚žÒíõú\bò×Íµ¤˜Ž‰‰‰‰ƒ€€";
const char Arr19[]=
"€ƒ„„„„„„„„„›í.INV_aaOË¯žš•‘‘‰…††€„„„„„„„‡™ó2IRUYVQQT[gtoe!Õµ§˜’’‹ˆ‡„„„„„…’ð/HUTOL@1-01ASor}o]Ûµ¢œ˜“‹‡„„„„ˆª=ILTRI0 +Cairje@æ»¢™–‡„„„ŠÈ#@FING@!\f\b\b;P[cd^PøÅ§–’Ž„„‰½#@GIOG@)äÞåãáçø\a*K]encMòÅ¥”Ž„„¤BHJFG7þìÝÊÌÊÊËÏØäè\v1I_iph:Ú·˜Ž„”<LOIP9)àÓÐÅ½¹¹º¾ÆÊÓæ\r@Xiplh)Ù¥„»/LONQT6éÓÌÍ¹´´·¼»¹ÃÆÔò\"H]imj[³“‹GRURTFøÚÑÐÃ´¡œœ¥ª¯¹ÆÍßþ/Tgmpo4Ñ—’0O]TUX3äÒÏÆµ¤™•’•™¢¶¹ÂÑëQelroOê”Ü@SYVZP!ùæÕÎÂ®›’Ž–˜©µ¼Æà?gmnth¦#HV^Z`I\bòéÐÆµ§‘ŽŽ‘‹•¤®¸ÂØö.^eitmDÌ8S[X]`I\tðâÑÁ°¢Š‡‡‡‹”ž«³¼×ò VfmvpPäCT[X]dL\tõáÐ¿¬‹„†‰‰‹‘ž±²¼ÓñMhnxue\fFW\\X^gO\föáË¼ª—ˆ„ˆ‹‰‹Ž™§±¼Òí\tOhmtte/JW\\[`hPùâÍ½ª˜Ž‹ŽŽ‹Œ’™©»ÅÚôObntrkRJW\\`afVöãÍ¾«˜Œ‹Ž“³¿ËÜõ\vObnpniYCV`c`cW-üäÊÃ¸ž“‹‡‰ŽŽ—£ºÇÊßúTbnpnjf1U`c`hhGáÌÊ½¬™ŽŠ‰……Ž£½ÎØò)[cjmnifÎ=Z^]fiX%òÎÊÇ¸¡’ŽŒŽ“·ÎÙèþ2ZfjlkdU«4S]ZbgjA\väÒÍÆ²£œ™’–¤Ã×æù\f#H^cejkaG•@RT[ecR4ØÕÊ¿®««®®»Ðáñþ9O]`eie`9‹½&JNP\\fbT+öÙÒÊÉÊÎÇÄÍÛë4KR^_cid[/‡¡ø3LJW`c_S:\vðØÙ××ÏÐâý\t#7DEE\\_bcfK€Œµ;MJPX][K9-ùîì÷\a!$/AE2;U[\\`]9€„œ¾2ELOQUUF7.&14B:2/R\\[bV0î€ƒˆŸ½ó\";BJQVUTH;1#!!/:0&\n0PY]bL\"Ò€€ƒˆš´Þ!39ADE=85421\"÷êò)J[^]<Ë€€ƒ…Š–©ÃÞë&($&#!æëÕÔàò4KY]Q(ø°€€€ƒ„†œ¦¼ÉÜãäáàâØÚÏÃÄÆÑäý.QXY=ß–€€€ƒ„„Š‹”£§©¨«ª¬²±³¹¾ÇÓç&?VXQ)ÿÉ…€€€€†‰‹‹Ž’ŽŽŽŒ’–¥ª´¶»ÊÞõ$GYY?ïÈ…„„„‡‰Ž‹‹‹ŽŽ••š§®µ¹ÄØçÿ+MPI$Ú¶…„„„ˆ‹‹‹Ž’’“”—¨®²±·Éàì6PR>ìÉš„„„•žœž™™”“–‘—ª³³²¼Ôäÿ\f&@JIÿáÄ‘„„‘¡®³³®­¢˜—œžŸ©³³±¸Êáð4HA)çË³‰‡„›®·»¼½¹­¬¥£§§ª°µµºÆÛõ\n&9C0÷ÚÄ•ˆ‡„”·¿ÂÁÁ½¶¯°ª¬±»ºº¾ÄØôÿ\b-6+öÞÉ´Ž‡‡„ŽµÄÅÊËÀ¾¶¹¹µ¼ÉÉÍÓÝõ\f\"4/ùäÒ¼”ˆ‡‡„ˆ¯ÆÇËÈÅÂÅÈÊËÈÍÓÐßõÿ\v1+øãÓÄ¤‡‡‡‡Ž¦½ÈÏÌÍÛÚÞÚÖÛÛÝñ  þæÏÅ­‡‡‡‡‹—ŸºÙåæàããäáäîô!\"#%ÿäÖÍ²‡‡‡‡‡‹˜œ°Éìùùù)/3/'\tõâÕË«ˆ‡‡‡‡‡’”ž¬½ß\v\t+::=:1 \f\tìÛÌÂ¨Ž‡‡‡‡‡‡‡Ž˜¦µÄß$81<>?C8!\r\nþóéÚÊ¸¡Š‡‡‡‡‡‡‡‡•œ¨»Óêû9MH@4\"ûõìæÛÊ¼¤Ž‹‡‡‡‡†„„„„’›¤ª³ÇáòðæîñàÞÒÉ·¬‹‚‡‡„„„„„„„ƒ€";

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
	return ((iNumPx < 10) || (bHasGrey && (iMaxNeigh < 8)))	;	
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

	 
	 if (max(iHeight1,iHeight2)-iHeightRama>2 || max(iWidth1,iWidth2)-iWidthRama>3)
		 return 0.;

	 float f;
	 f=cmp_2_Pict_with_Rama(DigitPattern,iHeight1,iWidth1,Digit2,iHeight2,iWidth2,iHeightRama,iWidthRama);
	 
	 if (fMax<f)
	 {
		 fMax=f;
	 }
	 
	 return fMax;
 }
//----------------------------------------------------------------
int Get_Final_Number(int iter)
{
   float f,fMax=0;
   int iBestDigit;

   for(int iDigit=0;iDigit<=9;iDigit++)
   {
	   
	   for(int iCombNo=0;iCombNo<=1;iCombNo++)
	   {
		   int iWidth;
		   const char *sArr;
		   switch(iDigit)
		   {
		   case(0):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE00;
					   sArr=Arr00;

				   }
				   else
				   {
					   iWidth=iE10;
					   sArr=Arr10;
				   }	
			   break;
			   }
		   case(1):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE01;
					   sArr=Arr01;
				   }
				   else
				   {
					   iWidth=iE11;
					   sArr=Arr11;
				   }		   
			   break;
			   }
		   case(2):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE02;
					   sArr=Arr02;
				   }
				   else
				   {
					   iWidth=iE12;
					   sArr=Arr12;
				   }		   
			   break;
			   }
		   case(3):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE03;
					   sArr=Arr03;
				   }
				   else
				   {
					   iWidth=iE13;
					   sArr=Arr13;
				   }		   
			   break;
			   }
		   case(4):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE04;
					   sArr=Arr04;
				   }
				   else
				   {
					   iWidth=iE14;
					   sArr=Arr14;
				   }		   
			   break;
			   }
		   case(5):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE05;
					   sArr=Arr05;
				   }
				   else
				   {
					   iWidth=iE15;
					   sArr=Arr15;
				   }		   
			   break;
			   }
		   case(6):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE06;
					   sArr=Arr06;
				   }
				   else
				   {
					   iWidth=iE16;
					   sArr=Arr16;
				   }		   
			   break;
			   }
		   case(7):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE07;
					   sArr=Arr07;
				   }
				   else
				   {
					   iWidth=iE17;
					   sArr=Arr17;
				   }		   
			   break;
			   }
		   case(8):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE08;
					   sArr=Arr08;
				   }
				   else
				   {
					   iWidth=iE18;
					   sArr=Arr18;
				   }		   
			   break;
			   }
		   case(9):
			   {
				   if (iCombNo==0)
				   {
					   iWidth=iE09;
					   sArr=Arr09;
				   }
				   else
				   {
					   iWidth=iE19;
					   sArr=Arr19;
				   }		   
			   break;
			   }

		   };
		  					  
		   Resize_Digit(iter,iWidth);
		   f=cmp_2_Pict(sArr,48,iWidth,DigitResized[iter],48,iWidth);
		   //printf("DIGIT=%d iCombNo=%d f=%f\n",iDigit,iCombNo,f); 

		   if (fMax<f)
		   {
			   fMax=f;
			   iBestDigit=iDigit;
		   }
	   }
	   //printf("\n");
   }
   return iBestDigit;
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