#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prime checking function */
int isPrime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

/* Global variables */
int ALPHA = 0;
int BETA = 0;
int BSTI = 0;
int BSTV = 0;
int BV = 0;
int DEP = 0;
int DX = 0;
int DY = 0;
int EVAL = 0;
int FX = 0;
int FY = 0;
int I = 0;
int I1 = 0;
int I2 = 0;
int MAXDEP = 0;
int MAXV = 0;
int MBASE = 0;
int MCNT = 0;
int MI = 0;
int NODES = 0;
int NV = 0;
int P = 0;
int P1 = 0;
int PV = 0;
int QV = 0;
int RV = 0;
int STM = 0;
int T = 0;
int TX = 0;
int TY = 0;
int VAL = 0;
int X = 0;
int X1 = 0;
int Y = 0;
int Y1 = 0;
int B[72];
int BL[30];
int M[2000];
int TB[72];
int V[400];

int main() {
    memset(B, 0, sizeof(B));
    memset(BL, 0, sizeof(BL));
    memset(M, 0, sizeof(M));
    memset(TB, 0, sizeof(TB));
    memset(V, 0, sizeof(V));

L10:
    /* ADZCHESS - Chess Engine in BASIC */
L20:
    /* Inspired by baeagn . c */
L30:
    /* Simplified alpha - beta search */
L40:
    /* */
L50:
    /* Board : 8 x8 grid stored linearly */
L60:
    /* Pieces : WP = 1 WN = 2 WB = 3 WR = 4 WQ = 5 WK = 6 */
L70:
    /* BP = - 1 BN = - 2 BB = - 3 BR = - 4 BQ = - 5 BK = - 6 */
L80:
    /* */
L90:
L100:
L110:
L120:
L130:
L140:
    /* */
L150:
    MAXDEP = 4;
L160:
    PV = 100;
L170:
    NV = 315;
L180:
    BV = 325;
L190:
    RV = 500;
L200:
    QV = 980;
L210:
    MAXV = 20000;
L220:
    /* */
L230:
    printf("%s", "ADZCHESS - Loading position");
    printf("\n");
L240:
    /* Load board from start . brd */
L250:
    Y = 7;
L260:
    if (Y < 0) goto L350;
L270:
    X = 0;
L280:
    if (X > 7) goto L330;
L290:
    printf("? ");
    scanf("%d", &P);
L300:
    B[Y * 8 + X] = P;
L310:
    X = X + 1;
L320:
    goto L280;
L330:
    Y = Y - 1;
L340:
    goto L260;
L350:
    printf("? ");
    scanf("%d", &STM);
L360:
    B[64] = 1;
L370:
    B[65] = 1;
L380:
    B[66] = 0;
L390:
    B[67] = 0;
L400:
    B[68] = STM;
L410:
    /* */
L420:
    printf("%s", "Board loaded");
    printf("\n");
L430:
    /* */
L440:
    /* Transpose if black to move */
L450:
    if (STM == 0) goto L630;
L460:
    Y = 0;
L470:
    if (Y > 3) goto L570;
L480:
    X = 0;
L490:
    if (X > 7) goto L550;
L500:
    I1 = Y * 8 + X;
L510:
    I2 = ( 7 - Y ) * 8 + X;
L520:
    T = B[I1];
L530:
    B[I1] = B[I2];
L540:
    B[I2] = T;
L550:
    X = X + 1;
L560:
    goto L490;
L570:
    Y = Y + 1;
L580:
    goto L470;
L590:
    I = 0;
L600:
    if (I > 63) goto L630;
L610:
    B[I] = 0 - B[I];
L620:
    I = I + 1;
L630:
    goto L600;
L640:
    /* */
L650:
    /* Main search loop */
L660:
    DEP = 1;
L670:
    if (DEP > MAXDEP) goto L9990;
L680:
    printf("%s", "Depth: ");
    printf("%d", DEP);
    printf("\n");
L690:
    NODES = 0;
L700:
    ALPHA = 0 - 20000;
L710:
    BETA = 20000;
L720:
    /* */
L730:
    /* Root search - generate and evaluate moves */
L740:
    MCNT = 0;
L750:
    Y = 7;
L760:
    if (Y < 0) goto L850;
L770:
    X = 0;
L780:
    if (X > 7) goto L830;
L790:
    P = B[Y * 8 + X];
L800:
    if (P > 0) goto L10000;
L810:
    /* Continue after move gen */
L820:
    X = X + 1;
L830:
    goto L780;
L840:
    Y = Y - 1;
L850:
    goto L760;
L860:
    /* */
L870:
    printf("%s", "Generated ");
    printf("%d", MCNT);
    printf("%s", " moves");
    printf("\n");
L880:
    if (MCNT == 0) goto L9990;
L890:
    /* */
L900:
    /* Evaluate each move at depth DEP - 1 */
L910:
    BSTV = 0 - MAXV;
L920:
    BSTI = 0;
L930:
    MI = 0;
L940:
    if (MI >= MCNT) goto L1100;
L950:
    /* Make move MI */
L960:
    I = 0;
L970:
    if (I > 71) goto L1010;
L980:
    TB[I] = B[I];
L990:
    I = I + 1;
L1000:
    goto L970;
L1010:
    MBASE = MI * 5;
L1020:
    FY = M[MBASE];
L1030:
    FX = M[MBASE + 1];
L1040:
    TY = M[MBASE + 2];
L1050:
    TX = M[MBASE + 3];
L1060:
    B[TY * 8 + TX] = B[FY * 8 + FX];
L1070:
    B[FY * 8 + FX] = 0;
L1080:
    /* Transpose */
L1090:
    goto L20000;
L1100:
    /* After transpose , evaluate */
L1110:
    goto L30000;
L1120:
    /* EVAL returned */
L1130:
    VAL = 0 - EVAL;
L1140:
    /* Unmake move */
L1150:
    I = 0;
L1160:
    if (I > 71) goto L1200;
L1170:
    B[I] = TB[I];
L1180:
    I = I + 1;
L1190:
    goto L1160;
L1200:
    /* Check if best */
L1210:
    if (VAL <= BSTV) goto L1260;
L1220:
    BSTV = VAL;
L1230:
    BSTI = MI;
L1240:
    BL[0] = FY;
L1250:
    BL[1] = FX;
L1260:
    BL[2] = TY;
L1270:
    BL[3] = TX;
L1280:
    MI = MI + 1;
L1290:
    goto L940;
L1300:
    /* */
L1310:
    printf("%s", "Best eval: ");
    printf("%d", BSTV);
    printf("\n");
L1320:
    printf("%s", "Best move: ");
    printf("%d", BL[0]);
    printf("%s", ",");
    printf("%d", BL[1]);
    printf("%s", " to ");
    printf("%d", BL[2]);
    printf("%s", ",");
    printf("%d", BL[3]);
    printf("\n");
L1330:
    printf("%s", "Nodes: ");
    printf("%d", NODES);
    printf("\n");
L1340:
    DEP = DEP + 1;
L1350:
    goto L670;
L1360:
    /* */
L9990:
    return 0;
L10000:
    /* MOVE GENERATION DISPATCH */
L10010:
    if (P == 1) goto L11000;
L10020:
    if (P == 2) goto L12000;
L10030:
    if (P == 3) goto L13000;
L10040:
    if (P == 4) goto L14000;
L10050:
    if (P == 5) goto L15000;
L10060:
    if (P == 6) goto L16000;
L10070:
    goto L820;
L10080:
    /* */
L11000:
    /* PAWN MOVES from Y , X */
L11010:
    if (Y == 7) goto L810;
L11020:
    Y1 = Y + 1;
L11030:
    if (B[Y1 * 8 + X] != 0) goto L11150;
L11040:
    if (Y != 6) goto L11080;
L11050:
    /* Promotion */
L11060:
    goto L50000;
L11070:
    goto L11150;
L11080:
    goto L50000;
L11090:
    /* Double push */
L11100:
    if (Y != 1) goto L11150;
L11110:
    if (B[( Y + 2 ) * 8 + X] != 0) goto L11150;
L11120:
    Y1 = Y + 2;
L11130:
    goto L50000;
L11150:
    /* Left capture */
L11160:
    if (X <= 0) goto L11230;
L11170:
    X1 = X - 1;
L11180:
    Y1 = Y + 1;
L11190:
    if (B[Y1 * 8 + X1] >= 0) goto L11230;
L11200:
    if (Y == 6) goto L11220;
L11210:
    goto L50000;
L11220:
    goto L50000;
L11230:
    /* Right capture */
L11240:
    if (X >= 7) goto L11310;
L11250:
    X1 = X + 1;
L11260:
    Y1 = Y + 1;
L11270:
    if (B[Y1 * 8 + X1] >= 0) goto L11310;
L11280:
    if (Y == 6) goto L11300;
L11290:
    goto L50000;
L11300:
    goto L50000;
L11310:
    goto L820;
L11320:
    /* */
L12000:
    /* KNIGHT MOVES from Y , X */
L12010:
    DY = 2;
L12020:
    DX = 1;
L12030:
    goto L51000;
L12040:
    DY = 2;
L12050:
    DX = - 1;
L12060:
    goto L51000;
L12070:
    DY = - 2;
L12080:
    DX = 1;
L12090:
    goto L51000;
L12100:
    DY = - 2;
L12110:
    DX = - 1;
L12120:
    goto L51000;
L12130:
    DY = 1;
L12140:
    DX = 2;
L12150:
    goto L51000;
L12160:
    DY = - 1;
L12170:
    DX = 2;
L12180:
    goto L51000;
L12190:
    DY = 1;
L12200:
    DX = - 2;
L12210:
    goto L51000;
L12220:
    DY = - 1;
L12230:
    DX = - 2;
L12240:
    goto L51000;
L12250:
    goto L820;
L12260:
    /* */
L13000:
    /* BISHOP MOVES from Y , X */
L13010:
    DY = 1;
L13020:
    DX = 1;
L13030:
    goto L52000;
L13040:
    DY = 1;
L13050:
    DX = - 1;
L13060:
    goto L52000;
L13070:
    DY = - 1;
L13080:
    DX = 1;
L13090:
    goto L52000;
L13100:
    DY = - 1;
L13110:
    DX = - 1;
L13120:
    goto L52000;
L13130:
    goto L820;
L13140:
    /* */
L14000:
    /* ROOK MOVES from Y , X */
L14010:
    DY = 1;
L14020:
    DX = 0;
L14030:
    goto L52000;
L14040:
    DY = - 1;
L14050:
    DX = 0;
L14060:
    goto L52000;
L14070:
    DY = 0;
L14080:
    DX = 1;
L14090:
    goto L52000;
L14100:
    DY = 0;
L14110:
    DX = - 1;
L14120:
    goto L52000;
L14130:
    goto L820;
L14140:
    /* */
L15000:
    /* QUEEN MOVES from Y , X */
L15010:
    DY = 1;
L15020:
    DX = 1;
L15030:
    goto L52000;
L15040:
    DY = 1;
L15050:
    DX = - 1;
L15060:
    goto L52000;
L15070:
    DY = - 1;
L15080:
    DX = 1;
L15090:
    goto L52000;
L15100:
    DY = - 1;
L15110:
    DX = - 1;
L15120:
    goto L52000;
L15130:
    DY = 1;
L15140:
    DX = 0;
L15150:
    goto L52000;
L15160:
    DY = - 1;
L15170:
    DX = 0;
L15180:
    goto L52000;
L15190:
    DY = 0;
L15200:
    DX = 1;
L15210:
    goto L52000;
L15220:
    DY = 0;
L15230:
    DX = - 1;
L15240:
    goto L52000;
L15250:
    goto L820;
L15260:
    /* */
L16000:
    /* KING MOVES from Y , X */
L16010:
    DY = 1;
L16020:
    DX = 1;
L16030:
    goto L51000;
L16040:
    DY = 1;
L16050:
    DX = 0;
L16060:
    goto L51000;
L16070:
    DY = 1;
L16080:
    DX = - 1;
L16090:
    goto L51000;
L16100:
    DY = 0;
L16110:
    DX = 1;
L16120:
    goto L51000;
L16130:
    DY = 0;
L16140:
    DX = - 1;
L16150:
    goto L51000;
L16160:
    DY = - 1;
L16170:
    DX = 1;
L16180:
    goto L51000;
L16190:
    DY = - 1;
L16200:
    DX = 0;
L16210:
    goto L51000;
L16220:
    DY = - 1;
L16230:
    DX = - 1;
L16240:
    goto L51000;
L16250:
    goto L820;
L16260:
    /* */
L20000:
    /* TRANSPOSE BOARD */
L20010:
    Y = 0;
L20020:
    if (Y > 3) goto L20120;
L20030:
    X = 0;
L20040:
    if (X > 7) goto L20100;
L20050:
    I1 = Y * 8 + X;
L20060:
    I2 = ( 7 - Y ) * 8 + X;
L20070:
    T = B[I1];
L20080:
    B[I1] = B[I2];
L20090:
    B[I2] = T;
L20100:
    X = X + 1;
L20110:
    goto L20040;
L20120:
    Y = Y + 1;
L20130:
    goto L20020;
L20140:
    I = 0;
L20150:
    if (I > 63) goto L20190;
L20160:
    B[I] = 0 - B[I];
L20170:
    I = I + 1;
L20180:
    goto L20150;
L20190:
    goto L1110;
L20200:
    /* */
L30000:
    /* EVALUATE POSITION */
L30010:
    NODES = NODES + 1;
L30020:
    EVAL = 0;
L30030:
    Y = 0;
L30040:
    if (Y > 7) goto L30300;
L30050:
    X = 0;
L30060:
    if (X > 7) goto L30280;
L30070:
    P = B[Y * 8 + X];
L30080:
    if (P == 0) goto L30260;
L30090:
    if (P == 1) goto L30140;
L30100:
    if (P == 2) goto L30160;
L30110:
    if (P == 3) goto L30180;
L30120:
    if (P == 4) goto L30200;
L30130:
    if (P == 5) goto L30220;
L30140:
    if (Y < 4) goto L30150;
L30145:
    if (Y == 4) goto L30155;
L30147:
    if (Y == 5) goto L30160;
L30148:
    EVAL = EVAL + 400;
L30149:
    goto L30260;
L30150:
    EVAL = EVAL + 100;
L30152:
    goto L30260;
L30155:
    EVAL = EVAL + 120;
L30157:
    goto L30260;
L30160:
    EVAL = EVAL + 200;
L30162:
    goto L30260;
L30170:
    EVAL = EVAL + NV;
L30175:
    goto L30260;
L30180:
    EVAL = EVAL + BV;
L30185:
    goto L30260;
L30200:
    EVAL = EVAL + RV;
L30205:
    goto L30260;
L30220:
    EVAL = EVAL + QV;
L30225:
    goto L30260;
L30230:
    if (P == - 1) goto L30240;
L30232:
    if (P == - 2) goto L30244;
L30234:
    if (P == - 3) goto L30246;
L30236:
    if (P == - 4) goto L30248;
L30238:
    if (P == - 5) goto L30250;
L30240:
    EVAL = EVAL - 100;
L30242:
    goto L30260;
L30244:
    EVAL = EVAL - NV;
L30245:
    goto L30260;
L30246:
    EVAL = EVAL - BV;
L30247:
    goto L30260;
L30248:
    EVAL = EVAL - RV;
L30249:
    goto L30260;
L30250:
    EVAL = EVAL - QV;
L30260:
    X = X + 1;
L30270:
    goto L30060;
L30280:
    Y = Y + 1;
L30290:
    goto L30040;
L30300:
    goto L1130;
L30310:
    /* */
L50000:
    /* ADD MOVE to list */
L50010:
    MBASE = MCNT * 5;
L50020:
    M[MBASE] = Y;
L50030:
    M[MBASE + 1] = X;
L50040:
    M[MBASE + 2] = Y1;
L50050:
    M[MBASE + 3] = X1;
L50060:
    M[MBASE + 4] = 0;
L50070:
    MCNT = MCNT + 1;
L50080:
    /* Return varies by caller */
L50090:
    if (P == 1) goto L11090;
L50100:
    goto L820;
L50110:
    /* */
L51000:
    /* ADD NONSLIDER MOVE */
L51010:
    Y1 = Y + DY;
L51020:
    X1 = X + DX;
L51030:
    if (Y1 < 0) goto L51120;
L51040:
    if (Y1 > 7) goto L51120;
L51050:
    if (X1 < 0) goto L51120;
L51060:
    if (X1 > 7) goto L51120;
L51070:
    if (B[Y1 * 8 + X1] > 0) goto L51120;
L51080:
    MBASE = MCNT * 5;
L51090:
    M[MBASE] = Y;
L51100:
    M[MBASE + 1] = X;
L51110:
    M[MBASE + 2] = Y1;
L51120:
    M[MBASE + 3] = X1;
L51130:
    M[MBASE + 4] = 0;
L51140:
    MCNT = MCNT + 1;
L51150:
    /* Return to knight / king */
L51160:
    if (P == 2) goto L12040;
L51170:
    if (P == 6) goto L16040;
L51180:
    goto L820;
L51190:
    /* */
L52000:
    /* ADD SLIDER MOVES */
L52010:
    Y1 = Y;
L52020:
    X1 = X;
L52030:
    Y1 = Y1 + DY;
L52040:
    X1 = X1 + DX;
L52050:
    if (Y1 < 0) goto L52200;
L52060:
    if (Y1 > 7) goto L52200;
L52070:
    if (X1 < 0) goto L52200;
L52080:
    if (X1 > 7) goto L52200;
L52090:
    P1 = B[Y1 * 8 + X1];
L52100:
    if (P1 > 0) goto L52200;
L52110:
    MBASE = MCNT * 5;
L52120:
    M[MBASE] = Y;
L52130:
    M[MBASE + 1] = X;
L52140:
    M[MBASE + 2] = Y1;
L52150:
    M[MBASE + 3] = X1;
L52160:
    M[MBASE + 4] = 0;
L52170:
    MCNT = MCNT + 1;
L52180:
    if (P1 < 0) goto L52200;
L52190:
    goto L52030;
L52200:
    /* Return to piece */
L52210:
    if (P == 3) goto L13040;
L52220:
    if (P == 4) goto L14040;
L52230:
    if (P == 5) goto L15040;
L52240:
    goto L820;
    return 0;
}
