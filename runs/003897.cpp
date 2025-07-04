#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<set>

using namespace std;

const int N=14; //resolution of pattern of each number
const int NumberOfFonts=40;

const char F_compressed[][10*N*N/3+1 +(10*N*N)%3]={"P A@@}}C@xAtB@M@!@pC@O@|@PC@O@t@pC@M@|@PC@O@|@PC@G@xAtB@twO@@t_@@@pB@@@o@@@~K@@twB@@Gn@@@`K@@@xB@@@n@@@`K@@@xB@@@n@@@`K@@@xB@@@n@@@x B@P_}A@!@|@`K@n@@@`K@@@|@@@PG@@@]@@@tA@@PG@@@_@@@|B@@`_UE@|  K@P A@@_}A@tBt@@M@n@@@PK@@@]@@@}K@@@zK@@@pC@@@t@pC@M@tBxC@|UO@@t_@@@@t@@@`O@@@|C@@p @@@MO@@xrC@@G|@@t@O@`KpC@t  O@VU_B@@pC@@@|@@@@O@@~ G@PWUB@|@@@@G@@@pbB@@~ K@PoXK@`@pC@@@t@@@@M@|@PC@m@^@@_uC@@}G@@` C@@}uC@pCxA@m@h@pC@@@|tG@@ WO@pG`G@|@PC@O@t@PC@M@xApA@tWO@@x_@@|  C@UU}@@@PC@@@^@@@pC@@@m@@@pC@@@m@@@pC@@@!@@@`K@@@t@@@@M@@@pC@@@t_@@P_}@@^@^@PK@G@xAxB@tWG@@~ B@xAtB@O@|@pC@M@|@PC@m@|@@ uC@@}G@@P A@@ uA@tAxB@O@|@pC@M@|@pC@m@~@@ }O@@}QC@@@|@`A@G@tBtB@|uG@@to@@@",
	"` A@@}uC@pCxB@^@|@PC@M@|@`C@O@x@pC@N@|@`C@M@t@`G@O@pCtB@tWO@@x_@@@x@@@`O@@@}C@@|}@@@AO@@@pC@@@|@@@@O@@@pC@@@|@@@@O@@@pC@@@|@@@@O@@@t_B@P_}B@^@|@`C@M@`@PC@@@|@@@pK@@@o@@@|A@@xK@@`o@@@|B@@P_UE@|  C@P A@@}uC@pAtB@n@!@@@`G@@@~@@@|K@@@uK@@@pC@H@tBPC@m@xApC@tWo@@t_@@@@|@@@PO@@@~C@@p @@@MO@@xrC@@G|@@t@O@`KpC@|  G@}  A@@pC@@@|@@@@O@@~ G@`WUB@t@@@@O@@@pYE@@~ O@`GPO@@@PC@@@xA@B@n@t@PC@^@^@@}uC@@}G@@` K@@~uK@pKxC@^@T@PC@@@|vo@@ [o@pG@O@|@PC@O@xBPK@M@pCpC@tWo@@x_B@t  K@VU}@@@PK@@@^@@@pC@@@^@@@pC@@@^@@@PC@@@|@@@`G@@@xB@@@M@@@PC@@@x_@@P_}@@|@]@`G@G@pApA@|BO@@| B@P_}B@]@|@pC@m@|@PK@]@|@@ uK@@}o@@P A@@}uC@xAxA@M@|@pC@M@t@pK@^@|B@ vo@@}WC@@@t@`K@O@xAtB@|wO@@t_@@@",
	"@}G@@^Zg@pK`g@^BpKPk@tJ|B@]Bo@PgpK@tI|B@]BmBpG@g@|APK`g@Pg}A@P I@@t@@@Zo@@`yK@@`~B@@@o@@@pK@@@|B@@@o@@@pK@@@|B@@@o@@@pK@@@~A@@PUA@@t_B@pkuA@m@~BpK@]@t[pK@tG|B@hrK@@`oB@@]B@@!J@@pI@H@]@PIp  _BPUUe@P G@@mVg@pIpK@|BtA@~bo@@p A@@he@@@`m@@@`o@nBpKPg@~BpIPg@ti}A@x I@@pK@@@|B@@Pg@@@|RB@@g]@@trG@@g|A@TB_@`KpG@t  _@hjoM@@pG@@@~I@@`UI@@@A@p  B@!Ue@@kj@@pB@@@!uA@@gzK@@@xA@@@|B@I@o@|BxI@]@_@@]}I@@Vi@@@}G@@!Yo@pKPi@^B`@Pk]B@|nuA@_IvBpg@^@|J@g@m@xI`K@]@PCpK@pg_@@P A@P  G@TUuI@jjn@dB@I@F@l@@@PI@@@n@@@pK@@@]B@@pK@@@~B@@Po@@@tK@@@VA@@@L@@@`B@@`Y@@@euB@pAX@@|@J@@~eB@@uO@@lbo@PI@G@T@pA@n@l@@^zI@@Ti@@P]@@@gvB@tBT@@o@n@pKPK@tB~B@|U]@@TYK@@H|B@@`G@@@!B@@PI@@Xg@@@fB@@@",
	"` g@@} o@x }O@}C~Kp @ A|Gp_@ A|Op_@ C|Gp_@ C|GP ` Bp }O@t  B@x I@@P @@@~O@@x C@x  @@  O@po C@dp @@@|O@@@ C@@p @@@|O@@@ C@@p @@@|O@@x g@P  o@|_ OP B}KhFP B@@|O@@p A@` G@@}_@@t B@` C@@|  oP   K|   BP o@@  _@t_}O@uC}C@@p @@P K@@| @@@u B@@p_@@@|OP @ At }o@|  A@t K@@@tO@@` C@@~ @@p O@@ }C@tG @P pO@~C|Cp U E|   C    `jZ J@@pO@@@|C@}  AP  _@|  G@ B@@poj@@~  AP   Bxot @@@tO@@@}C|Op @}_ K@  _@@} B@@}o@@~ _@p }O@}K|IP @@@|_ C@   Cp [ A|Op @ CtOP @ Cp }o@x  A@P G@|   B   op   C@@to@@@ A@@tO@@` B@@|O@@` B@@tO@@@ C@@p_@@@~G@@P B@@t K@P  G@~_ CP @ BtOxO@|  A@~ O@x  O@ C~Gp_@ C|Op_@}_ K@  _@@} A@` g@@} _@x }O@}C|GP @ CtOp @~g}O@   C@}W @@@|O@}B Ap }O@x  B@x I@@",
	"Po@@@]M@@pBG@@M`C@PAp@@T@L@@G@C@pAp@@T@L@@E@C@PCx@@pBG@@tu@@@tK@@@l@@@PK@@@}B@@tm@@@AK@@@pB@@@l@@@@K@@@pB@@@l@@@@K@@@pB@@@l@@@@K@@@tG@@pWG@@N`C@PCpB@@@l@@@`C@@@!@@@PC@@@m@@@tB@@`G@@@!@@@PWU@@| o@@po@@@_M@@x@G@@HPC@@@!@@@tC@@@ @@@@|@@@@L@@@@C@PBp@@t@M@@|uB@@|K@@@@K@@@tB@@@o@@@TK@@@sB@@ll@@`CK@@lpB@`Al@@|  @@UuE@@@l@@@@K@@@pB@@} B@PWE@@!@@@@K@@@pj@@@| B@`g~@@`@!@@@@M@@@PC@T@!@@M`K@@_]@@@}A@@P_@@@]]@@pBM@@M@B@PA@@@!}C@@ zA@pCx@@|@l@@E@K@PCp@@xBM@@tuB@@tG@@| _@@UuK@@@!@@@PC@@@!@@@`C@@@!@@@@K@@@t@@@@O@@@pA@@@l@@@`C@@@x@@@@tK@@pWK@@lPC@`Ct@@pBM@@tuB@@~O@@xAO@@M@C@pApB@T@l@@MPC@@_]@@@}A@@po@@@_m@@t@M@@M`C@pAp@@T@l@@MPK@@g~B@` n@@@@C@@Bx@@x@G@@|}@@@~K@@@",
	"@}K@@!@G@pC`K@^@pCPK@|@t@@M@O@PKpC@tBt@@M@m@pC`G@|@pA`K@pA^@@P B@@n@@@}K@@@tB@@@m@@@PK@@@tB@@@m@@@PK@@@tB@@@m@@@PK@@@tB@@@m@@@} B@@X}A@`AxC@L@xBPA@!@d@@G@@@xA@@@O@@@tB@@PK@@@M@@@T@H@PB`A`  _@TUUK@@}G@@^PG@p@pK@H@tB@@@M@@@xB@@~G@@@`O@@@`G@@@pCPA@|@t@`G@|@~@@t A@@@tB@@Po@@@UK@@xxB@`Cn@@l`K@pBxB@G@n@p   ATUue@@@n@@@`K@@@xB@@@n@@VUM@P  C@d@@@@I@@@P@@@@| I@@IxG@@@PK@@@pA@@@|@T@@G@m@xB@O`G@@}o@@@X_@@xA@@`K@@@!@@@`Kj@@tVuB@ @tBpK@|@|@@O@O@pCPK@|@pA`G@tB~@@x A@pUUe@|  K`A@X@d@@C@B@l@@@PC@@@l@@@pC@@@n@@@PC@@@|@@@`G@@@tB@@@O@@@P A@`KpC@!@pB@G@l@pKPC@poM@@p A@@g}C@!@tCPC@t@t@@N@N@PC@M@M@@~_@@` K@@m`G@xB`K@O@pApC@|@|@@O@M@xC@O@ @`_mO@@jpA@@@M@@@xB@@PK@@~G@@@",
	"` A@@nPA@pApB@n@|@PC@M@|@PC@O@t@pC@M@|@PC@M@t@`K@O@pApB@xBE@@x_@@@t@@@}O@@@pC@@@t@@@@M@@@PC@@@t@@@@M@@@PC@@@t@@@@M@@@PC@@@|@@@~ G@@X B@PBtB@D@|@PG@O@xCpC@X@^@@@pC@@@M@@@T@@@PA@@@J@A@X@p@@  O@|  C@P A@@CpA@xBt@@^@M@@@PC@@@l@@` B@@@pA@@@xB@F@!@pK@O@T@xA@F@O@@v_@@@@T@@@@G@@@|A@@P]@@@fG@@pxA@@I^@@X`G@@CxA@Tj]J@jZgB@@xA@@@^@@@| @@UbA@P _@@t A@@A@@@P@@@@T}B@@CxA@h@tB@@@^@`A`G@|BxA@E@m@`AxA@` K@@@}K@@!`K@PCtA@n@N@PC@@@|@@@@OuK@pG`K@|BpC@O@|@PC@O@xBpA@t@M@@x_@@t  A@} O@PB@B@L@H@@A@A@@@d@@@@C@@@x@@@@G@@@xA@@@m@@@pC@@@|@@@@M@@@x_@@PAt@@L@l@`C@K@xAp@@|GA@@t @@@U B@N@~@pA@N@l@@C@G@X@`K`C@@}G@@P B@@MpB@tBx@@O@!@pC@O@|@pC@m@}@@odO@@VpC@@@!@@A`C@tAT@@nPC@@}G@@@",
	"@v I@tKtGPO@xG~A@t[O@@~}C@@  @@p O@@| C@@  B@xg_@@}Po@xKP_`o@`}_B`vC@@} @@@xO@@@|C@@@ @@@pO@@@|C@@@ @@@pO@@@|C@@@ @@@pO@@@|C@@} o@@P g@P  o@d@~O@@@|K@@@ @@@pO@@@|B@@pK@@@m@@@|@P@xA@NPgjzc    t   OX A@`I~A@@@|@@@@O@@@xB@@PI@@`uA@@@pC@@@xA@@@^@@@PG@@@}@@@vA@P_B@@@@t@@@`O@@@|C@@p|@@@KO@@TpC@PA|@@N@O@p   Bt  o@@@O@@@pC@@@|@@@@O@@  C@pUU@@L@@@`A@@@x A@@hvC@@@tC@@@|@@@@M@@@pC@@@~@@@pC@@PO@@tg@@@@@]@@@]@@@^@@@xA@@@O@@@xYE@@ ao@pG@O@|@PG@O@xAPK@^@xAPC@tA^@@x B@|  K@WU}@P@@I@H@p@@@@E@@@p@@@@M@@@pB@@@M@@@pA@@@M@@@pC@@@m@@@pC@@@X A@`KtA@!@|@@G@O@pKpB@xgK@@p @@@e B@!@~BPC@]@t@@G@m@xB@O@G@@}o@@P A@@OPK@tBpC@O@tBpC@]@|BPG@]@|A@]Po@@VqC@@@^@@@pC@@@O@@@]@@@U@@@@",
	"@Ve@@t@!@`C@l@|@@M`G@PKtB@tAo@@}pK@POtB@tA^@@m@O@PCPC@l@PCpB@`WI@@f@@@uK@@@tB@@@n@@@`K@@@xB@@@n@@@`K@@@xB@@@n@@@`K@@@xB@@@]@@@v_@@@@ZG@@J`G@X@pC@C@|@T@@O@EhxA`kAM@`GtB@@`A@@@F@@@X@@@`B@I@} _@t  K@@T]@@X@^@@C@O@x@xA@^IE@@eV@@@htB@@@|@@@@M@@@pC`K@~@t@PK@l@m@@T]@@@@pB@@@o@@@tK@@PvB@@IM@@hPC@`Bt@BD@MXPUuWG@@t`A@@M`@@pK@@@|B@@X A@@@D@@hXB@@ K@@PJ@@@H@@@@hB@@TbC@@ApC@`@t@@@@M@X@pC@m@l@`KpA@`UA@@@XuA@pApA@O@|@tB@I@O@@@xQUB@}BtAPG@|@tB@]@M@`G`K@tBpA@O@pBxB@PUA@P@@@@~  @P  G@d@@@@@@H@@@@@@@@D@@@`B@@@d@@@@C@@@t@@@@O@@@pC@@@!@@@PUA@@A`C@L@pB@C@d@pA@A@tGF@@t B@@V A@T@~BPC@|@!@@O@E@pB@K@E@@Ue@@@UE@@l@N@pC@M@]@`KPK@pAtA@!@|@PG@]@~A@TIm@@@pC`A@!@|@PC@M@M@@]e@@@",
	"TB@@Ps@@@|l@@@OG@@psA@@|!@@@OG@@psA@@|!@@@OG@@psA@@|l@@@MC@@@U@@@`C@@@~@@@@O@@@pC@@@|@@@@O@@@pC@@@|@@@@O@@@pC@@@|@@@@O@@@pC@@@~B@@@z@@@H!@@@BO@@`qC@@x|@@@@O@@@pA@@@N@@@p@@@@A@@@``@@@BH@@PUA@@t @@@XA@@@pA@@X|@@@nO@@@qA@@@L@@@XB@@@pB@@@|@@@NO@@P{C@@T|@@@@G@@@V@@@@L@@@PC@@@|@@@@O@@@xC@@@~@@@`O@@@rC@@`|@@@DO@@@pC@@@|@@@@O@@@xC@@`U@@@tO@@@B@@@@@@@@@A@@@bC@@`x@@@Hn@@@`K@@@xB@@|n@@@gK@@`x@@@`I@@@dB@@P{@@@|m@@@oA@@pC@@@|@@@@oC@@psA@@|!@@@OG@@psA@@|!@@@MC@@@e@@@|_@@@UI@@`@@@@@@@@@@B@@@`@@@@A@@@p@@@@E@@@pA@@@^@@@PG@@@tA@@@n@@@@i@@@TH@@@MH@@Pc@@@xJ@@@|@@@@M@@@PG@@@pC@@PtB@@D^@@@AG@@PpB@@PE@@@TB@@Ps@@@|l@@@OG@@psA@@|!@@@OG@@P{A@@`^@@@@G@@`yA@@tn@@@mC@@@f@@@@",
	"@~_@@tOx@P CP@| @hP O@D| C@A  @Pp O@D| C@A} @P@ O@JP CP@P `C@` G@@@v@@X O@p} C@@  @@p O@@| C@@  @@p O@@| C@@  @@p O@@| C@@  @@p O@@`}_@@E` @D@p `B@}OD@p CI@  @Ax G@@  @@| K@P _@@~ C@p o@@  A@t   C@u B@Np A`@| @@@ o@@p C@@|o@@|_@@@p B@@| A@@  @@p OD@| An@ G@t}g@@@@P@@@@G@@@|A@@p_@@@ G@@| A@P _@@y G@D| AP@ _@ez gPU} g@@ _@@p G@p  B@J@@@P@@@@|}G@@@|o@@@ o@Bp Gd@| CC@  P@p OL@| AI@ O@Ep @@v A@@t B@xOPA` C`@| @@` O@@t []@  @Xp O@D| C@A} @P@ O@DP CPBP `I@` G@t   G@@| B@` O@@| A@` o@@| C@` _@@t K@`  @@| G@`  B@| O@`  A@t o@@P g@@O@d@|C@L` G@Cx _d@|  C@   C@   AT   `B} OD@t AI@pO@E@tB@v_A@@}o@@np_@P@|_@A@ oP@p GD@| CA@  `Ap O`W~ C@@ _@@p C@@|o@X@ B@X A@@",
	"@X_@@P  @@h} @@@|o@T@~GPK@}C~@`_pO@pK|G@|@ C`CP C!@p  A@x G@@Pg@@@t@@@xo@@P K@@` B@@po@@@|K@@@ B@@po@@@|K@@@ B@@po@@@|K@@@o@@@P@@@@P_@@`  @@V _@@@~G@@@}A@@`o@@@tC@@@O@@@t@@@`C@@@^eJ@x  B`  G@TU]@@Po@@@ o@@h}G@@@}@@@PK@@@~B@@| A@@x @@@pO@@@|C@@@_@@@xA@@PK@@@E@@@@@F@@@p@@@@C@@@lPB@PCo@@nxK@pC~B@}Y Ep   @t  K@@`o@@@xK@@@]@@@`B@@PWE@@~ B@p G@@EH@@po@@@}_@@@}_@@@|O@@@~C@@@_@@@pC@@@M@@@T@@@PB@@@@@C@@@n@@@x@@@`K@@@!@@@pC~A@~t APOx @|KxO@ A|CP @o@x yA@t K@@xG@@@K@@@|  @p  G@x  @@@`K@@@|@@@`C@@@|@@@`K@@@|@@@`G@@@|A@@PG@@@D@@@@@`O@@N}G@tB B`_`O@t_t@@| C@@~ G@@! G@xA A`O@o@|KpA@ kG@P o@@Po@@@@tK@@x G@PC C@]@ ApOP @|KpO@}G|C` ko@`GtA@@@O@@@|@@@pA@@`K@@@D@@@@",
	"PG@@@}A@@pGD@@~@F@`K@A@t@`A@E@X@PA@N@X@`A@L@h@@C@B@PAP@@pBI@@Po@@@|@@@pO@@@}C@@x}@@@EO@@PPA@@@T@@@@F@@@`A@@@h@@@@B@@@`@@@@H@@@@H@@@`}C@@} C@poxB@@@l@@@PC@@@F@@@X@@@`A@@@L@@@PB@@@F@@@P@@@@eB@@PWeB@v  @P II@@@D@@@P@@@@A@@@X@@@` A@@@vA@@@p@@@@d@@@@K@@@p@@@@I@@PE@@@n@@@PK@@@!@@@PC@@@!N@@@cC@@Tte@@_]B@`@C@@@p@@@@L@@@@A@@@P@@@@D@@`oBH@t  A@]jB@`K@@@t@@@@N@@@@ A@@@`K@@@@A@@@P@@@@L@@@pB@@`K@@pg@@@@n@@@PC@@@N@@@pB@@@M@@@pB@@@L@@@`AB@@T~K@@uuC@PI|@@|@O@@^vB@@}K@@|UUA@}  @@@@A@@@D@@@`A@@@D@@@@A@@@h@@@@A@@@P@@@@J@@@P@@@@H@@@@B@@@@^@@@xyA@@OpB@xBT@@l@F@@O`B@t_E@POzC@tAPA@]@t@PG@E@xCUB@|CE@@t_@@` B@@|wB@`Kt@@xxO@@|_C@@~z@@@@E@@@p@@@@E@@@p@@@@I@@@X@@@@A@@@@@@@@",
	"@v_B@t  AP   A~_} R K} | ` O op { K| ~ A o} p C _}_`   CP  O@`}o@@`}_@X  O@  _@x  K@@} B@` O@@x C@@~ B@P o@@t K@@  AP   O|   Kt  _@@}_@@}  B|   P   OtK  CHP _@@| C@P O@@} @Bx G~P   O}   SUUuo@@@PBP _@P   @tu o@@t C@@}o@@x K@p  o@|  O@@~ C@@} @@p OtU  @   C@} I@@@PO@@@}K@@t B@` o@@~ K@pq B@O|o@tB K`Op It   A}  _`Uu C@@|o@@@ K@t  K@   Bx  O@   Ap_@@@~ G@P   @t   @X} _@@~ G@@  B]} GP  _@P _@@@~A@@x B@@ G@@t @@@ GJ@t  _@   _p w O| p C Ot P K~Gp w @p  K@P G@xWUU@   Op   A|  o@]@|C@@@ @@@tK@@@ @@@tG@@@ B@@tO@@` C@@|_@@@~C@@P _B`   A| x a Ox_x o}K|  o@~  KP   K~w  q `  to@ G|ot B~  K@T g@@}_@@}  Ax   B}O| p C}Ot b C~ ~_@   K@}  @@` K@@t @@` C@@~O@@@}@@@",
	"@X g@P   @    | i}o G@ w @`  O@p  C@~w @P ~_@|O  u C   _@   B@XUB@@D@@@~K@@~ @@| O@@} C@@q @@@|O@@@ C@@p @@@|O@@@ C@@p @@@|O@@@ C@@~I@@P _@@| _@@X _@@@ O@@` C@@x @@@}G@@x @@@ C@@|oj@p  G`   AXUU_@~g@@P  B@t  B@@}_@@@ K@@t_@@| A@@} C@@p C@@t @@X O@|  @@  A@p_B@@@@@_@@@tO@@P C@@~ @@x O@@  C@|{ @P_|O@}C Cx   O}   CUU _@@p @@@|O@u o@P  K@|  B@ jJ@p_B@@| G@`  O@`v K@@x B@@}O@`} A@  G@P G@@xI@@@@`A@@@}B@@t @@P K@@~O@@p g@@~  @P } @|Ot_@ C|Op ` At }O@|  A@t A@|  E@   Cp  _@hj}K@@p @@@~K@@p @@@~G@@p B@@~O@@p A@@~O@@@}A@@@D@@@X o@P  _@}G~Op @}KtOp @~o}G@~ _@P  _@~G|op @~G|OP A G~O@   A@} A@@}o@@} _@x }O@ C~Gp ` A|ox_@}_}K@}  @@v G@@x @@` K@@|o@@@}A@@@K@@@",
	"@}A@@|wC@p pC@|J~BPO@!@|GBM@_xqCpodt@|A@M@}@vA@_@m@pGYC@pWO@@P_@@@v@@@}O@@P}C@@` @@@pL@@@lC@@@W@@@PG@@@|A@@@]@@@PG@@@tA@@@m@@@`K@@@To@@p@]@@E`O@PSTA@pOw@@@tF@@`{@@@~A@@pG@@@]@@@pA`B@^}_@P  O@XU}C@|_e@@  O@PItB@@`K@@@^@@@pg@@@xG@@@pO@@@xA@H@^@PCPG@Pg @@T K@@PB@@@l@@@@K@@@tl@@@OK@@pCH@@^XA@PkU@@t}_B@  o@t g@@@pI@@@!B@@@C@@@p@@@ _B@@ouA@xCX@@~@@@@G@@@pUA@@|}K@@DwC@@@|B`@Po@!@pK@EP}@@_~C@@}G@@@PB@@` @@@~O@@po@@@}@@@pC@@@mTA@psuC@!FtA@gY|@PqKO@x@xA@T`O@@t_@@xWJ@@}  @p_iO@@@xA@@@O@@MxC@`C]@@@pK@@@u@@@pM@@@UA@@pm@@@~C@@@v@@@tm@@PG!@@|BO@@opC@pC~@@xwK@@^|A@xHvA@m@}@pA`o@|A~C@}U @@  C@@}G@@`Ya@@t M@tG~C@!@|@@G@O@tApC@xB}@@u_O@@ppK@@@~B@@@o@@@PK@@@|A@@PE@@",
	"@~_@@!B~BPBPr@F@DXPB`ADL@D@JC@A`q@h@XL@A@JCP@P`AB@LpQ@PBpG`K@` g@@~@@@|M@@@EC@@`q@@@XL@@@FC@@`q@@@XL@@@FC@@`q@@@XL@@@FC@@XyB@@  A@@x_@@Pi}B@E@s@P@pd@H@LI@@@S@@@PF@@@y@@@PA@@@G@@@d@@@P@PB@ijF@|  C@P K@@ETG@X@LC@B@SB`@pD@@@^A@@tK@@@!C@@@FC@@@SB@@Pd@D@iC@nvm@@v_@@@@~B@@pj@@@OJ@@TcB@`Sh@@LDJ@pBaB@Eph@p O~@@@cA@@Ph@@@DJ@@`[A@@  C@p K@@EC@@pZ@@@LA@@`q@@@p_A@@@@C@@@@A@@@P@@@@D@@@@C@A@T@PkzC@` G@@@x B@p_J@@W@@@lJ@@`S@@@dl_B@cGPBpX@P@LF@d@CA@IPR@P@pT@L@xVvB@P K@x  O@A`QB@@dL@@@cC@@Xd@@@CC@@pX@@@JI@@pp@@@LF@@PrB@@LL@@`[A@@to@@@P I@`[jE@LD@C`AAP@PPAD@T`W@@T@E@`uBN@FPAJp@PAAL@pP@K@LD`gP{@@} A@` K@@]mE@X@DE@C@FCp@@SBL@ph@I@LF@KPcB@]yD@@@FC@@Pl@@@VA@hvG@@ G@@@",
	"@T@@@p_@@@_O@@xpC@@GtA@p@}@@MPO@PAtA@l@m@@CpC@p@n@@dpA@@mG@@@m@@@@`G@@@}@@@~G@@Pt@@@@C@@@x@@@@K@@@p@@@@N@@@PC@@@!@@@@G@@@tA@@@I@@@@@@@tA@@~_@@|qA@pIM@@HT@@@PA@@@I@@@L@@@pB@@@K@@@~o@Tt  `ooX  ]@@hB@tWG@p _@@H!B@@pA@@@ _@@tWO@@ApA@@@M@@@T@@@TB@@xA@@PK@@@}@@@pA@@@@@@L@@@pC@@@_@@@|K@@x~@@`CG@@NpBN~_^ps   G@@tB@@@G@@@pA@@@m@@@PB@@@|UC@p o@@|B@@@O@@@t B@@ _@@@PK@@@l@@@pB@@`K@@@N@@@t@@@PO@@@!@@@@@T@@@`G@@@t@@@@G@@@x@@@@E@@@pB@@@F@@@pbE@@^WK@PKx@@l@K@@ G@@`g@@@PWZG@}  B@jzG@@@l@@@PC@@@N@@@PB@@@N@@@PB@@@L@@@PC@@@|@@@@G@@@P@@@@@QUI@|  Cp_@M@|At@@}pA@@_I@@Po@@@xG@@`{C@@N|B@pBN@@MtB@P C@@PI@@@@|@@@p G@@[ @@TxG@`C}@@T]K@@_T@@@@C@@@d@@@@C@@@x@@@@E@@@PO@@@!@@@@",
	"P A@@MxA@pAt@@m@^@pC`G@|@pC@O@|@pC@O@|@pC@O@!@PK`K@xAt@@t`K@@to@@@pB@@Po@@`wK@@HtB@@@m@@@PK@@@tB@@@m@@@PK@@@tB@@@m@@@PK@@@tA@@~ O@@u_@@tB~@@E@O@@@PK@@@|@@@`G@@@|@@@PC@@@M@@@x@@@`K@@@!@d@PWUG@|  B@t A@PKxC@T@|@@@@M@@@pC@@@M@@`}@@@h}B@@@|@@@@]@@@`G@!@tB@o`G@`}_@@@@m@@@pK@@@}B@@xn@@@[K@@TtB@`Cm@@lPK@PCtZ@|  G@@PK@@@tB@@@m@@@xO@@@`A@p _@@ljB@@C@@@p@@@@L@@@@wG@@PYo@@@@O@@@pC@@@t@@I@O@PCxB@X K@@@PO@@Pg@@@m@@@tB@@@O@@@xB@@@] G@pgPG@|@pC@O@|@pC@O@tBpC@|@m@@t_B@t  C@]U]@PB@C@@@t@@@@K@@@t@@@@G@@@x@@@@G@@@x@@@@O@@@xB@@@O@@@pA@@@t A@pCxC@^@tBPK@m@xAPC@|B^@@t A@PKtA@^@|@PK@m@t@PK@]@t@@o`G@@}o@@P I@@OPK@xBpA@M@|@pC@M@tBPK@~@}@@}_O@@@pC@@@!@@@PC@@@^@@@vA@@tA@@@",
	"@}K@@| G@pKpK@^@tAPK@!@t@@O@M@pCPC@|@t@@O@m@pA`G@]@pKpC@x _@@x B@@|B@@xo@@P_K@@!tB@@@m@@@PK@@@tB@@@m@@@PK@@@tB@@@m@@@PK@@t _@@  O@@t_@@x _@@F`O@@@pK@@@|B@@@O@@@xA@@@O@@@|@@@pK@@@o@@@|B@@P  G@t  C@X A@`  A@X@|@@@@m@@@pC@@Zo@@x A@@h}C@@@tA@@@~@@@`O@h@tA@  O@@}_@@@@ @@@xO@@@wC@@tt@@@GM@@|PC@`Kt@@!@M@PKPC@|  O@   C@@PC@@@t@@@@M@@  C@p _@@!@@@@G@@@pA@@@|_B@@  C@@@~A@@@~@@@@O@@@pA@B@_@p  A@P K@@@}o@@| G@PG@@@!@@@`K@@@tZg@@} _@Pg`O@t@PK@M@tBPG@M@pCxC@t o@@t_@@|  C@}  @@@@G@@@tB@@@O@@@tA@@@O@@@xA@@@O@@@pA@@@m@@@pC@@@m@@@pC@@@t B@p  B@^@^@PK@O@xAxA@tiG@@t_@@@ _@@~@]@pC@O@|@PK@o@|@`  G@`}o@@P A@@  C@tAtA@O@|@pC@O@|@pC@]@}@@  O@@uyC@@@|@@@`K@@@~@@} K@` G@@@",
	"` A@@NpA@pBt@@N@^@PC@G@t@pA@M@!@PC@G@t@pA@M@!@PC@C@pAx@@t@K@@to@@@PA@@X_@@PAG@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@xA@@h I@@t_@@pW_@@F@O@`BPK@@@tB@@@M@@@pA@@@N@@@p@@@@K@@@L@@@p@@@@_UE@|  C@x @@`K~@@d@n@@A@K@@@x@@@@K@@P A@@@xC@@@tA@@@^@@@`K@D@T@@E`A@` E@@@@l@@@pK@@@}@@@PM@@@QC@@ht@@@AM@@dPC@@At@@t  K@jZg@@@t@@@@m@@@vo@@  C@pUU@@L@@@@C@@@p@@@@d A@@gvA@@@tB@@@!@@@@G@@@xB@A@E@PIV@@p B@@@`I@@@K@@@n@@@pB@@@E@@@pRI@@]uG@PGPK@t@pA@M@!@PC@G@xBx@@t@G@@tg@@|  C@WU]@P@@C@D@T@@B@C@@@d@@@@C@@@l@@@`C@@@l@@@PC@@@!@@@pC@@@^@@@@t_@@PA!@@N@N@PC`C@xAT@@t[A@@to@@`Y @@N@m@pA@G@!@pA@G@L@`KPB@` I@@P A@@EpA@x@xB@M@!@pC@O@|@pC@]@}@@ UG@@VxB@@@O@@@x@@@`K@@@m@@@U@@@@",
	"` A@@^xA@pBpB@N@t@PA@N@T@@C@G@p@pA@L@T@@C@E@x@`C@M@pBpB@xAG@@x_@@tG@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@t_@@pK~@@M@!@pA@M@@@PC@@@!@@@`C@@@l@@@pA@@@G@@@|@@@pC@@@m@@@t  C@P B@@OxB@x@t@@@@N@@@pA@@PO@@@vK@@@PC@@@pA@@@T@P@@E@T@pB@!`G@@to@@@@P@@@@N@@@pC@@@}@@@xM@@@gC@@!x@@PCN@@l`C@pCt@@}  A@@`C@@@x@@@@N@@x G@@E@@@pB@@@l@@@@kB@@xwK@@@PC@@@pA@@@t@@@@M@H@PA@G@n@@GxA@@}K@@@PB@@@n@@@pA@@@M@@@xB@@@G@@@t A@@GxA@t@x@@G@l@pA@C@t@x@@!PK@@to@@t  A@@@M@@@pA@@@M@@@pA@@@M@@@pB@@@M@@@pB@@@M@@@pB@@@M@@@pB@@@F@@@@x_@@`Kt@@l@l@@C@E@pApB@xAE@@t @@PCtB@N@t@PA@L@T@@C@N@t@@oPK@@}G@@P B@@GxB@t@x@@G@L@pA@K@t@x@@!`G@@| @@@`G@@@|@@@`C@@@!@@@PC@@@D@@@@",
	"@}K@@| G@pKpC@^@xAPC@|@|@@O@O@PCpC@|@t@@O@M@pA`G@m@pKxC@x o@@x B@@N@@@tC@@P @@@!M@@@PC@@@t@@@@O@@@pC@@@|@@@@O@@@pC@@@|@@@t A@@ _@@@t_@@p _@@_@o@PBPK@@@|@@@PG@@@}@@@~A@@tK@@`O@@@|@@@@O@@@p  C@| uB@P B@@  A@pB|@@@@M@@@pC@@t_@@` A@@@~A@@@|@@@@n@`B`K@tB|@@| G@@to@@@@|@@@pO@@@}C@@xu@@@OM@@tRC@`Gt@@~@m@p   @XU}E@@@M@@@PC@@@t@@@@N@`UUA@t  B@n@@@PC@@@t}O@@}WO@pG`G@t@pC@@@|@@@@G@@@xA@G`O@P  B@` I@@@x@@@`O@@@~@@@pC@@@m@@@p[I@@} O@PoXG@|@pC@M@t@PK@O@xCtA@t O@@t_@@x_Ue@}  K@@@_@@@xC@@@O@@@tA@@@O@@@tA@@@O@@@xA@@@O@@@pA@@@m@@@PC@@@t_@@p _@@^@O@PCPC@tB|@@|wK@@~ @@xg}@@m@]@pC@O@!@pC@o@]@`  C@`}G@@` A@@} C@xAtA@M@|@PC@M@t@PC@~@}@@} O@@vuA@@@O@@@tA@@xG@@to@@@_@@@@",
	"` B@@FPA@p@p@@F@T@PB@F@L@`C@C@p@p@@L@l@`C@I@X@`A@E@p@p@@X@I@@xo@@@v@@@~M@@@@C@@@p@@@@L@@@@C@@@p@@@@L@@@@C@@@p@@@@L@@@@C@@@p@@@} _@@x_@@PAx@@N@X@`B@L@@@@C@@@d@@@PA@@@E@@@T@@@PA@@@E@@@T@@@PA@D@|  C@P A@`KPC@@@PB@@@X@@@@I@@@T@@@}C@@@PC@@@PA@@@p@@@@L@@@PA@e@E@@v_@@@@O@@@TC@@@s@@@dL@@@AC@@dp@@`AL@@L@C@`Ap@@!U]B@jjG@@@p@@@@L@@@|_@@  C@p@@@@L@@@@C@@@p@@@@!}C@@I`K@@@`A@@@p@@@@L@@@@C@A@T@PKPC@@}G@@@x_@@pA@@@C@@@L@@@`A@@@dPI@@YkE@pO@I@t@@A@E@p@@C@L@PB`A@pBN@@P_@@|  A@C@X@@@@K@@@p@@@@F@@@PB@@@L@@@`A@@@d@@@@C@@@p@@@@I@@@p@@@@L@@@t_@@PAT@@N@l@PA@E@X@PB@l@N@@Tu@@PIT@@F@d@PB@F@d@`C@F@T@@I`A@@}G@@P @@@EXB@x@P@@I@d@PB@F@d@PA@L@~@@mVN@@TbC@@@T@@@@C@@@T@@@XA@` A@@@",
	"@}K@@~ G@pGxG@~@tCpG@~B|A@o@_@pGpG@|A|A@o@_@pKPO@}@pGxG@x _@@x B@@`O@@@~C@@t @@x O@@^tC@`B}@@@PO@@@tC@@@}@@@PO@@@tC@@@ @@|  _@   G@x A@P  C@~A}APO@}@tAPO@@@tC@@@ @@@~C@@to@@p @@P A@@ A@@p   @|  O@@}g@@~ _@pOpO@~@pK@@@~@@@xG@@|_@@@ _@@@Po@@@pGPG@|AxGPo@t  A@X K@@@|C@@P @@@~O@@pwC@@m}@@xQO@@OtC@|B}@`ozoBt   @UU E@@PO@@@tC@@@}@@   @p  G@|@@@@O@@@pCE@@|}_@` w @xKPo@@@pG@@@|AtA@_@}A~C@} o@@~_@@@}G@@| o@poPO@~@PAPG@@@|y B@_  Ap @ @|C@o@ @pG`O@|BpOPO@x  B@P A@t  O@}  C@@@^@@@pC@@@o@@@tA@@@O@@@tC@@@_@@@xK@@@}@@@PO@@@|C@@@ @@@X K@`  G@|ItK`O@|ApG@o@|_~A@t G@@} O@|A}GPG@|C|A@}@}AxG@   @@} A@` G@@} O@pGpO@}@pKPG@|AtC`_@~A~O@} wA@}G]@@@pG@@@~@pGxG@x  @@x B@@",
	"@v B@tKtCPO@tC|A@|bo@@ tC@pO @@tsO@@}tC@pO~B@|C_@@oPO@tCPoPO@` o@@PC@@z_@@PuG@@@tA@@@]@@@PG@@@tA@@@]@@@PG@@@tA@@@]@@@PG@@@~G@@  _@@P G@@oPo@|@POPo@pKxK@|AT@`o@@@tC@@Po@@`]@@@]@@@^@@@tB@@P   ot   K`}K@@MpK@pAxA@!@~@@@`G@@@!@@@}A@@@vK@@@pC@@@|B`C@o@tBpC@n@m@@~_@@@@t@@@PO@@@~C@@p~@@@KO@@TpC@`A|@@N@O@pivg@TU}G@@@O@@@pC@@@|@@@@O@@| O@`WUA@X@@@@F@@@PB@@@T G@@GxG@@@pC@@@|B@@@o@t@pC@o@~@`KpC@`}G@@@PK@@PG@@@M@@@xB@@@O@@@xYE@@}YO@pKPO@|@pC@O@|@PK@O@pApA@tBM@@t_@@|  C@_U}@p@@K@D@x@@@@K@@@T@@@@C@@@T@@@@C@@@T@@@@C@@@T@@@@C@@@T@@@@x B@PKxB@!@|@@G@M@pCpC@tKn@@t B@`[ B@n@}@PC@]@|@`G@m@xB@O@G@@}e@@` A@@MpC@xBxA@O@|@pC@o@|@pK@]@|B@_XO@@}qC@@@n@@@pC@@@O@@@^@@@!B@@@",
	"p B@@  B@tg @@}yO@p_~C@|g @@ yO@p_~C@|g @@ yO@P_~C@tg @@| K@@~o@@@tC@@X @@p O@@| C@@P @@@tO@@@}C@@P @@@tO@@@}C@@P @@@tO@@@}C@@P @@@~G@@x O@@ vG@pO~C@|S @@@|G@@P @@@|G@@P @@@|K@@p_@@@~C@@p  A@| _@@t B@P  B@|W_@@ zO@`J}A@@to@@` C@@` C@Ti @@ zO@po~C@tW @@~ K@@~o@@@|_@@` G@@t A@@ _@@x G@@] A@p{_@@~|G@PG A@|  A@  _@PU K@@p_@@@|G@P  A@t _@@}B@@Po@@@t _@@} O@P_|C@@@ B@@po@p_|K@|G @@}yO@@  A@` G@@P A@@  A@tG @@}QE@p_H@@| o@@  O@p_|C@|G @@ qO@P_|C@tg @@| G@@|_@@| G@@  A@@P_@@@tG@@@ B@@pO@@@~C@@P_@@@|G@@@ B@@pO@@@~C@@P @@@|G@@@~_@@p o@@}yO@P_~C@tg @@~wG@@  @@t _@@}yO@p_|C@|G @@}yO@`  A@` G@@x A@@  A@tg @@}qO@p_|C@|G @@}qO@P  C@p  @@`rO@Pe|C@tg @@~ G@@~o@@@",
	"@ A@@~uC@pCxA@^@|@PK@M@t@PK@O@tBpC@m@t@PK@m@t@`G@O@pCxA@xWO@@p_@@@XA@@v_@@PiG@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@XuWA@   B@}G@@tUO@@@PG@@@pC@@@|@@@PK@@@~@@@pC@@@O@@@|@@@PC@@@^@@@pWUB@|  @@~_@@PW @@@@O@@@PC@@@|@@`uC@@t_@@@@}@@@@m@@@`G@@@xA@@@o@@]}A@P K@@@@~@@@pO@@@}C@@x}@@@GO@@tpC@`K|@@!@O@Pgvg@t  G@@@O@@@pC@@@|@@@@O@P  @@tUI@@M@@@PC@@@t@@@@}G@@@vO@@@`O@@@pC@@@t@@@@O@@@xC@PWo@@t_@@@@}G@@~UC@pC@@@n@@@PC@@@|tK@@_wG@pGpK@|@xA@O@!@PC@G@xAt@@tUG@@to@@|  B@  o@@@PC@@@n@@@pC@@@n@@@pA@@@M@@@pA@@@m@@@pC@@@]@@@pC@@@|@@@@t_@@pW_@@n@O@`KPC@pCl@@twA@@|O@@p{o@@MPO@pCPK@|@xB@o@M@`_}A@` K@@P B@@]}A@xB|@@M@^@pC@G@t@xC@^@ @@}]O@@}rC@@@^@@@PK@@@~@@!uC@@}G@@@",
	"` A@@~uA@pCxB@n@|@PC@M@|@PK@O@tBpC@m@|@PK@M@t@`K@O@pCxB@xWG@@x_@@to@@@uK@@@tB@@@m@@@PK@@@tB@@@m@@@PK@@@tB@@@m@@@PK@@@tB@@@m@@@PK@@@}o@@tU_@@@@O@@@PK@@@|@@@@O@@@|B@@PK@@@o@@@|B@@PK@@@^@@@pWUA@|  @@}_@@PU}@@@@m@@@PK@@@t@@@XC@@|_@@@@}@@@@^@@@@G@@@pA@@@]@@_}C@P G@@@@|B@@Po@@@~K@@pyB@@Mn@@tbK@`GxB@!@n@PgZg@t  O@@@n@@@`K@@@xB@@@n@P  @@tUE@@M@@@PC@@@t@@@@]I@@P O@@@PO@@@PK@@@tB@@@m@@@pC@pU_@@|_B@@@}o@@|UI@pC@@@^@@@PK@@@|xG@@ io@pG@O@|@PC@M@t@PK@M@pCpA@xWO@@x_@@|  C@   @@@@O@@@t@@@@G@@@|@@@PK@@@!@@@pC@@@^@@@pK@@@~@@@PG@@@|@@@@x_@@PW}@@!@n@@G@K@pCt@@x[K@@t_@@P[_@@n@_@pC@O@|@pC@m@!@@_uK@@}G@@` A@@]uC@xAxA@M@|@PC@M@t@PK@^@|B@]zo@@~QC@@@|@@@@G@@@|@@TuK@@}g@@@",
	"P B@@]}B@pA|@@M@n@PC`G@|@pA@O@!@pC@G@|@pA@M@!@PC`K@pA|@@tuG@@to@@@x@@@@O@@`}C@@| @@@@M@@@PC@@@t@@@@M@@@PC@@@t@@@@M@@@PC@@@t@@@@M@@@x B@P_}B@!@|@`K@M@@@PC@@@|@@@PK@@@]@@@tA@@pK@@@o@@@|B@@P_UE@|  C@P B@@_}B@tB|@@H@M@@@pC@@@m@@@}C@@@vC@@@xB@@@!@PA@G@t@tB@|uG@@to@@@@|@@@PO@@@~C@@p}@@@MO@@xrC@@G|@@t@O@`KpC@t  G@VU_B@@pC@@@|@@@@O@@  K@pWU@@!@@@@K@@@pjB@@~ K@`GxK@@@pC@@@|@@@@O@T@pC@m@]@@_}C@@}G@@` A@@}uC@pCtB@m@H@PC@@@|tK@@ wG@pKPK@|@pA@M@!@PC@G@pAtB@tWG@@x_@@|  C@UU}@@@@G@@@tB@@@O@@@xA@@@O@@@pA@@@m@@@pC@@@^@@@pC@@@^@@@PK@@@to@@pW_@@^@M@PKPC@pA|@@tQK@@to@@P_o@@]@M@pC@G@|@pA@M@^@@_uC@@}G@@P B@@_}B@tB|@@O@n@pC@G@|@pA@]@]@@ }G@@}qA@@@^@@BPC@tB|@@|uK@@tg@@@",
	"`}A@@FpA@pBt@@N@n@PC@G@t@pA@M@!@PC@G@t@pA@M@l@PC`C@pBt@@t@C@@tg@@@x@@@tO@@PrC@@@|@@@@O@@@pC@@@|@@@@O@@@pC@@@|@@@@O@@@pC@@@|@@@X_B@@~o@@pWo@@F`O@P@PC@@@t@@@@O@@@pB@@@E@@@T@@@`C@@@N@@@x@@@@WUE@|  C@P B@@G~B@h@!@@@@G@@@p@@@@E@@` A@@@xC@@@tA@@@^@`@`K@D@t@@E`C@` E@@@@!@@@pK@@@}B@@Pn@@@aK@@XxB@@An@@d`K@@AxB@t  K@jZg@@@xB@@@m@@@zo@@  K@pUU@@L@@@@C@@@p@@@@! K@@IxC@@@xA@@@|@@@@G@@@pB@A@N@PAX@@p_A@@@`I@@@K@@@n@@@pB@@@E@@@pRI@@]wG@PGPK@t@pA@M@!@PC@G@xBp@@t@K@@tg@@|  K@_U}@P@@I@D@X@@@@C@@@T@@@@C@@@T@@@`C@@@l@@@PC@@@!@@@pC@@@^@@@@t_@@PA!@@L@N@`K`C@pAT@@t[A@@t_@@`[ @@L@m@PA@G@!@pA@M@L@@GpB@@ I@@P B@@EpB@t@t@@O@n@pC`G@|@xA@m@_@@ ]K@@ft@@@@G@@@x@@@`K@@@M@@@e@@@@",
	"` A@@NxA@pA|@@n@^@PC`G@|@pC@O@|@pC@O@|@pA@m@!@PK`K@pAt@@tBK@@to@@`M@@@ C@@@t@@@@M@@@PC@@@t@@@@M@@@PC@@@t@@@@M@@@PC@@@t@@@@O@@@} @@@}_@@x@]@@N@O@@ApK@@@|@@@@O@@@xA@@@O@@@x@@@@K@@@!@@@pA@@@_UI@|  A@~_@@pB|@@L@m@@BPK@@@|@@@PC@@P B@@@~A@@@~@@@@o@P@pC@L@|@@KPC@P G@@@@l@@@`K@@@|B@@po@@@eK@@pxB@@Kn@@X`K@@KtA@|  C@jZg@@@xB@@@n@@@|_@@  A@pUe@@L@@@@C@@@pUB@@| C@@B~C@@@|B@@@m@@@PK@@@t@@@@O@`@|@@x A@@@PG@@`G@@@n@@@pA@@@O@@@pYI@@}uG@PKPG@|@xC@O@|@PK@O@xAxA@tBM@@t_@@t  C@]U}@PA@I@@@p@@@@E@@@x@@@@M@@@pB@@@M@@@xA@@@O@@@xA@@@O@@@xC@@@t_@@PC!@@^@M@`GPC@pC|@@tkC@@to@@@Wo@@!`o@PKPG@t@xA@m@^@@OpC@@}G@@P A@@OxA@tBt@@O@^@pC`G@|BxA@~@^@@}uK@@V~@@@@G@@@t@@@`K@@@m@@@]@@@@",
	"P B@@_}B@xA|@@M@M@pC`K@|@xA@O@!@pC@G@|@xA@O@n@PCPC@xA|@@|uK@@to@@@!@@@PG@@p A@@@^@@@`G@@@xA@@@^@@@`G@@@xA@@@^@@@`G@@@xA@@T}E@@  C@@}o@@tW_@@B@O@@@pC@@@|@@@@O@@@tB@@`O@@@~@@@pC@@@O@@@|@@@PWUI@t  A@t B@PW}A@H@|@@@@O@@@pA@@TG@@@ B@@@tA@@@t@@@@m@@@PC@H@|@@_uK@`}g@@@@|@@@pO@@@ C@@t|@@PKO@@mpC@xA|@@O@o@p  _@hj~B@@@O@@@pC@@@|@@@@O@P  C@tUU@@m@@@PK@@@tB@@@}U@@P  B@@@}@@@@O@@@PC@@@|@@B`O@pW}@@x A@@@}G@@|UA@pK@@@^@@@PC@@@|vG@@ uG@pCPK@|@pA@O@!@PC`G@xAtB@tuG@@to@@|  C@UU}@@@@O@@@tB@@@O@@@tB@@@O@@@tB@@@O@@@tB@@@O@@@tB@@@O@@@tB@@@t_@@PW}@@!@^@`G@G@xCxA@tKM@@| @@Pc @@n@^@PC@O@tBpC@^@^@@ uC@@}G@@P A@@]}A@xAtB@M@!@pC@O@t@pC@^@|@@ uO@@}yC@@@!@@@PC@@@^@@TuC@@}G@@@",
	"@}A@@!PA@PCpB@|@|@`G@o@tAPK@m@tBPK@m@tBPK@^@|@@G@O@PCpB@pAG@@p_@@`E@@@vA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@O@@@vG@@@t_@@Pw_@@D`o@`@PG@@@xB@@@M@@@pB@@@F@@@p@@@@A@@@D@@@P@`@@]UO@|  A@P_@@@i}@@H@m@@@PC@@@T@@@@A@@@}A@@`}A@@@~@@@@O@@@PC@@@l@@EPA@P I@@@@!@@@PG@@@vA@@P!@@@CG@@dpA@`A!@@D@G@PBxA@|  G@@`G@@@pA@@@!@@@@G@@p C@@^U@@p@@@@F@@@p_@@@t A@@@~B@@@~@@@@M@@@`C@@@p@@@@I@PIX@@x_@@@@Pe@@`K@@@m@@@xA@@@O@@@xyO@@]`O@pC`G@|@pC@O@|@PK@O@xApB@tBE@@x_@@p  C@^U]@P@@C@@@T@@@@K@@@p@@@@E@@@pB@@@N@@@PA@@@l@@@@C@@@T@@@@K@@@vo@@xBn@@G@E@pCPA@tAL@@|{@@@|K@@@uK@@lxK@PApC@!@t@@O@N@`GpB@` K@@P B@@ExA@t@t@@O@^@pC@O@|@pC@m@|@`OPG@@ vB@@@O@@@t@@@`K@@@m@@`e@@@@",
	"` C@@~uC@pCxA@^@|@PK@O@t@PC@M@t@PC@M@t@PC@m@|@PG@O@pCtB@tWO@@x_@@@X@@@PG@@@}A@@|]@@@aG@@@xA@@@^@@@`G@@@xA@@@^@@@`G@@@xA@@@^@@@`G@@@~o@@tWo@@F`O@@@pC@@@|@@@PG@@@|@@@PG@@@~@@@pC@@@]@@@xC@@@ UI@t  C@t_@@PW_@@@@O@@@pK@@@|@@@PK@@@_@@@` @@@@]@@@`G@@@xC@H@]@@_}C@`}G@@@@PB@@@m@@@xK@@@ B@@|m@@pcK@@mxB@tBn@`oZg@t  G@@@^@@@`K@@@xB@@@n@P  B@tUE@@M@@@PC@@@tUA@@} C@PA|A@@@~@@@@O@@@pC@@@|@@@PG@PW @@P A@@@t@@@pG@@@_@@@tA@@@O@@@tUA@@  K@pGxC@|@tB@O@m@PCPK@tB|@@|uG@@to@@|  C@  _@@@PC@@@^@@@PC@@@^@@@PK@@@!@@@PK@@@|@@@PG@@@|@@@`O@@@tA@@@t_@@pW_@@^@O@`GpC@pC|@@xwC@@|_@@pk_@@]@o@pC`G@|@xA@o@o@`_}C@` G@@P B@@_}A@xA|@@m@n@PC`G@tBxA@~@_@@} G@@V}@@@`G@@@|@@@pG@@@_@@@pB@@@",
	"` A@@}uC@pApA@m@|@PC@M@|@PK@O@tBpC@m@|@PK@M@t@PK@O@pApA@tUO@@t_@@@t@@@PO@@P C@@X}@@@@O@@@pC@@@|@@@@O@@@pC@@@|@@@@O@@@pC@@X}U@@} O@@}_@@tW @@B@]@@@@G@@@xA@@@m@@@pC@@@o@@@|B@@pK@@@o@@@~@@@pWUE@|  K@t A@PWuC@H@tA@@@^@@@PC@@Xo@@@ A@@@pK@@@pC@@@|@@@@O@H@tA@_uG@`}o@@@@xC@@@ @@@|O@@psC@@m|@@tBO@`GpC@^@|@PgjoBt   @@@|@@@@O@@@pC@@@|@`  O@xWUB@^@@@`G@@@xA@@@~ A@`W}C@@@tA@@@|@@@@O@@@pC@B@]@pW}A@X K@@@vo@@tWI@PG@@@|@@@PK@@@tvo@@ W_@pC@o@|@`G@O@xAPK@^@pCpC@tWo@@x B@t  O@VUuC@@@^@@@PC@@@^@@@pC@@@^@@@pC@@@^@@@pC@@@m@@@pC@@@m@@@pC@@@t B@pW}A@]@|@PC@M@tApC@|Kn@@| B@pc}B@M@|@pC@n@|@`K@_@|@@_uG@@}o@@` K@@}uK@xApC@m@xBPC@!@t@@O@^@xC@}u_@@~gG@@@xB@@@O@@@tB@XuG@@~g@@@",
	"fA@@prB@@ll@@@KK@@prB@@ll@@@KK@@prB@@ll@@@KK@@prB@@ll@@@KK@@`Y@@@PA@@@^@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@@G@@@pA@@@!@@@PU@@@LL@@@CC@@pp@@@DN@@@PC@@@l@@@pC@@@N@@@pA@@@lH@@@KB@@pb@@@!F@@@UA@@pp@@@LL@@@CC@@Pp@@@@L@@@pA@@@p@@@Hl@@@CK@@ppB@@Ll@@@CK@@PU@@@@!@@@`G@@@tA@@@]@@@HG@@@qA@@`!@@@AG@@pzC@@@!@@@@G@@@pA@@@!@@@@O@@pY@@@lD@@@KA@@pB@@@l@@@@WA@@ppB@@Hl@@@@K@@ppB@@Ll@@@CK@@ppB@@TF@@@eA@@pr@@@lL@@@KC@@pB@@@!E@@@KK@@prB@@ll@@@KK@@prB@@ll@@@KK@@PY@@@d~@@@AG@@PpB@@HN@@@`C@@@t@@@@G@@@pB@@@N@@@PC@@@T@@@@G@@@pB@@@N@@@PY@@@ll@@@KK@@prB@@ll@@@KK@@`U@@@lL@@@KK@@prB@@ll@@@KK@@prB@@XF@@@fA@@prB@@ll@@@KK@@prB@@ll@@@KK@@prB@@Xn@@@@K@@ppB@@Ll@@@CK@@PY@@@@",
	"tG@@` K@@t A@@}_@@PkG@@tzA@@m^@@PkG@@tzA@@m]@@P G@@t A@@}O@@@}A@@PC@@@ @@@pO@@@|C@@@~@@@@O@@@pC@@@|@@@@O@@@pC@@@ B@@p_@@@|G@@@ A@@@}A@@p B@@~_@@` G@@xvA@@Dm@@@xC@@`O@@@|d@@`KG@@t A@@ _@@p G@@| A@@}_@@P G@@t A@@]m@@`qA@@@M@@@pO@@@XK@@XtA@@O]@@p G@@t A@@~o@@@}A@@@~@@@pO@@@~C@@P @@@!O@@PsC@@!|@@@ o@@`uK@@@|@@@po@@@|G@@@ A@@p_@@@ G@@p A@@|o@@@gB@@xB@@@~G@@P K@@XtA@@F]@@pSG@@| A@@ o@@P C@@Po@@@tG@@` C@@t B@@}_@@PkI@@tf@@@}O@@PWG@@tzA@@m^@@P G@@t B@@~O@@@}B@@| A@@ _@@p G@@|zA@@ON@@`qA@@@m@@@pC@@@~@@@`O@@@tA@@@]@@@pG@@@|A@@@}A@@x @@@}o@@P K@@tvB@@|O@@@}A@@x @@@m^@@PkG@@t A@@}o@@` C@@Po@@@tK@@` C@@t B@@}_@@PSG@@ttA@@]]@@` G@@`vA@@m]@@P G@@t B@@~O@@@}A@@@",
	"` B@@npA@pAx@@m@!@pC@O@|@pC@O@t@pC@M@|@pC@O@|@PK@G@pAx@@t@G@@xo@@@!@@@xC@@P @@@HM@@@PC@@@t@@@@M@@@PC@@@t@@@@M@@@PC@@@t@@@@M@@@|o@@@x A@PApC@E@pCpB@|@!@@O@}ApC@]@]@@@xA@@`G@@@n@@@t@@@`C`@@|UM@`  C@x o@@^uB@@@G@@@tI@@@iO@@@`G@@@pC@@@tB@@@m@@@pC@@@^@L@pC@E`G@@vg@@@@d@@@`K@@@|B@@pm@@@EK@@tpB@`Cl@@!fK@pU}_@@@!@@@@K@@@pB@@@l@@@t_@@UU@@p A@@L@@@@w_@@pA~@@H@^@@@@M@@@PK@@@tB@@@M@@@pC@B@n@PAxA@P A@@@}I@@n`K@pA@@@n@@@PSwA@|FpA@O@t@pC@^@|@`G@M@xBPK@M@pApC@xBN@@x_@@|  G@WU]@P@@C@@@T@@@@C@@@T@@@`C@@@t@@@@G@@@x@@@@M@@@pC@@@|@@@@ B@@to@@PCL@@l@I@@GpB@pgO@@p B@@~ A@xB}@@G@]@p@@O@L@pA@I@^@@KxC@@uG@@` A@@EpA@xBpB@M@|@pC@M@|@PK@O@xBpC@m@xBXK@pu|@@@@O@@@xB@T@G@@to@@@",
	"@@@TE@@tAA@xAP@`G@L@n@PAxA@N`G@pA!@@OPC@|@l@PK`A@o@d@~B@EvA@@}I@@@@@@K@@@}@@@|C@@dO@@`t@@@PC@@@M@@@t@@@`K@@@n@@@pA@@@O@@@t@@@@C@@@@@@@PC@@Pg@@`G@@@m@@@`@`@@@@M@@@~B@@|A@@tA@@tA@@xA@@xA@@pW O@|gJ@@@@@~O@@]J@@T@@@@@@N@@@vA@@VB@PUB@@@PA@@@x@@@@E`A@tBL@PG@CXo@@ g@@@@@@x@@@tO@@tu@@TRC@xBm@PAtBPKPK@mV}APW}i@@@G@@@!@@@pC@@@M@@@pB@@@@@P C@@E@@@T@@@PA@@@E@@@tUA@@GPA@@@T@@@@K@@@t@@@PK@A`o@P`_@@p_B@@@@@~@@@^B@@tB@@pC@@@O@@@|VA@PGpB@^@l@pC`C@N@!@pAPC@l@M@@It@@@uB@@@@V  @`i`C@@@M@@@t@@@PC@@@O@@@|@@@pC@@@O@@@|@@@pC@@@M@@@tB@@@K@@@@@@P A@PIx@@F@M@p`_@@l_@@Po@@P A@@_x@@|@L@`C@C@l@t@@C`K@PB]@@P B@@@@tO@@xGL@PG`C@o@d@t@`C@K@l@p@xC@LXO@@Tt@@@PC@@@M@@@t@@@xA@@pA@@@@"
};

const int white_regions50[]  ={1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,99,99,99,99,99,99,99,99,99,99,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,1,1,0,0,0,1,0,1,0,2,1,99,99,99,99,99,99,99,99,99,99,1,1,3,0,0,0,0,1,2,1,2,1,1,2,2,1,2,1,3,2,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,0,0,2,0,1,0,0,0,1,0,1,0,2,1};
const int white_regions20[]={1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,1,1,1,0,3,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,1,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,2,2,1,0,0,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,2,1,1,1,1,0,0,0,2,1,2,1,0,0,1,2,2,1,2,1,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,1,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,1,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1};

const int left_regions50[]={0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,1,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,99,99,99,99,99,99,99,99,99,99,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,2,1,2,0,2,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,0,1};
const int left_regions20[]={0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,0,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,2,2,1,1,0,1,0,1,0,0,1,2,0,0,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,0,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,2,0,0,0,0,1,2,1,1,0,1,0,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,1,0,1,0,1,0,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,2,1,1,0,1,0,1};

const int right_regions50[]={0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,2,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,2,2,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,1,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0};
const int right_regions20[]={0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,1,1,1,0,1,0,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,1,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,1,0,0,1,1,0,0,0};
const int is_left_region_highter[]={0,0,1,0,0,2,2,1,1,1,0,0,1,1,0,2,2,1,0,1,0,1,1,1,0,0,2,0,1,0,0,0,1,1,0,2,2,1,0,1,0,0,1,1,0,2,2,1,0,1,0,1,1,1,0,2,2,1,2,1,0,1,1,1,2,2,2,0,2,1,0,1,1,1,0,2,2,1,2,1,0,1,2,2,1,2,2,1,2,1,0,1,1,1,0,2,2,0,2,1,0,0,2,1,0,2,2,1,2,1,0,0,1,1,2,2,2,1,2,1,0,0,1,2,0,2,2,1,0,1,0,2,0,1,0,2,0,1,2,1,0,0,1,1,0,2,2,1,0,1,0,0,1,0,0,1,2,1,0,0,0,0,1,1,2,2,2,1,0,1,0,1,2,2,2,2,2,1,1,0,0,1,1,1,2,2,2,1,2,1,0,1,1,1,0,2,2,1,0,1,0,1,1,0,2,2,2,1,2,1,0,0,1,1,0,2,2,1,1,1,0,1,1,1,0,0,2,1,2,1,0,1,1,1,2,2,2,1,2,1,0,1,1,1,0,2,2,1,0,1,0,1,1,1,0,2,2,1,2,1,0,0,1,0,0,2,2,1,2,1,0,1,1,1,0,2,2,1,2,1,0,0,1,1,0,2,2,1,2,1,0,0,1,1,0,2,2,1,0,1,0,1,1,1,2,2,2,1,2,1,0,1,1,1,2,2,2,1,2,1,0,1,1,1,0,2,2,1,2,1,0,1,0,1,0,2,2,1,2,1,0,0,1,1,0,2,2,1,1,1,0,1,1,1,0,2,2,1,2,1,0,1,1,1,2,2,2,1,2,1,0,1,1,2,2,2,2,1,2,1,0,0,1,2,2,2,2,1,2,1,0,1,1,1,2,2,2,1,0,1};

vector<string> s, s1, s2, s3; //s - all numbers, s1 - first number, s2 - second number, s3 - third number in ascii graphics in original resolution

bool filled1=false, filled2=false, filled3=false; //filled1 = true, if corresponding number was written in its array s1
char ch1[N][N], ch2[N][N], ch3[N][N]; //all numbers in ascii graphic, resolution N*N
bool trash=false;

//DECOMPRESS fonts patterns---------------------------------------------------------------------------------------------------------------------

vector<string> F; //fonts patterns

inline char convert (bool a, bool b) {
	if ((!a)&&(!b)) return '.';
	if ((!a)&&b) return '%';
	if (a&&(!b)) return '#';
	return '@';
}

void decompress() { 
	vector<bool> v(6);
	char n, t;
	for (int i=0; i<NumberOfFonts; i++) {
		F.push_back("");
		for (int j=0; j<(10*N*N/3+(10*N*N)%3+1); j++) {
			n=F_compressed[i][j];
			if (n==32) n=127;
			else if (n==33) n=92;

			F[i].push_back(convert(n&(1<<0),n&(1<<1)));
			F[i].push_back(convert(n&(1<<2),n&(1<<3)));
			F[i].push_back(convert(n&(1<<4),n&(1<<5)));
		}
	}
	F.back().resize(F[0].size());
}

//TRIM----------------------------------------------------------------------------------------------------------------------------------------------
void trim(vector<string> &s, bool make_square=false, bool sssp=false) {  
	//if (!make_square) trim all sides; else (if only one number) trim left, up, down and make a square.
	//sssp = s4itat svetlo-seroe pustim
	bool flag=true;

	while(flag) { //trim bottom
		for (int i=0; i<s.back().size();i++) 
			if (s.back()[i]!='.') {
				if (!((s.back()[i]=='%')&&sssp)) {
					flag=false;
					break;
				}
			}
			if(flag) s.pop_back();
			if (s.size()==0) return;
	}

	int count=0; //trim top
	flag=true;
	int w=s[0].size(), h=s.size();

	for (int i=0; i<s.size(); i++) {
		for (int j=0; j<s[i].size(); j++)
			if (s[i][j]!='.') {
				if (!((s[i][j]=='%')&&sssp)) {
					flag=false;
					break;
				}
			}
			if (flag) count++;
			else break;
	}	
	s.erase(s.begin(),s.begin()+count);

	h=s.size();
	//------------------------------------------------
	count=0;  //trim left side
	flag=true;
	for (int j=0; j<w;j++) {
		for (int i=0; i<h; i++) {
			if (s[i][j]!='.') {				
				if (!((s[i][j]=='%')&&sssp)) {
					flag=false;
					break;
				}
			}
		}
		if (flag) count++;
		else break;
	}

	if(count) { 
		for (int i=0; i<s.size(); i++) {
			s[i].erase(s[i].begin(), s[i].begin()+count);
		}
		w=s[0].size();
	}

	//------------------------------------------------
	if (!make_square) {//trim right side
		count=0;  
		flag=true;

		for (int j=w-1; j>0;j--) {
			for (int i=0; i<h; i++) {
				if (s[i][j]!='.') {
					if (!((s[i][j]=='%')&&sssp)) {
						flag=false;
						break;
					}
				}
			}
			if (flag) count++;
			else break;
		}

		if(count) 
			for (int i=0; i<s.size(); i++) {
				s[i].erase(s[i].end()-count, s[i].end());
			}
	}
	//----------------------------------------------------------
	else { //make vector<vector<char>> s squared
		for (int i=0; i<h; i++) {
			s[i].resize(h,'.');
		}
	}
}
//DIVIDE BY LINES and related functions------------------------------------------------------------------------------------------------------

void delete_border(vector<string> &sn) { //1/4 left and right, 1/8 up, down
	int horiz,vert;
	horiz=sn[0].size()/4;
	vert=sn.size()/8;
	sn.erase(sn.end()-vert, sn.end());
	sn.erase(sn.begin(), sn.begin()+vert);
	for(int i=0; i<sn.size(); i++) {
		sn[i].erase(sn[i].end()-horiz,sn[i].end());
		sn[i].erase(sn[i].begin(),sn[i].begin()+horiz);
	}
}

void check_for_border() { 
	trim(s1);
	int w=s1[0].size(), h=s1.size();

	for (int i=(h/4); i<((3*h)/4); i++) { //let it be border conditions
		if (s1[i][0]=='.') 
			return;
		if (s1[i][w-1]=='.') 
			return;
	}

	//if program is here, s1 has a border
	delete_border(s1);

	//if s1 has a border, s2, s3 are bordered too
	trim(s2);
	delete_border(s2);

	if (filled3) {
		trim(s3);
		delete_border(s3);
	}
}

void fill_sn(vector<string> &sn, vector<int> lines) { //fill s1, s2, s3 using lines[] - array with coords of empty vertical lines
	int l, r;
	if(&sn==&s1) {
		l=0;
		r=lines[0];
		filled1=true;
	}
	else if(&sn==&s2) {
		l=lines[0]+1;
		r=lines[1];
		filled2=true;
	}
	else if (&sn==&s3) {
		l=lines[1]+1;
		r=s[0].size();
		filled3=true;
	}
	for (int i=0; i<sn.size(); i++) {
		for (int j=l; j<r; j++){
			sn[i][j]=s[i][j];
			s[i][j]='.';
		}
	}
}

void find_vertical_lines (const bool sssp=false) { ///sssp = s4itat svetlo-seroe pustim


	vector<int> lines;

	bool flag;
	int w=s[0].size(), h=s.size(), j=0;

	while (j<w) {
		flag=true;
		for (int i=0; i<h; i++)
			if (s[i][j]!='.') {
				if (!((s[i][j]=='%')&&sssp)) {
					flag=false;
					break;
				}
			}	

			if (!flag) j++;
			else {
				lines.push_back(j); //one empty verticle line was found

				while (j<w) { //if verticle line is wide j++
					for (int i=0; i<h; i++) {
						if (s[i][j]!='.') {
							if (!((s[i][j]=='%')&&sssp)) {
								flag=false;
								break;
							}
						}
					}	
					j++;
					if (!flag) break;
				}	
			}
	}

	int n=lines.size();
	if (n>2) {
		cout<<"Error: more than 2 empty vertical lines"<<endl;
		return;
	}
	if (!n) return;

	if (n==2) {
		fill_sn(s1, lines);
		fill_sn(s2, lines);
		fill_sn(s3, lines);

		check_for_border();

		trim(s1,true);
		trim(s2,true); 
		trim(s3,true);

		return;
	}

	//if (n==1) - only one verlical line was found:

	if(!(filled1||filled2||filled3)) {
		if(lines[0]<(s[0].size()/2)) {
			fill_sn(s1,lines);
			trim(s1, true);
		}
		else {
			lines.push_back(lines[0]);
			fill_sn(s3,lines);
			trim(s3, true);
		}
		return;
	}

	if (filled3){
		lines.push_back(s[0].size());
		fill_sn(s1,lines);
		fill_sn(s2,lines);
		trim(s1, true);
		trim(s2, true);
		return;
	}

	//if filled1
	lines.push_back(lines[0]);
	lines[0]=0;
	fill_sn(s2,lines);
	fill_sn(s3, lines);
	trim(s2,true);
	trim(s3,true);
}
//FIND CONNECTED REGIONS and related functions--------------------------------------------------------------------------------------------------------------------
vector< vector<int> > array_of_labels;
vector<int>labels_id; //sperva dlya i-oi metki labels[i] = i. Kogda nahodim, chto metka i  ekvivalentna metke j, stavim label[i]=j (ili label[j]=i).
set<int>actual_labels;//zapolnyaetsya posle zameni ekvivalentnih metok

void init_labels(const vector<string> &s) { 
	int h=s.size(), w=s[0].size();
	array_of_labels.clear();
	array_of_labels.resize(h);
	for(int i=0; i<h; i++)
		array_of_labels[i].resize(w,0);
	labels_id.clear(); 
	labels_id.resize(1,0);
	actual_labels.clear();
}

int up(int i,int j) {
	if (i==0) return 0;
	return array_of_labels[i-1][j];
}

int left(int i,int j) {
	if (j==0) return 0;
	return array_of_labels[i][j-1];
}

int left_up (int i, int j) {
	if ((i==0)||(j==0)) return 0;
	return array_of_labels[i-1][j-1];
}

int left_down (int i, int j) {
	if ((i==array_of_labels.size()-1)||(j==0)) return 0;
	return array_of_labels[i+1][j-1];
}


int new_label(int i, int j) {
	int t=labels_id.size();
	labels_id.push_back(t); //labels_id[t]=t; 
	return t;
}

int get_label(int label) {
	if (label==labels_id[label]) return label;
	return (get_label(labels_id[label]));
}

void add_equiv (int m1, int m2) {
	int a, b;
	a=get_label(m1);
	b=get_label(m2);
	if(a<b)
		labels_id[b]=a;
	else labels_id[a]=b;
}

void add_equiv_if_need (int label, int main_label) {
	if (!label) return;
	if (label!=main_label) add_equiv (label, main_label);
}

void set_label(int i, int j, bool second_time=false) {
	int t;
	if (!second_time) {
		t=up(i,j);
		if(t) {
			add_equiv_if_need(left(i,j),t);
			array_of_labels[i][j]=t;
			return;
		}

		t=left (i,j);
		if (t) { 
			array_of_labels[i][j]=t;
			return;
		}
	}

	else {
		t=left_up(i,j);
		if (t) {
			add_equiv_if_need(left(i,j),t);
			add_equiv_if_need(left_down(i,j),t);
			add_equiv_if_need(up(i,j),t);
			array_of_labels[i][j]=t; 
			return;
		}
		t=left(i,j);
		if (t) {
			add_equiv_if_need(left_down(i,j),t);
			add_equiv_if_need(up(i,j),t);
			array_of_labels[i][j]=t; 
			return;
		}
		t=left_down(i,j);
		if (t) {
			add_equiv_if_need(up(i,j),t);
			array_of_labels[i][j]=t; 
			return;
		}
		t=up(i,j);
		if (t) {
			array_of_labels[i][j]=t; 
			return;
		}
	}
	array_of_labels[i][j]=new_label(i,j);
}

void resolve_equiv() { //prohodit po razmechennomu massivu i pomechaet elementi s ekvivalentnimi metkami odnoi metkoi; mnojestvo ostavshihsya metok zapisivaet v aktual_labels
	for (int i=0; i<array_of_labels.size(); i++)
		for (int j=0; j<array_of_labels[i].size(); j++) {
			if (array_of_labels[i][j]) {
				int t=get_label(array_of_labels[i][j]);
				array_of_labels[i][j]=t;
				actual_labels.insert(t);
			}

		}
}

int count_white_connected_regions(const vector<string> &s) { 
	init_labels(s);
	int w=s[0].size(), h=s.size();

	for (int i=0; i<h; i++) 
		for(int j=0; j<w; j++) 
			if ((s[i][j]=='.')||(s[i][j]=='%'))
				set_label(i,j);
	resolve_equiv();

	for (int i=0; i<h; i++) {
		actual_labels.erase(array_of_labels[i][0]);
		actual_labels.erase(array_of_labels[i][w-1]);
	}

	for (int j=0; j<w; j++) {
		actual_labels.erase(array_of_labels[0][j]);
		actual_labels.erase(array_of_labels[h-1][j]);
	}

	vector<int> countlabels;
	countlabels.resize(actual_labels.size(),0);

	vector<int> actual_labels_vector;
	for (set<int>::iterator iter=actual_labels.begin(); iter!=actual_labels.end(); iter++) 
		actual_labels_vector.push_back(*iter);


	for (int i=0; i<h; i++) 
		for (int j=0; j<w; j++) {
			int t=array_of_labels[i][j];
			for (int k=0; k<actual_labels_vector.size(); k++)
				if (t==actual_labels_vector[k]) {
					countlabels[k]++;
					break;
				}
		}

		for (int i=0; i<countlabels.size(); i++){
			if (countlabels[i]<2){
				actual_labels.erase(actual_labels_vector[i]);
			}
		}

		return actual_labels.size();
}

void copy_labeled_items(vector<string> &sn, int label) {
	for(int i=0; i<s.size(); i++) {
		for (int j=0; j<s[0].size(); j++){
			if(array_of_labels[i][j]==label) {
				sn[i][j]=s[i][j];
				s[i][j]='.';
			}
		}
	}

	if (&sn==&s1) filled1=true; 
	if (&sn==&s2) filled2=true; 
	if (&sn==&s3) filled3=true; 
}

void init_s123() {
	s1.resize(s.size());
	for(int i=0; i<s.size();i++)
		s1[i].resize(s[0].size(),'.');
	s2=s1;
	s3=s1;
}

void reinit_s123() {
	s2.resize(s.size());
	for(int i=0; i<s.size();i++) {
		s2[i].clear();
		s2[i].resize(s[0].size(),'.');
	}
	if(!filled1) s1=s2;
	if(!filled3) s3=s2;
}

inline int mass(vector<string> &a) {
	int h=a.size(), w=a[0].size(), m=0;
	for(int i=0; i<h; i++)
		for (int j=0; j<w; j++)
			if (a[i][j]!='.') m++;
	return m;
}

void find_connected_regions(bool second_time=false) { 

	init_labels(s);
	//find connected regions----------------------------------
	for (int j=0; j<s[0].size(); j++) {
		for(int i=0; i<s.size(); i++) {
			if (s[i][j]!='.')
				set_label(i,j,second_time);
		}
	}

	resolve_equiv();
	//--------------------------------------------------------

	if (actual_labels.size()==1) return;

	vector< vector<string> > crs; //cr - connected regions

	vector<string> cr=s2; //s2 is an empty one
	for (set<int>::iterator iter=actual_labels.begin(); iter!=actual_labels.end(); iter++) {
		copy_labeled_items(cr, *iter);
		crs.push_back(cr);
		cr=s2;
	}

	//now each connected region is an item of vector crs;

	int hmin=s.size(), hmax=0, h;
	vector< vector<string> >crs_copy=crs;

	for (int i=0; i<crs.size(); i++) {
		trim(crs_copy[i]);
		h=crs_copy[i].size();
		if (h>=hmax) hmax=h;
		if (h<=hmin) hmin=h;
	}

	if ((3*hmin)<hmax) trash=true;

	if (trash) {
		for (int i=0; i<crs.size(); i++) {
			if (crs_copy[i].size()<(hmax/3)) {
				crs.erase(crs.begin()+i);
				crs_copy.erase(crs_copy.begin()+i);
				i--;
			}
		}
	}

	if (crs.size()==3) {
		s1=crs[0], s2=crs[1], s3=crs[2];
		filled1=true, filled2=true, filled3=true;
		return;
	}

	if (crs.size()==1) {
		s=crs[0];
		if (trash) find_vertical_lines();
		return;
	}

	if (crs.size()==2) {
		if (!trash) {//check_for_border
			//border begins before digit=>it's in crs[0]
			int h=crs_copy[0].size(), w=crs_copy[0][0].size();
			bool border=true;
			for (int i=h/4; i<(3*h/4); i++) {
				if ((crs_copy[0][i][0]=='.')||(crs_copy[0][i][w-1]=='.')) {
					border=false;
					break;
				}
			}

			if ((h<5)||(w<5)) border=false;

			if (border){
				s2=crs[1];
				filled2=true;
				return;
			}
		}

		if (filled1) {
			s2=crs[0], s3=crs[1];
			filled2=true, filled3=true;
			return;
		}
		if (filled3) {
			s1=crs[0], s2=crs[1];
			filled1=true, filled2=true;
			return;
		}
		//if !(filled1||filled2||filled3)
		if (mass(crs[0])>mass(crs[1])){
			s3=crs[1], s=crs_copy[0];
			filled3=true;
			if (trash) 
				find_vertical_lines();
			return;
		}
		else {
			s1=crs[0], s=crs_copy[1];
			filled1=true;
			if (trash) 
				find_vertical_lines();
			return;
		}	
	}
}

//VERTICAL LINES WITH ONLY ONE POINT WHERE THERE ARE DARK PIXELS FROM EACH SIDE------------------------------------------------------------------------------------
void lines_fill (vector<string> &sn, int a, int b) {
	for (int i=0; i<s.size(); i++) {
		for (int j=a; j<b; j++) {
			sn[i][j]=s[i][j];
			s[i][j]='.';
		}
	}
	if (&sn==&s1) filled1=true; 
	else if (&sn==&s2) filled2=true;
	else if (&sn==&s3) filled3=true;
}

inline int count_mass(int a, int b) { //count mass of part of vector<string> s between vertical lines a and b
	int m=0;
	for (int j=a; j<b; j++)
		for (int i=0; i<s.size(); i++)
			if (s[i][j]!='.') m++;
	return m;
}

inline void delete_line (vector<int> &lines, vector<int> &lines_weight, int i) {
	lines.erase(lines.begin()+i);
	lines_weight.erase(lines_weight.begin()+i);
}


void process_vector_of_vertical_lines (vector<int> &lines, vector<int> &lines_weight) {

	if (lines.empty()) return;

	for (int i=0; i<lines.size()-1; i++) 
		if (lines[i+1]-lines[i]==1) { //select better from lines[i] and lines[i+1]
			if (lines_weight[i+1]<lines_weight[i])   
				delete_line (lines,lines_weight,i);
			else delete_line (lines,lines_weight,i+1);
			i--;
		}
		if (lines.empty()) return;

		if (lines[0]==1) lines.erase(lines.begin());
		if (lines.empty()) return;

		if (lines.back()==s[0].size()-1) 
			lines.pop_back();
		if (lines.size()==0) return;

		//merge back too small pieces-----------------
		vector<int> mass;

		mass.push_back(count_mass(0,lines[0]));
		for (int i=0; i<lines.size()-1; i++)
			mass.push_back(count_mass(lines[i],lines[i+1]));
		mass.push_back(count_mass(lines.back(),s[0].size()));

		int maxmass=0;
		for (int i=0; i<mass.size(); i++)
			if (mass[i]>maxmass) maxmass=mass[i];

		while (3*mass.back() < maxmass) {
			lines.pop_back();
			mass[mass.size()-2]+=mass.back();
			mass.pop_back();
		}

		for (int i=0; i<mass.size()-1; i++) 
			if (3*mass[i]<maxmass) {
				lines.erase(lines.begin()+i);
				mass[i]+=mass[i+1];
				mass.erase(mass.begin()+i+1);
				i--;
			}

			if (lines.size()==0) return;
			//----------------------------------------------

			if (lines.size()>2) return;


			if (lines.size()==2) {
				if ((!filled1)&&(!filled3)) {
					lines_fill(s1,0,lines[0]); 
					lines_fill(s2,lines[0],lines[1]);
					lines_fill(s3, lines[1], s.size());
				}
				return;
			}
			//if lines.size==1

			if (filled3) {
				lines_fill(s1,0,lines[0]);
				lines_fill(s2,lines[0],s[0].size());
			}
			else {
				lines_fill(s2,0,lines[0]);
				lines_fill(s3,lines[0],s[0].size());
			}
}

void find_vertical_lines_with_dark_gray_pixel() {
	int w=s[0].size(), h=s.size(), count;

	vector<int> lines;
	vector<int> lines_weight;

	for (int j=1; j<w; j++) {
		count=0;
		for (int i=0; i<h; i++) {
			if ((s[i][j-1]=='.')||(s[i][j]=='.')) continue;
			if ((s[i][j-1]=='%')||(s[i][j]=='%')) continue;
			if ((s[i][j-1]=='@')&&(s[i][j]=='@')) {
				count+=5;
				break;
			}
			count++;
		}
		if (count<=2) {
			lines.push_back(j);
			lines_weight.push_back(count);
		}
	}
	process_vector_of_vertical_lines(lines, lines_weight);
}
//DIVIDE BY SPECIAL LINES-------------------------------------------------------------

bool is_line_special(int j) {
	for (int i=0; i<s.size(); i++) {
		char a=s[i][j-1],b=s[i][j];
		if ((a=='@')||(b=='@')) return false;
		if ((a=='.')||(b=='.')) continue;
		if ((a=='%')||(b=='%')) continue;
	}
	return true;
}

void find_special_vertical_lines() {
	trim(s);
	int w=s[0].size(), h=s.size();
	vector<int>lines;

	int j1=1;
	while (is_line_special(j1)) j1++;

	int j2=w-1;
	while (is_line_special(j2)) j2--;

	if (j2<=j1) return;

	for (int j=j1+1; j<j2; j++) 
		if (is_line_special(j)) lines.push_back(j);

	vector<int> temp(lines.size(),0);

	process_vector_of_vertical_lines(lines,temp);
}
//DELETE LIGHT GRAY PIXELS (for divide())--------------------------------
inline void delete_light_gray() {
	for (int i=0; i<s.size(); i++)
		for (int j=0; j<s[0].size(); j++)
			if (s[i][j]=='%') s[i][j]='.';
}


vector <int> find_right_border (vector<string> &sn) {
	vector<int> border(sn.size(), 0);

	for (int i=0; i<sn.size(); i++) 	
		for (int j=sn[0].size()-1; j>=0; j--)
			if (sn[i][j]!='.') {
				border[i]=j;
				break;
			}
			return border;
}

void copy_ligth_gray_to_sn(vector<string> &sn, vector<int>&bn, vector<string>&s_copy) {
	for (int i=0; i<sn.size(); i++) {
		for (int j=0; j<=bn[i]; j++) 
			if (s_copy[i][j]=='%') {
				sn[i][j]='%';
				s_copy[i][j]='.';
			}
			for (int j=bn[i]+1; j<sn[0].size(); j++) {
				if (s_copy[i][j]!='%') break;
				sn[i][j]='%';
				s_copy[i][j]='.';
			}
	}

}


void set_light_gray_pixels(vector<string>&s_copy, bool s1_changed, bool s2_changed, bool s3_changed) {
	//find s1, s2, s3 right borderd
	vector<int> b1, b2, b3;

	if (s1_changed) {
		b1=find_right_border(s1);
		copy_ligth_gray_to_sn(s1,b1,s_copy);
	}
	if (s2_changed) {
		b2=find_right_border(s2);
		copy_ligth_gray_to_sn(s2,b2,s_copy);
	}
	if (s3_changed) {
		b3=find_right_border(s3);
		copy_ligth_gray_to_sn(s3,b3,s_copy);
	}

}


//DIVIDE---------------------------------------------------------------------------------

bool divide() {
	init_s123();
	find_vertical_lines();
	if (filled2) return true;

	find_connected_regions();
	if (filled2) return true;

	trim(s,false,true);
	if (s.size()==0) {
		if(filled1||filled3) return true;
		return false;
	}

	trim(s);
	reinit_s123();
	find_vertical_lines(true);
	if (filled2) return true;

	if (!trash) {
		trim(s);
		reinit_s123();
		find_vertical_lines_with_dark_gray_pixel();
		if (filled2) return true;

		trim(s);
		reinit_s123();
		find_special_vertical_lines();
		if (filled2) return true;

		vector<string> s_copy=s;
		bool f1=filled1, f2=filled2, f3=filled3;
		delete_light_gray();
		find_connected_regions(true);

		f1=(f1!=filled1), f2=(f2!=filled2), f3=(f3!=filled3);
		if (s!=s_copy) 
			set_light_gray_pixels(s_copy,f1,f2,f3);
		if (filled2) return true;
	}

	s2=s;
	filled2=true;
	return true;
}

//RESIZE--------------------------------------------------------------------------------------------

int CharToInt (char c) {
	if (c=='@') return 0;
	if (c=='#') return 85;
	if (c=='%') return 170;
	return 255;
}

char IntToChar (int i) {
	int b1=64,b2=137,b3=192;

	if (i<b1) return '@';
	if (i<b2) return '#';
	if (i<b3) return '%';
	return '.';
}

inline int roundup(double i) {
	if (((double)((int)i))==i) return i;
	return (int)i+1;
}

void resize(vector<string> &L, char S[N][N], bool need_trim=true) {   

	if(need_trim) trim(L,true);	

	if (L.size()!=N) {
		double setka[N+1];
		double sum=0;
		double d=((double)L.size()/N);

		for (int i=0; i<N; i++){
			setka[i]=sum;
			sum+=d;
		}

		setka[N]=L.size();

		int l,r,up,down;
		double dl, dr, dup, ddown;

		double area;
		int t;

		for (int row=0; row<N; row++) {
			up=roundup(setka[row]);
			down=setka[row+1];
			dup=(double) up-setka[row];
			ddown=setka[row+1]- (double) down;

			for (int column=0; column<N; column++) {

				l=roundup(setka[column]);
				r=setka[column+1];
				dl=(double)l-setka[column];
				dr=setka[column+1]-(double)r;

				area=(setka[column+1]-setka[column])*(setka[row+1]-setka[row]);
				if(area!=0.0) {
					sum=0;
					for (int i=up; i<down; i++)
						for (int j=l; j<r; j++)
							sum+=CharToInt(L[i][j]);
					if (dl!=0.0) {
						t=0;
						for (int i=up; i<down; i++)
							t+=CharToInt(L[i][l-1]);
						sum+=dl*(double)t;
					}
					if (dr!=0.0) {
						t=0;
						for (int i=up; i<down; i++)
							t+=CharToInt(L[i][r]);
						sum+=dr*(double)t;
					}
					if (dup!=0.0) {
						t=0;
						for (int j=l; j<r; j++)
							t+=CharToInt(L[up-1][j]);
						sum+=dup*(double)t;
					}
					if (ddown!=0.0) {
						t=0;
						for (int j=l; j<r; j++)
							t+=CharToInt(L[down][j]);
						sum+=ddown*(double)t;
					}
					if(dup*dl!=0.0) 
						sum+=(double)CharToInt(L[up-1][l-1])*dup*dl;
					if(dup*dr!=0.0) 
						sum+=(double)CharToInt(L[up-1][r])*dup*dr;
					if(ddown*dl!=0.0) 
						sum+=(double)CharToInt(L[down][l-1])*ddown*dl;
					if(ddown*dr!=0.0) 
						sum+=(double)CharToInt(L[down][r])*ddown*dr;

					S[row][column]=IntToChar((int)(sum/area));
				}
				else S[row][column]='.';
			}
		}
	}
	else 
		for (int i=0; i<N; i++)
			for (int j=0; j<N; j++)
				S[i][j]=L[i][j];

}

//LEFT REGIONS COUNT and related function----------------------------------------

bool skip (vector<string> &s, int i, int j, bool horizontal=true) {

	if (s[i][j]=='.') return true;
	if (s[i][j]=='@') return false;
	if (s[i][j]=='#') return false;

	//%
	if (horizontal) {
		if (i>0)
			if (s[i-1][j]=='.') return true;

		if (i<s.size()-1)
			if (s[i+1][j]=='.') return true;
	}
	else {
		if (j>0)
			if (s[i][j-1]=='.') return true;
		if (j<s[0].size()-1)
			if (s[i][j+1]=='.') return true;
	}
	return false;
}


void fill_black(vector<string> &s, bool left) {
	int w=s[0].size(), h=s.size(), j;

	if (left) 
		for (int i=0; i<h; i++) {

			j=0;
			while (j<w) {
				if (skip(s,i,j)) j++;
				else break;
			}

			if (j<w) 
				for (int k=j; k<w; k++)
					s[i][k]='@';
		}
	else for (int i=0; i<h; i++) {
		j=w-1;
		while (j>0) {
			if (skip(s,i,j)) j--;
			else break;
		}

		if (j>0) 
			for (int k=0; k<j; k++)
				s[i][k]='@';
	}


	for (int j=0; j<w; j++) {
		int i=0;
		while (i<h) {
			if (skip(s,i,j,false)) i++;
			else break;
		}
		if (i<h) 
			for (int k=0; k<i; k++)
				s[k][j]='@';

		i=h-1;
		while (i>-1) {
			if (skip(s,i,j, false)) i--;
			else break;
		}

		if (i>-1)
			for (int k=i; k<h; k++)
				s[k][j]='@';
	}
}

int left_right_regions_count(vector<string> s, bool left, int &upperbound) {
	fill_black(s,left);
	upperbound=s.size();

	int w=s[0].size(), h=s.size(), maxcount=0, i, count, count_white;
	for (int j=0; j<w; j++) {
		i=0, count=0;
		while ((s[i][j]!='.')&&(i!=h-1)) i++;
		if (s[i][j]=='.') 
			if (i<upperbound) upperbound=i;
		while (i!=h-1) {
			count_white=0;
			while (s[i][j]=='.') {
				i++;
				count_white++;
			}
			if (count_white>1) count++;
			while ((s[i][j]!='.')&&(i!=h-1)) i++;
		}
		if (count>maxcount) maxcount=count;
	}

	return maxcount;
}

//COMPARE--------------------------------------------------------------------------------------------
char ch[N][N];
vector<int> result;

int compare(char A[N][N], char B[N][N]) {
	int sum=0;
	int d;
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++) 
			if (A[i][j]!=B[i][j]) {
				d=CharToInt(A[i][j])-CharToInt(B[i][j]);
				if (d<0) d=-d;
				sum+=d;
			}
			return sum;
}

void get_letter_to_ch(int font, int number) {
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++) 
			ch[i][j]=F[font][number*N*N+i*N+j];
}

void move_left_right(char chn[N][N], char chn_shifted_left[N][N], char chn_shifted_right[N][N]) {
	vector<string> sq;
	if(chn==ch1) sq=s1;
	else if(chn==ch2) sq=s2;
	else if(chn==ch3) sq=s3;
	vector<string> sq2=sq;

	double shag=(double)sq.size()/(double)N;
	int sdvig=shag/2;
	if (!sdvig) sdvig=1;
	int w=sq[0].size(),h=sq.size();

	for(int i=0; i<h; i++) { 
		for (int j=w-1; j>=sdvig; j--) 
			sq[i][j]=sq[i][j-sdvig];
		for (int j=0; j<sdvig; j++) 
			sq[i][j]='.';
	}
	resize(sq,chn_shifted_right,false);

	for(int i=0; i<h; i++) { 
		for (int j=0; j<w-sdvig; j++) 
			sq2[i][j]=sq2[i][j+sdvig];
		for (int j=w-sdvig; j<w; j++) 
			sq2[i][j]='.';
	}
	resize(sq2,chn_shifted_left,false);	
}

inline void copych (char ch1[N][N], char ch2[N][N]) { //copy content of ch1 to ch2
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			ch2[i][j]=ch1[i][j];
}

void before_compare (vector<string>&sn, int &white, int &left, int &right, int &left_highter) {
	trim (sn,false,false);

	int left_upperbound, right_upperbound;
	right=left_right_regions_count(sn,false, right_upperbound);
	left=left_right_regions_count(sn,true, left_upperbound);
	white=count_white_connected_regions(sn);

	if (left&&right) {
		int t=left_upperbound-right_upperbound;
		if (t<0) t=-t;
		if (t<3) left_highter=0;

		else	if (left_upperbound>right_upperbound) 
			left_highter=2;
		else left_highter=1;
	}
	else left_highter=0;


	trim(sn,true);
}

void compare_with_patterns(char chn[N][N]) {

	int white, left, right,left_highter;
	if(chn==ch1) before_compare(s1,white,left,right,left_highter);
	else if(chn==ch2) before_compare(s2,white,left,right,left_highter);
	else if (chn==ch3) before_compare(s3,white,left,right,left_highter);

	int min=1000000, minnum=10, minfont=100, t;

	int beginfont=0, endfont=NumberOfFonts-1;
	if(trash) beginfont=12, endfont=12;

	int white_min, white_max, left_min, left_max, right_min, right_max,pattern_left_highter;
	bool white_ok, left_ok, right_ok, left_highter_ok;
	bool flag=false;
	for (int font=beginfont; font<=endfont; font++){
		for (int n=0; n<10; n++) {
			white_min=white_regions20[font*10+n];
			white_max=white_regions50[font*10+n];
			if (white_min>white_max) swap(white_min, white_max);

			left_min=left_regions20[font*10+n];
			left_max=left_regions50[font*10+n];
			if (left_min>left_max) swap(left_min, left_max);

			right_min=right_regions20[font*10+n];
			right_max=right_regions50[font*10+n];
			if (left_min>left_max) swap(left_min, left_max);

			pattern_left_highter=is_left_region_highter[font*10+n];

			white_max=99;

			white_ok=(white>=white_min)&&(white<=white_max);
			left_ok=(left>=left_min)&&(left<=left_max);
			right_ok=(right>=right_min)&&(right<=right_max);

			left_highter_ok= (!pattern_left_highter) || (!left_highter) || (pattern_left_highter==left_highter);

			if ( white_ok && left_ok && right_ok && left_highter_ok ) {
				flag=true;
				get_letter_to_ch(font,n);
				t=compare(chn,ch);
				if(t<min) {  
					min=t;
					minnum=n;
					minfont=font;
				}
			}

		}
	}

	if (!flag) {
		result.push_back(0);
		return;
	}

	char chn_trimmedhard[N][N], chn_shifted_left[N][N],chn_shifted_right[N][N];
	char chn_shifted_left2[N][N];

	if (min>0) {
		move_left_right(chn, chn_shifted_left, chn_shifted_right);

		if (chn==ch1) {
			trim(s1,true,true);
			resize(s1,chn_trimmedhard);
		}
		else if(chn==ch2) {
			trim(s2,true,true);
			resize(s2,chn_trimmedhard);
		}
		else if(chn==ch3) {
			trim(s3,true, true);
			resize(s3,chn_trimmedhard);
		}

		int t2;
		for (int font=beginfont; font<=endfont; font++){
			for (int n=0; n<10; n++) {
				white_min=white_regions20[font*10+n];
				white_max=white_regions50[font*10+n];
				if (white_min>white_max) swap(white_min, white_max);

				left_min=left_regions20[font*10+n];
				left_max=left_regions50[font*10+n];
				if (left_min>left_max) swap(left_min, left_max);

				right_min=right_regions20[font*10+n];
				right_max=right_regions50[font*10+n];
				if (left_min>left_max) swap(left_min, left_max);

				pattern_left_highter=is_left_region_highter[font*10+n];

				white_ok=(white>=white_min)&&(white<=white_max);
				left_ok=(left>=left_min)&&(left<=left_max);
				right_ok=(right>=right_min)&&(right<=right_max);
				left_highter_ok= (!pattern_left_highter) || (pattern_left_highter==left_highter) || (!left_highter);

				if ( white_ok && left_ok && right_ok && left_highter_ok ) {

					get_letter_to_ch(font,n);
					t=compare(chn_trimmedhard,ch);
					t2=compare(chn_shifted_left,ch);

					if(t<min) {  
						min=t;
						minnum=n;
						minfont=font;
					}
					if (t2<min) {
						min=t2;
						minnum=n;
						minfont=font;
					}
				}
			}
		}
	}

	result.push_back(minnum);
}

//MAIN-----------------------------------------------------------------------------------
int main() {
	decompress();
	string a;
	while(!cin.eof()) {
		if(cin>>a)
			s.push_back(a);
	}

	trim(s);

	if (!divide()) {
		cout << "Error: couldn't separate digits"<<endl;
		return -1;
	}

	if (filled1) {
		resize(s1,ch1);
		compare_with_patterns(ch1);
	}
	if (filled2) {
		resize(s2,ch2);
		compare_with_patterns(ch2);
	}
	if (filled3) {
		resize(s3,ch3);
		compare_with_patterns(ch3);
	}

	for (int i=0; i<result.size();i++)		cout<<result[i];

	result.clear();
	s.clear();
	s1.clear();
	s2.clear();
	s3.clear();
	filled1=false;
	filled2=false;
	filled3=false;
	array_of_labels.clear();
	labels_id.clear();
	actual_labels.clear();	
	trash=false;
}