#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<set>
const int N=11; //resolution of pattern of each number
const int NumberOfFonts=36;

const char F_compressed[NumberOfFonts][10*N*N/3+(10*N*N)%3+1]={"xo@@Gm@t@M@G`CpBp@l@L@K`CpAx@T@M@!tB@~K@@L@@pC@` @@lL@@@C@@p@@@L@@@C@@p@@@L@@@C@@~G@piO@M@K@@pB@@N@@xA@`G@@m@@tB@`G`@| o@xo@`Gm@T@G@@pA@`O@@tK@@PC@@p@!@N@^xA@~G@@@K@@|B@Po@@NK@prB@El@x@K@  G@@^@@@K@@pB@ _@pA@@L@@`cB@t C@FPC@@p@@@L@G`C`G^@` A@P_@@g^@t@N@G@@pvG@|aG@G`CpAp@t@N@!xA@~G@| O@@pC@@M@@pB@@M@@pB@@N@@pA@@l@@@C@@x@@@~G@xaG@MPC`C!@PwA@!uBpAt@l@L@G`C`G^@` A@xo@`Gn@!@M@K`CpAx@xbO@tgC@@x@T@M@^tB@}K@@",
	"p_@@Gm@t@M@E@CpApB!@L@G@KPCxBt@M@!tB@|G@@N@@xC@P @@DF@@PC@@x@@@N@@PC@@t@@@N@@`C@@~G@paG@M`C@@p@@@M@@t@@PK@@m@@|@@PKJ@| O@xo@@Gm@t@E@@pA@`M@@|K@@PC`BpBt@n@!xA@~G@@`K@@|@@PO@@lC@pz@@EL@x@C@  G`U]B@@C@@p@@} @paB@l@@@[I@xwG@HPC@@pAh@!@M`C@G]@` A@P_@@o^@t@N@E@@puO@|AO@G@KpCpBt@N@|zA@tG@t o@hxC@@N@@pA@@M@@pA@@N@@PA@@!@@@C@@p@@@~G@pQK@NPC`CT@p[K@t @PKt@!@l@G@K`G^@` A@xo@@Gm@t@N@G@KPAxAxAo@t_K@`rBt@M@!tB@~K@@",
	"PUB@gvBxBT@M@npI`G!@xAG@^PCPKpBtBxbG@xo@@N@@uC@@v@@@M@@PC@@t@@@M@@PC@@t@@@m@@Xe@@]G@tjm@G`GPWxAPEm@`tB@xI@`k@@n@HpWuAXUU@x}@@kvBxB^@tRK@Po@@hM@@@GPCpKt@!B!PG@|o@@|@@@G@@xb@@eG@prA@I!@XBG@Uuo@j^J@@G@@TE@@h@p G@dj@@A@@puA@DpA@@tBX@m@GpI`Gm@@UB@PuB@evBxBH@mU@pmv@|A^@g@GPApAx@!@TrK@tg@p _@TUG`BPBh@F@@pB@@G@@xB@@O@@pI@@^B@@e@@@A@@d@@de@@CD@pAA@xo@@im@T@E@E`C@Kd@@UB@TG@`IN@!@K@GpAPC]@PoG@@zB@@m@@pB@PI@@e@@@",
	"P A@  AtK @ PopOxK|C~B `opOtKtK @| G@|_@@tC@` @@}O@| C@o @@pO@@|C@@ @@pO@@|C@@ @@t Bp  B}a `FpO@@}A@tO@p @@ A@|ojP  O|  Cx A`  AtC @@pO@P @@t_@@Po@@xK|K B~ O@~_@@@ @@|O@P C@} @x[O`_tC|[ A   r  o@@}@@PO@  Cp  B|iJ`oJ@t _@}wo@@xG@B~A R_`  C` G@P A@  CtG @ `@p_ B|  @ b_pOpGtG}B| O@t_@|  C   `e}K@`_@@|C@Po@@|C@`_@@tK@@ @@pO@@~_@x _@}rOPo|Cp o@| Gpo|C|C~B roP  C` G@x A@  AtK}B `_PotGx  At__@`xGxG B| G@|_@@",
	"xK@@kC@TPB@IX@pBF@l`A@KX@PBF@TPB@lN@@~B@@I@@xB@Po@@DI@@PB@@d@@@I@@PB@@d@@@I@@PB@@}A@xzB@Ix@@@N@@PA@@N@@pB@@K@@!@@PC@@| C@tK@`kC@hpB@@l@@xC@@v@@@T@@@F@dPA@MN@@}B@@p@@@M@@pC@@y@@XL@@CC@dp@@  @`jK@@p@@@L@@ G@pB@@L@@`c@@x @@Ft@@@L@@@C@Ip@`kG@P_@@xG@@kK@T`B@I@@p}C@|pB@KX@pBN@T`A@nN@@~A@| C@B!@@`C@@!@@`C@@T@@@C@@p@@@E@@PA@@d@@@}B@xz@@Fd@`CK@p_@@!M@PAE@l`C@IX@`kK@P_@@tK@`kC@TPA@KX@PBM@tpC@|w@@@F@hPB@NN@@}B@@",
	"PU@@Gx@x@!@M@MpA`C!@x@G@NPCPCx@!@!`C@TE@`K@@uB@@l@@@K@@pB@@l@@@K@@pB@@l@@@K@@uG@@Tm@P@N@I@GP@pA@@l@@PC@@M@@T@@PBD`WUATUm@P B@It@`@l@@@C@@d@@TG@@@K@@PC!@T@M`K@Vm@@@G@@|A@P!@@AG@dpAPB!@!U_Bjug@@!@@@G@@pA@Uu@pUE@D@@@A@@p A@@PC@@pA@@T@E@G`Cx@`WA@@UA@l@@pB@@MJ@peT@|@!@O@MpAPCt@!@l`K@Tm@pUUBVUMP@P@H@F@@p@@@E@@p@@@M@@pA@@n@@`C@@Tm@pBL@L@K@Gp@`_K@P}A@KtAT@x@I@L`CPB`UK@xU@`Kx@!@!@G@MpApCt@|@tZO@`pA@@N@@xB@UA@@",
	"Pe@@Kl@x@M@E`CpAp@!@L@G@CPAx@x@N@lpB@TI@`M@@uC@@x@@@N@@`C@@x@@@N@@`C@@x@@@M@@vW@@VG@`@E@EPC`Gt@`@G@@T@@`A@@J@@`@A@Wu@| O@Xm@`Al@t@G@HpB@@E@@UB@@pA`At@|@M@IpA@UK@@@C@@t@@`O@@TC@Pt@@JM@`PC@euB@@M@@PC@@}A@gF@p A@dJ@@B@@PUB@IpB@@|@X@M@OpAPBl@PUB@PU@@E!@x@G@E@@paB@!aK@OPCpAx@T@N@LpA@!I@t O@UU@P@H@D`B@@D@@@A@@T@@@K@@x@@@M@@`C@@VE@P@I@E`A`Cd@pWB@p B`A~@L@L@C@CPAX@PUB@xE@`CL@!@E@GPCpAt@xbO@xYC@@T@X@K@MX@@UA@@",
	"`}g@n@}xA@om@P C@x B@~o@` G@tyC@O|ItAX I`]@@zG@@tA@@]@@PG@@tA@@]@@PG@@tA@@]@@} B@t BPb A@@ @@PO@@tA@@O@@!@@xAD`I@C   t  Oto@`@M@@`K@@T@@XA@@XC@@pA@@|@@@G@@^@P_@@@@K@@|B@Pm@@IK@XpB@Al@|U_@UuG@@l@@@K@@pB@ O@X@@@B@@PUB@@tA@@xB@@!@@@K@@t@@PK@tI@@@XA@xB@`C@@l@@P[E@|BO@G`GpApAt@!@!PC@TE@| o@C`A`@d@@@C@@X@@@C@@X@@@K@@x@@@G@@xB@@TO@p@E@L`C@GT@P_A@P}@@C|@T@!@E@G`Cp@`WA@x]@`CT@!@l@G@GpCpAxB]@XUK@@|@@PC@@M@@e@@@",
	"`YA@N`ApBpAM@tpC@M|@PCO@tPC@MpBpBx@F@XV@`I@@vA@@l@@@K@@pB@@l@@@K@@pB@@l@@@G@@vK@@`V@`B|@D@MPApCdH!@^RA@@F@@X@@`BH@]UAt o@@YC@FpAPB!@TiA@de@@H!@@@M@@PCt@!@EPA@eE@@@E@@tA@P^@@FK@`pB@AlHTjgC@pR@@l@@@G@@vK@@P@@VK@PE@@H@@@jB@PPA@@p@@@N@EPCPCL@PZ@@@UE@!@KPApBn@@P[V@tBT@M@nPC@Kx@x@T@K@Tf@X@@@} Cpjj@H@B@@`@@@@@@P@@@F@@PA@@!@@@K@@Tf@P@L@F@I`KP@pgA@P B@IvBT@!@C@E`AP@`iB@PYB@GPBt@x@M@lPC@KpAtBPiN@@PCT@l@GPA@gI@@",
	"V@@pn@@lG@@{A@p^@@lG@@{A@p^@@lG@@{B@`E@@pB@@n@@@K@@p@@@l@@@K@@pB@@l@@@K@@pB@@n@@@f@@HE@@RC@Pu@@@M@@pB@@F@@P@@@B@@`@@@|O@@X@@`T@@tE@@XA@@D@@`A@@PA@Pu@@|M@@RA@@F@@@C@@p@@@N@@PC@@t@@`N@@hC@@uB@@N@@`C@@t@@Pe@@TA@@@@@`J@@HC@@rB@@!@@HG@@wA@Pl@@`A@@d@@Pm@@!C@@G@@pI@@!K@@wA@p]@@!G@@uB@@E@@|G@@B@@@@@@@@@@`@@@J@@p@@@N@@PC@@t@@@M@@@I@@dH@@EB@PK@@pB@@!@@@N@@DK@@qA@Pd@@hA@@V@@pn@@lG@@{A@p^@@lG@@xA@@!@@TG@@wB@@F@@@",
	"`_A@}CAp @A}O`r CP|_@H O@R Chp @AtOd@xW@@XK@u @@|o@@ K@x B@~o@` K@x B@~o@` K@x B@X}AP@tCB@ Q@t_D@ K@| @P K@~_@p C@ o@t WIP}G@A~G@` C@x_@`}A@Xg@@x @@~o@` KIx @V A@@`B@@n@@xK@@ B@|o@P K@q BD|opU W@p B@|o@TUA@B@@XUB@@~C@` CBt R@}_DP KAt `A}K@uG@@]E@|CJp @@}O@p gE|_@J O@R C`x @AtOX@xWBTU}O@P A@|O@P C@|_@P C@| @P G@| BP O@| A@XUAPC`B~APP GIx  @|  @u oDx KAP `BPK`UE@PuA@A~CD@ CAp R@|oD@ Kdy B@|O@` ADxG@Tm@@",
	"@~K@x C@@ CP@ @G`otBpC_@!po`Ct_n@| B@tA@@M@@|C@P @@`O@@xC@@~@@`O@@xC@@~@@`O@@h@@@tG@p G@@}C@@ @@PK@@|@@`C@@L@@p_I`  @TUC@xK@P C@@~@@`C@@~B@P B@@_@@PG@@|@@PA@@I@@@P@@@E@@X`@@cG@!tAPG]@|  @} K@@]@@PK@@D@@tu@@ K@df@`o@@t_@@xo@@pK@@|@@@G@@!@@P@@@@h@@PA@@E@@t@@@G}@tz_@_pOpOxAtGN@| B@|A@PIJ@} CP o@@PC@@L@@PA@@l@@PC@@!@@PK@@D@@@@t@`S_@^pCP_l@x A@p K@M}AtBm@_pAp K@xG@@@}@@V @xP_@OpOpOtCtO]@|rC@@M@@x@@PA@@I@@@",
	"xC@@o@@xBA@M`BPBP@d@D@I@A`BP@p@H@dP@@tI@@O@@tC@` @@dM@@bA@@P@@@D@@@B@@`@@@H@@@B@@X_@`_m@P@K@@p@@@A@@D@@P@@@J@@P@@@A@@pUJ@u_C`eD@@P@@@B@@XB@@uC@@PB@@P@@@J@@P@@dA@@G@@pB@@E@@pD@@FC@puG@DL@@@C@@P@@@H@@@B@Pgj@| K@M@@PC@@t@@@TE@@@B@@@A@@d@@`A@xE@@@C@@T@@@C@@l@@`A@@d@@@QG@P]G@dpA@EN@@ B@|UE@^yA@@D@@`@@@D@@@@@@D@@@B@@`@@@B@@`@@@`K@@mM@pAF@T@A@Mh@t}C@OPBpCX@|`J@]X@@}A@po@@mN@pQK@t_B@XD@@@A@@d@@@A@@D@@`B@@H@@@",
	"` K@} Gx  G}c s p ~O|_ K}W Q x  Gx  @X A@t A| OP  B@~o@@ C@p @@~o@` K`~ I|  Gv  BX IP  C}  RG o@p C@~O@p B@ oM|  S   @@@At Ap  CHt @@}K@t IP  K`v A@|_@P C  o` _@@@~@@xO@` C@| @pyO@M|Cxb B   P  O@` B@xO@| OP  C| _`_@@t G@} o`} O@p C@| P  Cx K@`o@@|G@p @@~KBp  G|  K S q pot_|Ct o@t BtUUB  _p  C|B}@@PG@@|B@PO@@~A@pO@@~C@`_@@t Ip  G}G~S W_x  Ct  R   |C}O}A C  O@}_@P K@  Gto}K C R rox  Cx  @@}K@p_@@ A@PG@@",
	"@~_B|  q u ~Kp_ @t O@} CP_ A~s   p  C`]I@`A@P_@P G@t A@P_@@tG@@}A@P_@@tG@@}A@P_@@_B@p K@T K@@ C@P @@tG@@ @@|K@p_e@  KTU}B}I@P O@`}G@@ B@vG@p A@` C@P @h}G@ _@p_@@@@|B@P_@@}G@x A@ _@|yGPO~A}  [   @@}I@P_@} Bp o@|UA`_B@x K@~ C@P B@to@v Ap K@tI@@@d@@pO@@ C@tG@` g@t _@ ropOtG|K B~ G@~o@| _@  OPU B@pO@@~A@pO@@~C@po@@~C@P_@@@A@@v Ax  A b poxGx_ @t G`_tO|C|C B P }G` o@P A@  AtG @ Pop_|Kx  @P G@` @@}K@Po@@pB@@",
	"P_@@}^@xEM@m@EpGaA|z|@o@FPKTAxCL@tVA@tG@`M@@ C@@}@@PE@@TA@@V@@`G@@pA@@!@@@G@@pB@@UK@dPC@idB`oe@@TA@PG@@~@@pA@@NXAP  @XuO@|_A@_]@@`C@@N@@pG@@PG@@pA`@|@t`G@| @@XH@@E@@pJ@@nC@PCB@tx@@WM@x o@}w@@`E@@PB@@D@@ G@PCM@t@@@N@@`wA@P~C@@tBH@m@KPKPE_@` B@@N@@xG@`_@@|B@PK@@!~A@{pAplv@dFM@NpA@~G@tUB@  C`Bt@@@G@!t@@BO@@XA@@g@@XC@@ @@`E@@^K@pCC@^xB@GM@PwA@TtAPA~@!@m@OvC` _@` A@PEA`] @x@M@N`CPCt@P[o@@[K@@tB@@m@@PG@@T@@",
	"P K@EPEX@BAAP@q@DPD`@DCD@q@APXD@ITAT@xWB`M@@NC@@q@@PL@@DC@@q@@PL@@DC@@q@@PL@@ O@@~G@XPE@A`AP@hB@@f@@dB@@E@@!@@PBJ@B`@| O@x_@`Au@D@j@B`B@@U@@xA@@dA@@hBH`f@IVA@}G@@PG@@NA@Pa@@QH@dDA`AQ@!UT@BDA@@Q@@PD@P G@|o@@Q@@hA@@Q@@`]B@@`B@@P@@@D@B@ApBd@P B@@}K@|A@PD@@e@@P!U@DKP@S@DpD@AdIP@dIE@t_@t _@BDJ@@Q@@hD@@QB@PL@@bA@PD@@DC@PV@@|K@@t_@PDX@IAD`RAAPRE@xAIPBAAL@AAA`PPBDA` g@x_@`ky@L@Q@CPDP@HIh@a@TUD@@DA@`f@@TB` A@@",
	"@E@@|K@PqA@L|@`AO@dpC@C|@p@K@Lt@@iC@@G@@@x@@PG@@yB@@I@@p@@@F@@PB@@L@@`C@@x@@@E@@@@@XA@tm@pQA@@E@@d@@P@@@C@@l@@x_Bm_ yo@XE@}m@T}B@PA@@ G@tzC@@l@@PA@PA@`I@@^@@pA@@@@p@@@G@@|B@pM@`aC@mTp~  K@pB@@L@@PC@@D@@` G@tU@@G@@po@@VO@@p@@@A@@D@@X@@PK@@!@@@@E@@x@@@E@@pB@@L@@PB@@LH@`_O@lPA@[I@PG@@pU]@U C@@N@@PB@@F@@P@@@J@@P@@@L@@`C@@h@@@PVE@ uCtCL@|X@@}A@@O@@TG@PrC@Fd@PwB@PA@@@O@@|_@PzC@F]@p]C@dd@@@A@@D@@@C@@pA@@n@@@",
	"xm@@CL@T@G@GPCpAt@!@M@GPCpAt@t@G@lx@@^K@@L@@tC@Px@@@N@@`C@@x@@@N@@`C@@x@@@n@@v_@`]G@T`K@@pA@@l@@PC@@N@@p@@@K@@l@@`kV@| G@V]@PBl@@@G@@pB@@K@@}B@@tB@@!@@@G@GxBPWK@@PA@@^@@PE@@YA@XT@@CE@TPQ@W}E@@E@@PC@@|B@jN@x C@F@@`A@@X@@@~o@@@M@@@K@@pBpBN@tU@@@~@@t@@PC@@N@@PcJ@|UG@GPCpAx@!@N@NPA@^G@t O@IPA`@L@@`A@@l@@@C@@T@@@C@@T@@@C@@t@@@Vo@x@N@E@KPCpBpaG@xuB`Cx@T@!@M@K`Ct@`WA@x]@`CT@T@N@G@CPCxBxWo@`RC@@t@@`K@@^@@!B@@",
	"P B@_}@xB!@M@GPCpC|@t@M@EPCpAxBl@|uC@|G@@M@@~C@py@@@N@@`C@@x@@@L@@@C@@p@@h]B@  B@}K@tuK@BpA@@!@@`K@@|@@PC@@M@@t@@Pgj@t O@t_@PWo@H@G@@xB@VG@P A@@xA@@t@@@O@gvB` K@@pK@@}B@xn@@EK@xpB@Gl@t@K@  GPU]B@@C@@pB` o@xiB@N@@`C@@x B@T}A@@|@@@M@@PCpio@x B@P A@]V@pB@@M@@PwG@|WO@O`CPCpBt@N@|vA@~G@| O@jZC@@!@@`K@@t@@@K@@t@@@G@@t@@@G@@x@@@~G@xUG@MPCPCT@PWC@po@`G^@!@N@G@CPg}@P A@x_@Pgm@|@O@G`CpAx@tWO@tWC@@t@@@G@e}@` A@@",
	"Pm@@Cl@X@G@EPCpAt@!@M@GPCPAT@T@I@lp@@^A@@T@@VK@`pA@@!@@@G@@pB@@l@@@G@@pA@@!@@Xo@@}K@XxC@ApA`@!@@@K@@x@@@C@@D@@P@@@iJ@| O@tG@PBG@D`C@@T@@`A@@uC@@pA@@T@@@E@AX@`WA@@PA@@^@@PE@@ZA@PT@@AE@`PA@  I@@G@@PA@@~B@ o@P@@@D@@@A@@P A@HxB@@|@@@E@BpBP@E@xo@@@T@@X@@`C@@L@@`SI@tRG@GPCpAt@T@E@LpB@^I@| O@CXAP@D@H`A@@L@@`B@@L@@PB@@N@@pA@@N@@@VK@x@K@EpBPCL@pW@@x_@`A]@L@E@C`APAd@PU@@Xm@`Cl@T@E@KPCpAt@xaO@xqA@@L@@PB@@I@@E@@@",
	"po@@Kl@T@N@I@Cp@p@L@D@C@CPBp@T@L@lpB@|K@tC@@x@@@N@@`C@@p@@@N@@`C@@x@@@L@@`C@@x@@@~G@x@K@K@C`@p@@@F@@p@@@K@@!@@pA@@E@@t O@xo@`CN@h@K@@p@@PK@@XC@@`A@@p@L@F@Ep@@}K@@@J@@p@@@M@@xC@@{@@dL@`AC@lzB`U]B@@C@@p@@|_@@C@@X@@@eB@PUC@@PA@@p@@@L@A`CPAn@P B@@D@@PA@@N@@pB@@m@@puA@EpBp@T@L@I@Nx@@~A@t G@@p@@@E@@p@@@E@@p@@@I@@p@@@E@@p@@@F@@@tG@pBK@N`A@CT@P[C@tu@`Ax@l@L@I@C`CT@` A@xo@`CN@l@I@CPAPAl@puC@`M@@PA@@N@@p@@@F@@@",
	"P_@@]~@x@!@E@EpAPC!@t@G@MPApAx@n@|uC@tG@`K@@~B@po@@@K@@p@@@N@@`C@@x@@@N@@XG@@ K@@~K@twK@KpA@@l@@pC@`O@@]@@tB@@G@@pUE@|_G@to@`gM@@@K@@xB@tO@@}A@@xB@@!@d@G@]~@@}K@@PK@@|B@pm@@MK@xrB@Gl@| _@VuK@@l@@@K@@pBPUm@tUA@E@@P G@|[K@OPC@@x@@@M@BpApkO@P_@@@N@@xB@`K@@!@@`WI@twG@GPCpAx@t@M@^vA@~K@tWU@V O@@t@@`K@@|@@`K@@t@@@K@@t@@@G@@p@@@~K@xYC@EpBPCn@p A@| @PC!@l@M@KPCPg]@P B@x_@`g]@T@M@G@CPCx@xWO@xwA@@l@@xA@XG@@g@@@",
	"Po@@CL@d@F@A@Cp@p@L@L@C@CP@p@d@F@DP@@TC@`M@@eC@@P@@@D@@@A@@P@@@L@@@A@@P@@@D@@]WA@vG@P@F@A@C@@P@@@F@@X@@`A@@F@@X@@`A`@|UM@x_@`BT@@@L@@@A@`F@@XA@@`C@@P@@@L@APA@]K@@pC@@Y@@XD@@AA@hP@@CD@d@C@WuA@@F@@@A@@}A` o@X@@@F@@`A@@xUA@H`C@@P@@@D@@@CpBT@PwB@@}A@d@@P@@@J@@PXI@!AI@O@APBp@X@D@D`A@TE@| O@A@A@@d@@@A@@P@@@J@@PB@@D@@`B@@D@@@A@@~K@P@I@I@APBP@P@A@XU@`AT@D@L@A@C`AX@`UB@xG@`AD@D@F@C@CP@x@x`M@XGC@@P@@@I@@h@PW@@@",
	"P @@_}@xB^@O@OpCpK|@tBO@opCpCtA^@|uK@tO@@xB@`o@` K@ttB@Bm@@PK@@tB@@m@@PK@T}WB  o@to@pWo@m`OPApC@@~@@pG@`_@@}A@~A@p_UA|  @P A@_}AxB|@@@O@`}A@|O@@`O@@PKtB|B|uO@t_@@`O@@|C@P @@nO@pqC@M|@xao@  _`Z}I@@O@@pC@  ApUe@L@@`CJ@x}o@}RO@BpK@@tAo@o`_}A`}K@P B@_}AxAT@O@@p{_@|W @_@OpCPKxA|@|wG@to@t  @UUO@@x@@@G@@t@@`G@@t@@@O@@xC@@]@@PG@@t_@pW}@^@m`GPCp_m@p K@o}K|@tAo@]`_}K` G@P B@_}BtB|@M@mPKpGxW Ax_]@@PK`B~@|uK@tO@@",
	"`}G@^@OpA`G]@pSK@||B@Om@pSG@|pC`GtA~@x A@T@@}G@@xA@@^@@`G@@xA@@^@@`G@@xA@@]@@} A@t BpAtB]@|PG@OP@xC@@m@@tB@tB@xB@P_Uet  GX]@@C!@x@M@HpA@@M@@~A@@PC@@xBT@n@MpC@UG@@@K@@|B@Pm@@IK@XpB@Al@ljg@UuG@@l@@@K@@pB@} @PbB@D@@@AB@p C@HpC@@x@@@N@GPCPA!@PuA@@V@@T@@PC@@L@@P{G@|bG@GPCpCxBt@M@lpA@^E@| O@KhAP@D@@`A@@L@@`A@@D@@`A@@L@@`A@@L@@@TE@pBM@N`C`Kx@PgI@p @`C~@!@!@G@GPCx@PWA@x]@`C!@|@M@G`KpCxBtBM@tWC@@!@@`C@@M@@f@@@",
	"to@P O@t{K@ ~Bpoo@|{K@ ~Bpoo@t{K@} @@}K@@^@@~G@p A@`_@@pG@@|A@@_@@pG@@|A@@_@@pG@@}A@t C@o~@p[O@@|C@Po@@|C@Po@@~A@p_E@| C@|o@P O@|yC@j~@@tG@@}C@j}@pgo@|yC@} @@}K@@ C@p @@~O@P C@|}@`WO@ttC@  Ap  @@tC@@}@P O@tWA@]@@P G@twK@U|A@@_@|sK@ |BP_O@P B@to@P_O@tsK@ H@p O@|{K@ |BpOo@tsK@}}@@}K@| B@UO@@xC@@}@@pO@@|A@@o@@xC@@}@@pO@@|A@@}K@t C@}~@PoO@x A@~_@poo@|{K@ ~BP O@P B@to@P_O@tsK@ |BpOo@twK@~ B@Ho@tqK@}}@@}K@@",
	"Po@@On@x@M@M`CPCpB|@l@E@KPCx@x@M@|xB@tK@@V@@]G@@pB@@!@@@G@@pA@@!@@@G@@pA@@!@@  K` A@TxC@@x@@@N@@pC@@M@@t@@`C@@l@@pC@@| C@~G@`RG@@pA@@l@@uA@`}@@@|@@@M@@PC@J]@P A@@PC@@|B@pm@@EC@xpB@Kl@tjK@  G@@l@@@K@@p@P K@T@@@E@@PA@@to@@`O@@@G@@pA@@!@`RC@tO@@P @@oD@x@@@G@@puK@|QK@OpApAt@t@G@!t@@~K@| G@UuA@@N@@pB@@E@@p@@@M@@pB@@M@@pA@@n@@@~K@xRC@Mp@`KN@Pw@@to@PCO@l@G@GpAPKM@P B@xo@`KM@T@G@GPCPC|@xQO@xWC@@T@@@K@H~@@ A@@",
	"po@@Gn@x@M@E`CpApB!@l@G@KPAx@x@M@!xB@|K@tK@@xB@@l@@@K@@pB@@l@@@K@@pB@@l@@@K@@pB@` K@dXC@@pB@@l@@PC@@n@@xB@`K@@l@@pC@@| K@}G@`bG@@PC@@!@@ZA@P]@@@t@@@N@@PC@I^@p A@@`G@@|A@P]@@NG@ppA@G!@tjg@  O@@!@@@G@@pAp G@!@@@G@@pA@@|G@@ZO@@@G@@pC@@|@`PK@|o@@P A@mh@x@@@M@@puG@|BG@O`CPCp@t@N@!xA@|G@| O@UUC@@!@@`C@@l@@PA@@N@@pA@@N@@pC@@!@@@~G@paG@NPA@Kl@PwA@t_@`C]@!@M@G`CPG^@P A@x_@@Gn@t@M@E`CPCxBxBo@xgC@@x@@@G@Ht@@ A@@",
	"xo@@GM@t@G@GPApAt@!@M@KPCpAT@t@G@!t@@~K@@L@@PC@p @@HN@@`C@@x@@@N@@`C@@x@@@N@@`C@@~G@paG@M`C@@x@@@M@@xB@PK@@m@@t@@PK@@| o@to@`KM@h@K@@p@@`G@@~A@@pA@@t@l@M@mtB@}K@@`C@@|@@PO@@nC@px@@EL@x@C@  G`jm@@@C@@p@@ _@x@@@N@@`cB@t C@FpA@@x@@@N@GPCPKm@P B@x_@@Gn@t@I@E@@puK@|QK@GPApAt@t@E@!xB@~K@| O@@PC@@!@@@C@@t@@@K@@t@@@G@@x@@@M@@pB@@~K@xQC@MpB`Cl@PwA@to@PKn@!@M@GPCPKn@P A@xo@`KM@!@G@GPApAt@xRO@xWC@@!@h@K@nt@@}A@@",
	"Pm@@Cl@X@G@EPApBt@l@M@KPCPAT@T@I@Lp@@^A@@F@@UC@@t@@@M@@PC@@t@@@M@@PC@@t@@@M@@xK@@}K@XxC@ApB@@l@@@C@@T@@`A@@D@@P@@@kJ@| O@tO@`AM@H`C@@X@@@A@@uC@@pA@@T@H@G@AX@`WA@@`C@@|@@PM@@ZC@Pt@@AM@`PC@  I@@M@@PC@@~B@ _@P`B@D@@@A@@p C@HpA@@t@@@N@@PBP@D@xe@@@T@@X@@`C@@L@@`SI@tQK@GPCpAt@T@E@LpB@^I@| o@C`AP@D@@@A@@D@@`A@@L@@PB@@N@@pA@@M@@@VK@p@K@FpB`KL@pW@@x_@`A]@d@E@CPAPAl@PW@@Xm@`CL@!@G@KPApA|@xRG@xyA@@N@@PB@@I@@E@@@",
	"Pm@@Kn@x@G@EPCpAt@!@M@GPCpCT@t@G@lp@@^A@PC@@u@@@L@@@C@@x@@@L@@@C@@p@@@L@@`C@@~K@@uK@TPC@JxB@@l@@`C@@!@@`C@@l@@pB@@gJ@| O@]G@p@G@DpC@@l@@XA@@}A@@tB@@!@D@K@Ct@PUA@@@A@@|@@PO@@TC@pt@@IM@PPC@  C@@M@@PC@@}A` O@X`@@J@@`UB@x A@@tB@@!@@@G@@pB@@E@TU@@@t@@t@@`C@@!@@`WI@tRG@OpCpAt@t@M@lpA@^I@| O@K`A`@d@@@C@@T@@@C@@T@@@K@@t@@@K@@t@@@^K@xBK@MpB`KL@pWB@po@@Km@t@O@GpCPC!@PWB@xm@`Cn@!@G@GPCpCt@xaO@XuA@@M@@pB@@G@@e@@@",
	"xo@`KM@t@K@GpApAT@!@E@KPApA!@T@K@nt@@~C@@E@@vA@`]@@@G@@pA@@!@@@G@@pA@@!@@@G@@ _@` K@TRC@@pB@@l@@`C@@!@@pC@@M@@t@@PK@@| O@~o@PaM@@@K@@x@@tC@@vA@@pB@@!@@@K@K~@P A@@PK@@~B@xn@@KK@!pBpAl@| _@jzA@@l@@@K@@pBP o@t@@@M@@PC@@t_@@j}@@@l@@@K@@xBpaO@t_@@P @@mH@x@@@M@@p}K@|RK@KPCpAt@t@G@^t@@~K@| O@@PC@@|@@`C@@!@@`C@@!@@`C@@!@@`C@@!@@@~G@paG@MPC`KT@PgC@t_@`C~@!@N@M`C`G^@` A@xo@`Gm@t@G@GPCPCx@xaO@xWC@@T@@@K@H^@@ A@@",
	"Pm@@El@pBM@M`KPCpB|@l@M`KPCx@p@M@TpB@TI@PC@@v@@@M@@`C@@x@@@N@@`C@@x@@@N@@PC@@~B@@~K@pzK@ApA@@!@@@C@@X@@@A@@D@@P@@@iZ@t G@tG@`bG@@PA@@D@@`A@@}A@@t@@@l@@@C@BX@PWB@@`C@@|@@PM@@iC@Px@@AN@D`C@  K@@N@@`C@@x@@to@@iB@D@@@_@@`}B@@|@@@l@@@I@@P@`@J@tg@@@TB@t@@`C@@l@@P[G@!@G@GPCpAx@t@M@lpB@!I@p O@eZA`@L@@@C@@T@@@C@@p@@@I@@p@@@L@@PB@@UA@T`C@Kp@PCF@pW@@pG@@QG@l`C@KpBPAL@PW@@XM@`CN@!@G@KPCpAt@t@M@tuA@@N@@pB@@E@`E@@@",
	"P_@@o^@x@M@M`CpAp@!@L@G`CPCx@t@M@!xB@~K@@F@@tA@p_@@DG@@pA@@!@@@G@@pA@@!@@@G@@pA@@}C@tzC@@xB@@N@@pC@@n@@pA@@M@@xB@@O@@t O@~G@`RK@@pA@@!@@XA@@}@@@|@@@M@@PC@G^@P A@@@F@@pA@@_@@!G@PsA@M!@xiG@  G@@!@@@G@@pAP G@t@@@E@@PWB@tuA@Bt@@@n@@`K@@t@PiG@x_@@@E@@|B@PC@@n@@PwA@|yC@GpBpA!@T@G@nt@@~K@| O@UuA@@n@@pA@@N@@pA@@n@@PC@@!@@PC@@|@@@~K@xQC@MpB`KN@P B@t]@PK]@!@G@GpCPGm@P B@xo@`GM@t@G@EPAPC|@xYO@XwB@@M@@xA@`G@@!@@@",
	"x_@@G^@t@N@G@CpApB!@l@G@KpAp@t@N@!xA@~G@@N@@vC@P @@@N@@`C@@x@@@M@@`C@@x@@@M@@  B` G@TRK@@PC@@t@@@G@@t@@PC@@m@@t@@pK@@| o@~_@PI^@@@G@@pB@XK@@vC@@PC@@t@@@M@GtBP K@@@O@@tC@Pw@@NN@xbC@Gx@tjm@  _@@x@@@N@@`C`  @x@@@N@@`C@@x B@HvA@@t@@@N@@PCpAm@t B@` A@]@@pB@@M@@pwG@|bO@G@GpApAt@l@!pC@|G@|  @@@O@@pB@@M@@pB@@G@@xB@@G@@x@@@G@@t@@@~G@xaO@M`CPCx@pgK@T}@PCt@!@l@G@KPG~@` A@x_@@G~@t@l@G@GPCpAxI]@x_G@@pB@@M@HtB@}A@@"
};

const int white_regions50[]  ={1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,99,99,99,99,99,99,99,99,99,99,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,1,1,0,0,0,1,0,1,0,2,1,99,99,99,99,99,99,99,99,99,99,1,1,3,0,0,0,0,1,2,1,2,1,1,2,2,1,2,1,3,2,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1};
const int white_regions20[]={1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,1,1,1,0,3,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,2,2,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,1,1,0,0,0,2,1,2,1,0,0,1,2,2,1,2,1,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,1,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1,1,0,0,0,1,0,1,0,2,1};

const int left_regions50[]   ={0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,2,2,2,3,2,0,2,2,2,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,2,0,1,0,1,2,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,99,99,99,99,99,99,99,99,99,99,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,2,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,2,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,2,1,2,0,2,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1};
const int left_regions20[] ={0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,1,0,1,2,0,1,0,1,1,1,1,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,1,2,0,2,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,1,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1,0,0,1,2,0,1,0,1,1,1,0,1,1,2,0,1,0,1,1,1};

using namespace std;

vector<string> s, s1, s2, s3; //s - all numbers, s1 - first number, s2 - second number, s3 - third number in ascii graphics in original resolution
vector<string> F; //fonts patterns
bool filled1=false, filled2=false, filled3=false; //filled1 = true, if corresponding number was written in its array s1
char ch1[N][N], ch2[N][N], ch3[N][N]; //all numbers in ascii graphic, resolution N*N
bool trash=false;

//DECOMPRESS fonts patterns---------------------------------------------------------------------------------------------------------------------
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

void set_label(int i, int j) {
	int m1=up(i,j);
	if(m1) {
		array_of_labels[i][j]=m1;
		int m2=left(i,j);
		if ( m2 && (m2!=m1) )
			add_equiv(m1, m2);
		return;
	}
	m1=left(i,j);
	if (m1) { 
		array_of_labels[i][j]=m1;
		return;
	}
	m1=new_label(i,j);
	array_of_labels[i][j]=m1;
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

void find_connected_regions() { 

	init_labels(s);
	//find connected regions----------------------------------
	for (int j=0; j<s[0].size(); j++) {
		for(int i=0; i<s.size(); i++) {
			if (s[i][j]!='.')
				set_label(i,j);
		}
	}

	resolve_equiv();
	//--------------------------------------------------------

	if (actual_labels.size()==1) return;

	vector< vector<string> > crs; //cr - connected regions

	vector<string> cr=s2;
	for (set<int>::iterator iter=actual_labels.begin(); iter!=actual_labels.end(); iter++) {
		copy_labeled_items(cr, *iter);
		crs.push_back(cr);
		cr=s2;
	}

	//now each connected region is an item of vector crs;

	int hmin=s.size(), hmax=0, h;
	for (int i=0; i<crs.size(); i++) {
		trim(crs[i]);
		h=crs[i].size();
		if (h>=hmax) hmax=h;
		if (h<=hmin) hmin=h;
	}

	if ((3*hmin)<hmax) trash=true;

	if (trash) {
		for (int i=0; i<crs.size(); i++) {
			if (crs[i].size()<(hmax/3)) {
				crs.erase(crs.begin()+i);
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
			int h=crs[0].size(), w=crs[0][0].size();
			bool border=true;
			for (int i=h/4; i<(3*h/4); i++) {
				if ((crs[0][i][0]=='.')||(crs[0][i][w-1]=='.')) {
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
			s3=crs[1], s=crs[0];
			filled3=true;
			if (trash) find_vertical_lines();
			return;
		}
		else {
			s1=crs[0], s=crs[1];
			filled1=true;
			if (trash) find_vertical_lines();
			return;
		}	
	}
}

//------------------------------------------------------------------------------------
void lines2_fill (vector<string> &sn, int a, int b) {
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

void find_vertical_lines_with_dark_gray_pixel() {
	int w=s[0].size(), h=s.size(), count;

	int j1;
	for (j1=0; j1<w; j1++) {
		count =0;
		for (int i=0; i<h; i++) {
			if (s[i][j1]!='.')	count++;
			if (count>1) break;
		}
		if (count>1) break;
	}

	int j2;
	for (j2=w-1; j2>0; j2--) {
		count =0;
		for (int i=0; i<h; i++) {
			if (s[i][j2]!='.')	count++;
			if (count>1) break;
		}
		if (count>1) break;
	}

	vector<int> lines2;
	for (int j=j1+1; j<j2+1; j++) {
		count=0;
		for (int i=0; i<h; i++) {
			if ((s[i][j-1]=='.')||(s[i][j]=='.')) continue;
			if ((s[i][j-1]=='@')||(s[i][j]=='@')) {
				count+=5;
				break;
			}
			count++;
		}
		if (count==1) lines2.push_back(j);
	}

	if (!lines2.empty())
		for (int i=0; i<lines2.size()-1; i++) 
			if (lines2[i+1]-lines2[i]==1) {
				lines2.erase(lines2.begin()+i);
				i--;
			}

			if (lines2.size()>2) return;
			if (lines2.size()==0) return;

			if (lines2.size()==2) {
				if ((!filled1)&&(!filled3)) {
					lines2_fill(s1,0,lines2[0]); 
					lines2_fill(s2,lines2[0],lines2[1]);
					lines2_fill(s3, lines2[1], s.size());
				}
				return;
			}
			//if lines2.size==1

			if (!filled3) {
				lines2_fill(s1,0,lines2[0]);
				lines2_fill(s2,lines2[0],s[0].size());
			}
			else {
				lines2_fill(s2,0,lines2[0]);
				lines2_fill(s3,lines2[0],s[0].size());
			}
}
//DIVIDE---------------------------------------------------------------------------------

bool divide() {
	init_s123();
	find_vertical_lines();
	if (filled2) return true;

	find_connected_regions();
	if (filled2) return true;

	vector<string> s_nontrimmed=s;
	trim(s,false,true);
	if (s.size()==0) {
		if(filled1||filled3) return true;
		return false;
	}

	reinit_s123();
	find_vertical_lines(true);
	if (filled2) return true;

	s=s_nontrimmed;
	reinit_s123();
	find_vertical_lines_with_dark_gray_pixel();
	if (filled2) return true;

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
						sum+=(double)CharToInt(L[up-1][r])*dup*dl;
					if(ddown*dl!=0.0) 
						sum+=(double)CharToInt(L[down][l-1])*dup*dl;
					if(ddown*dr!=0.0) 
						sum+=(double)CharToInt(L[down][r])*dup*dl;

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
void fill_black(vector<string> &s) {
	int w=s[0].size(), h=s.size(), j;
	for (int i=0; i<h; i++) {
		j=0;
		while ((s[i][j]=='.')&&(j!=w-1)) j++;
		if (j!=w-1) 
			for (int k=j; k<w; k++)
				s[i][k]='@';
	}

	int i;
	for (int j=0; j<w; j++) {
		i=0; 
		while ((s[i][j]=='.')&&(i!=h-1)) i++;
		if (i!=h-1) 
			for (int k=0; k<i; k++)
				s[k][j]='@';

		i=h-1;
		if (s[i][j]=='.') {
			while (s[i][j]=='.') i--;
			for (int k=i+1; k<h; k++) 
				s[k][j]='@';
		}
	}
}

int left_regions_count(vector<string> s) {
	fill_black(s);
	int w=s[0].size(), h=s.size(), maxcount=0, i, count;
	for (int j=0; j<w; j++) {
		i=0, count=0;
		while ((s[i][j]!='.')&&(i!=h-1)) i++;
		while (i!=h-1) {
			count++;
			while (s[i][j]=='.') i++;
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

void move_right(char chn[N][N], char chn_shifted[N][N]) {
	vector<string> sq;
	if(chn==ch1) sq=s1;
	else if(chn==ch2) sq=s2;
	else if(chn==ch3) sq=s3;
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
	resize(sq,chn_shifted,false);
}

inline void copych (char ch1[N][N], char ch2[N][N]) { //copy content of ch1 to ch2
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			ch2[i][j]=ch1[i][j];
}

void before_compare (vector<string>&sn, int &white, int &left) {
	trim (sn,false,false);
	left=left_regions_count(sn);
	white=count_white_connected_regions(sn);
	trim(sn,true);
}

void compare_with_patterns(char chn[N][N]) {

	int white, left;
	if(chn==ch1) before_compare(s1,white,left);
	else if(chn==ch2) before_compare(s2,white,left);
	else if (chn==ch3) before_compare(s3,white,left);

	int min=1000000, minnum=10, minfont=100, t;

	int beginfont=0, endfont=NumberOfFonts-1;
	if(trash) beginfont=12, endfont=12;

	int white_min, white_max, left_min, left_max; 
	bool flag=false;
	for (int font=beginfont; font<=endfont; font++){
		for (int n=0; n<10; n++) {
			white_min=white_regions20[font*10+n];
			white_max=white_regions50[font*10+n];
			if (white_min>white_max) swap(white_min, white_max);

			left_min=left_regions20[font*10+n];
			left_max=left_regions50[font*10+n];
			if (left_min>left_max) swap(left_min, left_max);

			white_max=99;
			if ((white>=white_min)&&(white<=white_max)&&(left>=left_min)&&(left<=left_max)) {
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

	char chn_trimmedhard[N][N], chn_shifted[N][N];
	if (min>0) {
		move_right(chn, chn_shifted);

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
				if ((white>=white_min)&&(white<=white_max)&&(left>=left_min)&&(left<=left_max)) {

					get_letter_to_ch(font,n);
					t=compare(chn_trimmedhard,ch);
					t2=compare(chn_shifted,ch);
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
		cout<<"Error: couldn't separate digits"<<endl;
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

	for (int i=0; i<result.size();i++)
		cout<<result[i];

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
