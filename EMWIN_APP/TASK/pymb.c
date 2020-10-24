#include <stdio.h>
#include <string.h>
#include <stdio.h>

struct PY_index
{
    const char *PY;
    const char *PY_mb;
};

//"ƴ�����뷨�������б�,���(mb)"
const char PY_mb_space []={""};
const char PY_mb_a     []={"������߹�����"};
const char PY_mb_ai    []={"���������������������������������������������"};
const char PY_mb_an    []={"���������������������������������������"};
const char PY_mb_ang   []={"��������"};
const char PY_mb_ao    []={"�������°��ð��������������������������������"};
const char PY_mb_ba    []={"�Ѱ˰ɰְΰհϰͰŰǰӰ԰Ȱаʰ̰Ұ������������"};
const char PY_mb_bai   []={"�ٰװڰܰذݰ۲���������"};
const char PY_mb_ban   []={"��������߰����������������"};
const char PY_mb_bang  []={"���������������������"};
const char PY_mb_bao   []={"�����������������������ٱ����������������������������"};
const char PY_mb_bei   []={"�������������������������������������������"};
const char PY_mb_ben   []={"�����������������"};
const char PY_mb_beng  []={"�ı��±��Ű������"};
const char PY_mb_bi    []={"�ȱʱձǱ̱رܱƱϱ۱˱ɱڱͱұױٱαбӱֱݱѱ�������޵ݩ����ذ���������������������������������������������"};
const char PY_mb_bian  []={"�߱�������ޱ���������������������������"};
const char PY_mb_biao  []={"���������������������"};
const char PY_mb_bie   []={"�������"};
const char PY_mb_bin   []={"������������������������������"};
const char PY_mb_bing  []={"����������������������������"};
const char PY_mb_bo    []={"����������������������������������ز����������ǲ�������������ެ�������"};
const char PY_mb_bu    []={"�������������������������������������߲"};
const char PY_mb_ca    []={"��������"};
const char PY_mb_cai   []={"�²ŲĲƲòɲʲǲȲ˲�"};
const char PY_mb_can   []={"�ϲв��βҲѲͲ����������"};
const char PY_mb_cang  []={"�زֲײղ���"};
const char PY_mb_cao   []={"�ݲٲܲ۲��������"};
const char PY_mb_ce    []={"���߲����"};
const char PY_mb_cen   []={"����"};
const char PY_mb_ceng  []={"�������"};
const char PY_mb_cha   []={"�����������ɲ��������������������"};
const char PY_mb_chai  []={"�˲���������٭"};
const char PY_mb_chan  []={"��������������������������������������������������"};
const char PY_mb_chang []={"���������������������������������������������������"};
const char PY_mb_chao  []={"�����������������˴³���������"};
const char PY_mb_che   []={"�����������߳����"};
const char PY_mb_chen  []={"�óƳ����������³ĳȳ��������������������"};
const char PY_mb_cheng []={"�ɳ�ʢ�ųƳǳ̳ʳϳͳѳҳγȳ�����������������������ة�"};
const char PY_mb_chi   []={"�Գ߳ٳس�ճ�ݳֳܳ�޳ڳ۳��������ܯ����������������������߳������"};
const char PY_mb_chong []={"���س����ӿ������������"};
const char PY_mb_chou  []={"���������������ٱ�����"};
const char PY_mb_chu   []={"�������������������������������������ۻ���ء����������"};
const char PY_mb_chuai []={"�����������"};
const char PY_mb_chuan []={"������������������������"};
const char PY_mb_chuang[]={"��������������"};
const char PY_mb_chui  []={"����������׵����"};
const char PY_mb_chun  []={"����������������ݻ��"};
const char PY_mb_chuo  []={"����������"};
const char PY_mb_ci    []={"�δ˴ʴɴȴƴŴǴ̴��ŴôͲ�����������"};
const char PY_mb_cong  []={"�ӴԴдҴϴ������������"};
const char PY_mb_cou   []={"������"};
const char PY_mb_cu    []={"�ִ״ش����������������"};
const char PY_mb_cuan  []={"�ܴڴ���ߥ������"};
const char PY_mb_cui   []={"�ߴ�ݴ�޴�˥������������"};
const char PY_mb_cun   []={"���������"};
const char PY_mb_cuo   []={"������������������������"};
const char PY_mb_da    []={"����������������������������"};
const char PY_mb_dai   []={"�������������������������߾�����߰�����ܤ"};
const char PY_mb_dan   []={"������������������������������ʯ��������������������"};
const char PY_mb_dang  []={"����������������������"};
const char PY_mb_dao   []={"���������������������������������߶"};
const char PY_mb_de    []={"�ĵصõµ��"};
const char PY_mb_dei[]   ={"��"};
const char PY_mb_deng  []={"�ȵƵ˵ǳεɵʵ������������"};
const char PY_mb_di    []={"�صڵ׵͵еֵε۵ݵյܵ޵̵ĵ���ѵϵҵԵ���ۡ��ڮ��������ص����ݶ����������"};
const char PY_mb_dia        []={"��"};
const char PY_mb_dian  []={"�������ߵ�������������������������"};
const char PY_mb_diao  []={"�����������������������"};
const char PY_mb_die   []={"���������������ܦ������������"};
const char PY_mb_ding  []={"������������������������������������"};
const char PY_mb_diu   []={"����"};
const char PY_mb_dong  []={"����������������������������������"};
const char PY_mb_dou   []={"������������������������"};
const char PY_mb_du    []={"���ȶ��ɶ¶��ǶƶĶöŶ������ʶ��������������ܶ"};
const char PY_mb_duan  []={"�ζ̶϶˶Ͷ������"};
const char PY_mb_dui   []={"�ԶӶѶҶ�������"};
const char PY_mb_dun   []={"�ֶٶ׶նض۶ܶڶݲ��������������"};
const char PY_mb_duo   []={"����������޶��Զȶ��������������"};
const char PY_mb_e     []={"��Ŷ������ﰢ������������������������ݭ��������ج����"};
const char PY_mb_ei    []={"��"};
const char PY_mb_en    []={"������"};
const char PY_mb_er    []={"���������������������٦����"};
const char PY_mb_fa    []={"��������������������"};
const char PY_mb_fan   []={"���������������������������������������ެ�����"};
const char PY_mb_fang  []={"�ŷ����ķ����÷·�����������������"};
const char PY_mb_fei   []={"�ǷɷʷѷηϷ˷ͷзƷ̷�������������������������������"};
const char PY_mb_fen   []={"�ַݷҷ۷طܷ߷׷޷�ӷٷԷշ������������"};
const char PY_mb_feng  []={"�����������������ٺۺ������"};
const char PY_mb_fo    []={"��"};
const char PY_mb_fou   []={"���"};
const char PY_mb_fu    []={"�����������������������������������򸸷����󸳸���������������������������������и����������������������������������������������������������ݳ���������߻ۮܽ��"};
const char PY_mb_ga    []={"����и¿�����٤���������"};
const char PY_mb_gai   []={"�øĸǸŸƽ�����ؤ����"};
const char PY_mb_gan   []={"�ϸɸиҸ͸ʸθ̸˸Ӹ�����������ߦ�����������"};
const char PY_mb_gang  []={"�ոָٸ۸׸ڸܸԸؿ�����"};
const char PY_mb_gao   []={"�߸����ݸ����۬ھ���غ�����޻"};
const char PY_mb_ge    []={"�������������￩���������ٺϸ��������ܪ���������ت���������"};
const char PY_mb_gei   []={"��"};
const char PY_mb_gen   []={"������ݢب��"};
const char PY_mb_geng  []={"�����������������������"};
const char PY_mb_gong  []={"���������������������������������������"};
const char PY_mb_gou   []={"��������������������������������ڸ��������"};
const char PY_mb_gu    []={"�ŹɹĹȹʹ¹��ù˹̹͹����ǹ����Ƽֹ��������������������������ڬ�����������������"};
const char PY_mb_gua   []={"�ҹιϹѹй����������ڴ"};
const char PY_mb_guai  []={"�ֹչ���"};
const char PY_mb_guan  []={"�عܹٹ۹ݹ߹޹�ڹ��������ݸ����������"};
const char PY_mb_guang []={"������������"};
const char PY_mb_gui   []={"��������������������Ȳ���������������������"};
const char PY_mb_gun   []={"�������������"};
const char PY_mb_guo   []={"�����������������������������������"};
const char PY_mb_ha    []={"����Ϻ��"};
const char PY_mb_hai   []={"�������Ⱥ���������������"};
const char PY_mb_han   []={"����������������������������������������������������������"};
const char PY_mb_hang  []={"���ﺽ�������������"};
const char PY_mb_hao   []={"�úźƺ����º����ĺѸ�������������޶"};
const char PY_mb_he    []={"�ͺȺϺӺ̺˺κǺɺغպֺк׺ʺѺҺ����������������ڭ����"};
const char PY_mb_hei   []={"�ں�"};
const char PY_mb_hen   []={"�ܺݺ޺�"};
const char PY_mb_heng  []={"���ߺ��������޿"};
const char PY_mb_hong  []={"����������ڧ��ޮ��ް��ݦ��"};
const char PY_mb_hou   []={"������������ܩ����������"};
const char PY_mb_hu    []={"��������������������������������Ϸ�˺ͺ�������������������������������������������������"};
const char PY_mb_hua   []={"���������������������������"};
const char PY_mb_huai  []={"��������������"};
const char PY_mb_huan  []={"���������������û»������������ߧ����ۨ���ۼ����������"};
const char PY_mb_huang []={"�ƻŻλĻɻ˻ʻѻ̻Ȼǻлͻ�������������"};
const char PY_mb_hui   []={"�ػ�һ�ӻ�Իٻڻݻ޻ջֻ�ۻ߻׻仲�ܻ�������ޥ����������ڶ�����������"};
const char PY_mb_hun   []={"���������������ڻ"};
const char PY_mb_huo   []={"�������ͻ���������������޽߫������"};
const char PY_mb_ji    []={"�������ȼ��������Ǽ����Ƽ������ļ�ϵ���������ʻ������������������������������������������������¼ü����������˼̸���������������������ڵ��������ߴ����������������������آ��ܸ٥�������ު����"};
const char PY_mb_jia   []={"�ҼӼټۼܼ׼Ѽмμݼ޼ϼԼռؼ��Ѽ�������������������٤��������ۣ����"};
const char PY_mb_jian  []={"��������������潨��������߼��齡�������������ǳ���������𽢼���뽤��������������������������������������������������"};
const char PY_mb_jiang []={"������������������������ǿ��������������������"};
const char PY_mb_jiao  []={"�нŽ��ǽ̽Ͻɾ���������У�����ƽ��ý������νѽ����Ƚ½ͽĽ���ܴ������������������ٮ������"};
const char PY_mb_jie   []={"�ӽڽֽ�Խؽ�����ҽ��׽ٽ�߽���ۿ��ս۽ܽݽ�޼��������������������ڦ����ڵ"};
const char PY_mb_jin   []={"�����������ﾡ�������������������������������ݣ�������������"};
const char PY_mb_jing  []={"�������������������������������������������������������������������ݼ���������"};
const char PY_mb_jiong []={"��������"};
const char PY_mb_jiu   []={"�;žƾɾþ��Ⱦ��˾��¾Ǿʾ��ľ̾�������������������"};
const char PY_mb_ju    []={"��پ޾־߾���Ӿ۾оվؾھܾ�ϾѾ��Ҿݹ�۾㳵�׾Ҿ��������������������������������������������ڪ��"};
const char PY_mb_juan  []={"��Ȧ�������۲�������������"};
const char PY_mb_jue   []={"�������Ǿ����������������������������������ާ����������"};
const char PY_mb_jun   []={"�������������꿢����������������"};
const char PY_mb_ka    []={"��������������"};
const char PY_mb_kai   []={"�������������������������"};
const char PY_mb_kan   []={"��������Ƕ���������٩�ݨ��"};
const char PY_mb_kang  []={"��������������������"};
const char PY_mb_kao   []={"����������������"};
const char PY_mb_ke    []={"�ȿɿ˿ÿƿſ̿οͿǿʿ��¿Ŀ��������������������������������"};
const char PY_mb_ken   []={"�Ͽпҿ���"};
const char PY_mb_keng  []={"�ӿ��"};
const char PY_mb_kong  []={"�տ׿ؿ�������"};
const char PY_mb_kou   []={"�ڿۿٿ�ޢ������ߵ"};
const char PY_mb_ku    []={"�޿��ݿ�߿������ܥ�"};
const char PY_mb_kua   []={"������٨"};
const char PY_mb_kuai  []={"�����������ۦ����"};
const char PY_mb_kuan  []={"�����"};
const char PY_mb_kuang []={"�����������ڿ������ڲ������"};
const char PY_mb_kui   []={"�������������������������������������������ظ������"};
const char PY_mb_kun   []={"��������������������"};
const char PY_mb_kuo   []={"��������������"};
const char PY_mb_la    []={"���������������������������"};
const char PY_mb_lai   []={"���������������������"};
const char PY_mb_lan   []={"����������������������������������������"};
const char PY_mb_lang  []={"������������������ݹ������"};
const char PY_mb_lao   []={"���������������������������������������"};
const char PY_mb_le    []={"����������߷����"};
const char PY_mb_lei   []={"��������������������������ڳ������������"};
const char PY_mb_leng  []={"������ܨ�"};
const char PY_mb_li    []={"��������������������������������������������������������������������ٳٵ۪����ݰ���������������������ت߿������������޼���������������������������"};
const char PY_mb_lia        []={"��"};
const char PY_mb_lian  []={"������������������������������������������������"};
const char PY_mb_liang []={"������������������������ܮ�������ݹ"};
const char PY_mb_liao  []={"����������������������������ޤ����������"};
const char PY_mb_lie   []={"�������������������������"};
const char PY_mb_lin   []={"�����������������������������������������������"};
const char PY_mb_ling  []={"��������������������������������������۹��������������"};
const char PY_mb_liu   []={"����������������������µ½����������������"};
const char PY_mb_lo[]    ={"��"};
const char PY_mb_long  []={"��£����¡¢Ū����¤���������������"};
const char PY_mb_lou   []={"¥§©ª¶¦¨�����������������"};
const char PY_mb_lu    []={"·¶¼¹½¯¬³±«­®µ°��²¸¾º»´��������ޤ�������������������"};
const char PY_mb_luan  []={"��������������������"};
const char PY_mb_lue   []={"�����"};
const char PY_mb_lun   []={"����������������"};
const char PY_mb_luo   []={"�������������������������翩���������������������������"};
const char PY_mb_lv    []={"������¿���������������������������������"};
const char PY_mb_ma    []={"������������Ĩ������Ħ��������"};
const char PY_mb_mai   []={"������������۽��ݤ"};
const char PY_mb_man   []={"������������������á���ܬ�����������"};
const char PY_mb_mang  []={"æâäçãå��������"};
const char PY_mb_mao   []={"ëðñèìîòïóíêé���������������������"};
const char PY_mb_me    []={"ô��"};
const char PY_mb_mei   []={"ûÿúþ��ø��öùõü÷����ý������ĭ����������ݮ�����"};
const char PY_mb_men   []={"�������������"};
const char PY_mb_meng  []={"����������������å������������������ޫ"};
const char PY_mb_mi    []={"��������������������������������������������������������"};
const char PY_mb_mian  []={"������������������������������"};
const char PY_mb_miao  []={"������������������������������"};
const char PY_mb_mie   []={"���������ؿ"};
const char PY_mb_min   []={"������������������������������"};
const char PY_mb_ming  []={"��������������ڤ���������"};
const char PY_mb_miu   []={"����"};
const char PY_mb_mo    []={"��ĥĨĩĤīûĪĬħģĦġĮİ��ĭ����ðį�������Ժ���Ģ�����������������"};
const char PY_mb_mou   []={"ĳıĲ������ٰ����"};
const char PY_mb_mu    []={"ľĸĶĻĿĹ��Ĳģ��ĺĵĴļĽ��ķ�������������"};
const char PY_mb_na    []={"������������������������"};
const char PY_mb_nai   []={"��������������ܵ��ؾ٦"};
const char PY_mb_nan   []={"����������������"};
const char PY_mb_nang  []={"��������߭"};
const char PY_mb_nao   []={"����������ث������������"};
const char PY_mb_ne    []={"��������ګ"};
const char PY_mb_nei   []={"��������"};
const char PY_mb_nen   []={"���"};
const char PY_mb_neng  []={"��"};
const char PY_mb_ng[]    ={"��"};
const char PY_mb_ni    []={"���������������������������������٣�������"};
const char PY_mb_nian  []={"��������������ճإ���������"};
const char PY_mb_niang []={"����"};
const char PY_mb_niao  []={"������������"};
const char PY_mb_nie   []={"������������������������ؿ"};
const char PY_mb_nin   []={"���"};
const char PY_mb_ning  []={"š��������Ţ�������"};
const char PY_mb_niu   []={"ţŤŦť�������"};
const char PY_mb_nong  []={"ŪŨũŧ��ٯ"};
const char PY_mb_nou[]   ={"��"};
const char PY_mb_nu    []={"ŭŬū��������"};
const char PY_mb_nuan  []={"ů"};
const char PY_mb_nue   []={"Űű��"};
const char PY_mb_nuo   []={"ŲŵųŴ���������"};
const char PY_mb_nv    []={"Ů�����"};
const char PY_mb_o     []={"Ŷ���"};
const char PY_mb_ou    []={"żŻŷźŸ��ŽŹ���ک��"};
const char PY_mb_pa    []={"����ſž�Ұ�������������"};
const char PY_mb_pai   []={"����������������ٽ��"};
const char PY_mb_pan   []={"���������������ͷ������������������"};
const char PY_mb_pang  []={"���������Ұ���������"};
const char PY_mb_pao   []={"������������������������"};
const char PY_mb_pei   []={"�����������������������������"};
const char PY_mb_pen   []={"������"};
const char PY_mb_peng  []={"������������������������������ܡ���"};
const char PY_mb_pi    []={"��Ƥ��ƥ������ƨƢƧƣƦ������ơƩ������ا�������ߨۯ������ܱ�����������������������"};
const char PY_mb_pian  []={"Ƭƪƭƫ�����������������"};
const char PY_mb_piao  []={"ƱƮƯư���ݳ�������������"};
const char PY_mb_pie   []={"ƳƲ���"};
const char PY_mb_pin   []={"ƷƶƸƴƵ�������"};
const char PY_mb_ping  []={"ƽƾƿ����ƹƼƻƺ�������ٷ"};
const char PY_mb_po    []={"�����������Ȳ����ӷ����������۶�������"};
const char PY_mb_pou   []={"������"};
const char PY_mb_pu    []={"�����׸����������������������ֱ��ձ����������������W"};
const char PY_mb_qi    []={"�������������������������������������������������������������������������������������ݽޭ���������ܻ��ؽ��ٹ��������������������������������"};
const char PY_mb_qia   []={"ǡ����Ǣ������"};
const char PY_mb_qian  []={"ǰǮǧǣǳǩǷǦǶǥǨǯǬǴǫǱǸ��ǤǲǭǵǪ���������ٻ������ݡ����ܷ�����������"};
const char PY_mb_qiang []={"ǿǹǽ��ǻǺǼǾ������������������������"};
const char PY_mb_qiao  []={"�����������¿�����������ȸ������������������������ڽ��"};
const char PY_mb_qie   []={"������������ۧ���������٤��"};
const char PY_mb_qin   []={"����������������������������������������������"};
const char PY_mb_qing  []={"��������������������������������������������������"};
const char PY_mb_qiong []={"�����������������"};
const char PY_mb_qiu   []={"���������������������������������ٴ�������������"};
const char PY_mb_qu    []={"ȥȡ��Ȣ������Ȥ��������ȣ���޾��ޡ��۾ڰ�����������������������"};
const char PY_mb_quan  []={"ȫȨȰȦȭȮȪȯȧȬȩ�����ڹ����������"};
const char PY_mb_que   []={"ȴȱȷȸȳȵȲȶ�����"};
const char PY_mb_qui[]   ={"��"};
const char PY_mb_qun   []={"Ⱥȹ����"};
const char PY_mb_ran   []={"ȾȼȻȽ������"};
const char PY_mb_rang  []={"����ȿ�������"};
const char PY_mb_rao   []={"�����������"};
const char PY_mb_re    []={"��������"};
const char PY_mb_ren   []={"���������������������������������"};
const char PY_mb_reng  []={"����"};
const char PY_mb_ri    []={"��"};
const char PY_mb_rong  []={"������������������������������"};
const char PY_mb_rou   []={"������������"};
const char PY_mb_ru    []={"������������������������������޸����"};
const char PY_mb_ruan  []={"������"};
const char PY_mb_rui   []={"������������ި"};
const char PY_mb_run   []={"����"};
const char PY_mb_ruo   []={"����ټ��"};
const char PY_mb_sa    []={"����������ئ���"};
const char PY_mb_sai   []={"������˼����"};
const char PY_mb_san   []={"��ɢɡ���������"};
const char PY_mb_sang  []={"ɣɥɤ�����"};
const char PY_mb_sao   []={"ɨɩɦɧ��ܣ��������"};
const char PY_mb_se    []={"ɫɬɪ������"};
const char PY_mb_sen   []={"ɭ"};
const char PY_mb_seng  []={"ɮ"};
const char PY_mb_sha   []={"ɱɳɶɴɵɰɲɯ��ɷɼ����������������"};
const char PY_mb_shai  []={"ɹɸɫ��"};
const char PY_mb_shan  []={"ɽ��������ɼɾɿ��ɺ����դɻ���������������������۷�������������ڨ������"};
const char PY_mb_shang []={"���������������������������"};
const char PY_mb_shao  []={"����������������������������ۿ��������"};
const char PY_mb_she   []={"�������������������������������������"};
const char PY_mb_shei[]  ={"˭"};
const char PY_mb_shen  []={"�����������������������������ʲ��������ݷڷ�������������"};
const char PY_mb_sheng []={"��ʡʣ������ʤʢʥ����������������"};
const char PY_mb_shi   []={"��ʹʮʱ������ʯʦ��ʷʽʶʭʸʰʺʻʼ����ʾʿ��������������ʲֳ������ʧ������������ʨʳ��ʴ��ʵʩʪʫʬ��ݪ����������������������߱���"};
const char PY_mb_shou  []={"���������������������������"};
const char PY_mb_shu   []={"��������������������������������������������������ˡ�������������������"};
const char PY_mb_shua  []={"ˢˣ�"};
const char PY_mb_shuai []={"ˤ˦��˧˥�"};
const char PY_mb_shuan []={"˨˩����"};
const char PY_mb_shuang[]={"˫˪ˬ����"};
const char PY_mb_shui  []={"ˮ˭˯˰˵"};
const char PY_mb_shun  []={"˳˱˲˴"};
const char PY_mb_shuo  []={"˵��˶˸˷����������"};
const char PY_mb_si    []={"����˿˺��˽˻˼��˾˹ʳ�Ų���������������������������������������ٹ"};
const char PY_mb_song  []={"�����������������ݿ�����ڡ����"};
const char PY_mb_sou   []={"��������������޴�����������"};
const char PY_mb_su    []={"�����������������������������������������"};
const char PY_mb_suan  []={"�������"};
const char PY_mb_sui   []={"���������������������������������ݴ�"};
const char PY_mb_sun   []={"�������ݥ�����"};
const char PY_mb_suo   []={"��������������ɯ�����������������"};
const char PY_mb_ta    []={"������̤������̡̢̣�����������������"};
const char PY_mb_tai   []={"̧̨̫̬̥̦̩̪̭������߾����޷ۢ��"};
const char PY_mb_tan   []={"̸̲̾̽��̶̵̷̴̼̯̰̳̺̹̱̮̻̿۰������������"};
const char PY_mb_tang  []={"�����������������������������������������������"};
const char PY_mb_tao   []={"����������������������ػ������߶��"};
const char PY_mb_te    []={"������߯"};
const char PY_mb_teng  []={"����������"};
const char PY_mb_ti    []={"���������������������������������������������"};
const char PY_mb_tian  []={"����������������������������"};
const char PY_mb_tiao  []={"����������������������٬�������"};
const char PY_mb_tie   []={"����������"};
const char PY_mb_ting  []={"��ͣͦ��ͤͧͥ͢��͡���������������"};
const char PY_mb_tong  []={"ͬͨʹͭͰͲͱͳͯͮͩͫ����ͪ�����������١����"};
const char PY_mb_tou   []={"ͷ͵͸Ͷ����"};
const char PY_mb_tu    []={"��ͼ��Ϳ��ͺͻͽ͹;��ܢݱ������"};
const char PY_mb_tuan  []={"���������"};
const char PY_mb_tui   []={"��������������߯"};
const char PY_mb_tun   []={"�������ζ��������"};
const char PY_mb_tuo   []={"������������������������ر٢����������������������"};
const char PY_mb_wa    []={"�����������ݰ��������"};
const char PY_mb_wai   []={"������"};
const char PY_mb_wan   []={"��������������������������������������ݸ�����ܹ���������"};
const char PY_mb_wang  []={"��������������������â�������"};
const char PY_mb_wei   []={"ΪλδΧιθ΢ζβα��ΰ��ΣΥίκΨάηΩΤΡενξΫγοΦήέμ�������������������������������������������ޱ��"};
const char PY_mb_wen   []={"�����������������������������"};
const char PY_mb_weng  []={"��������޳"};
const char PY_mb_wo    []={"������������������������ݫ�����"};
const char PY_mb_wu    []={"������������������������������������������������������������������أ���������������������������������������"};
const char PY_mb_xi    []={"��ϴϸ��ϷϵϲϯϡϪϨ��ϥϢϮϧϰ��ϦϤ����ϣϭ������ϱ��ϳϩ����϶��ϫϬ����������������������������������������������ۭ����������������ݾ������"};
const char PY_mb_xia   []={"������ϿϺϹϼ��ϻ��Ͻ��Ͼ�����������������"};
const char PY_mb_xian  []={"����������������������������������������������������ϳ����޺���ݲ���������������������������"};
const char PY_mb_xiang []={"���������������������������ή������������ܼ��������������"};
const char PY_mb_xiao  []={"СЦ��������Ч����ФТ��Х������У�������������������������"};
const char PY_mb_xie   []={"дЩЬЪбѪлжЮмзкийШаЭегЫЯв����Ҷ��������ߢ�����������ޯ������"};
const char PY_mb_xin   []={"��������онп��Ѱ�����ضݷܰ�����"};
const char PY_mb_xing  []={"������������������������������ʡ�������ߩ��"};
const char PY_mb_xiong []={"��������������ܺ"};
const char PY_mb_xiu   []={"�����������������������������������"};
const char PY_mb_xu    []={"�����������������������������������������������ޣ���������ڼ�������"};
const char PY_mb_xuan  []={"ѡ������������ѤѣѢȯ������������������������������"};
const char PY_mb_xue   []={"ѧѩѪѥѨ��Ѧ�������"};
const char PY_mb_xun   []={"ѰѶѬѵѭѳѮѲѸѱѴѷѫ��ѯ��������ަ޹��������������ۨ�"};
const char PY_mb_ya    []={"ѽѹ��ѺѿѼ����������Ѿ����ѻ��������������������������"};
const char PY_mb_yan   []={"����������������������������������������������������������������������������������������������������ٲ۱۳�������������Ǧ����ܾ������"};
const char PY_mb_yang  []={"������������������������������������������������"};
const char PY_mb_yao   []={"Ҫҡҩҧ��ҤҨ����ҥңҦ��ҫҢԿ��زسߺ���������������������ű��Լ�"};
const char PY_mb_ye    []={"ҲҹҵҰҶүҳҺҴҸұҭҮ��ҷҬа��������������"};
const char PY_mb_yi    []={"һ��������������ҽ������������������������ʳ��������������Ҽ����Ҿҿ�����������ض���β���������������������������������������������������������ܲ����ڱ�����������������������٫���������������߮����������޲߽����"};
const char PY_mb_yin   []={"����ӡ����������������������������ܧ۴��ط���������������������"};
const char PY_mb_ying  []={"ӦӲӰӪӭӳӬӮӥӢӱӨӯӤӣӧӫө������������ݺ�۫�������������������"};
const char PY_mb_yo    []={"Ӵ���"};
const char PY_mb_yong  []={"��ӿ��ӵӼ��ӺӽӾӶӻӸӹӷ��ٸ��ܭ�����������"};
const char PY_mb_you   []={"��������������������������������������������٧ݬݯݵ������������������������������"};
const char PY_mb_yu    []={"������������������������������������������������������������������������������ξ����ԡԢԣԤԥԦε����������������������������������������خ��ٶ��������������������������ع������������"};
const char PY_mb_yuan  []={"ԶԱԪԺԲԭԸ԰ԮԳԹԩԴԵԬԨԷԫԧԯ��������������ܾ������ܫ��"};
const char PY_mb_yue   []={"��ԽԼԾ��������Ի˵��Կ����������"};
const char PY_mb_yun   []={"������������������������Ա�����۩ܿ����������"};
const char PY_mb_za    []={"����զ����������"};
const char PY_mb_zai   []={"��������������������"};
const char PY_mb_zan   []={"���������������������"};
const char PY_mb_zang  []={"�����߲������"};
const char PY_mb_zao   []={"������������������������������"};
const char PY_mb_ze    []={"��������զ�������������������"};
const char PY_mb_zei   []={"��"};
const char PY_mb_zen   []={"����"};
const char PY_mb_zeng  []={"����������������"};
const char PY_mb_zha   []={"��ը��բգեէ��թ����ա��߸�����������������դզ����"};
const char PY_mb_zhai  []={"ժխծիկ���լ������"};
const char PY_mb_zhan  []={"վռսյմճձչջղ��պտ��նշոհ�����"};
const char PY_mb_zhang []={"���³��������������������������������۵�����"};
const char PY_mb_zhao  []={"����������צ�׳������س�����������گ��"};
const char PY_mb_zhe   []={"����������������������������ߡ����������"};
const char PY_mb_zhen  []={"����������������������������������������������������������"};
const char PY_mb_zheng []={"��������������֤֢֣��������֡������ں�綡��"};
const char PY_mb_zhi   []={"ֱֻ֪֮��ָֽ֧֥֦��֨֩��֭֫֬��ְ֯��ֲ��ֳִֵֶַ����ֹֺ��ּ��־ֿ����������ʶ����������������������������ۤ���������������������������������ش�������μ�"};
const char PY_mb_zhong []={"�����������������������������ڣ��"};
const char PY_mb_zhou  []={"����������������������������������ݧ����������"};
const char PY_mb_zhu   []={"ס��������������������������������������������עףפ�����������������������٪�����������ۥ��������"};
const char PY_mb_zhua  []={"ץצ��"};
const char PY_mb_zhuai []={"קת"};
const char PY_mb_zhuan []={"תרש׬��׫׭�������"};
const char PY_mb_zhuang[]={"װײׯ׳׮״��ױ�����"};
const char PY_mb_zhui  []={"׷׹׺׶׸׵�������"};
const char PY_mb_zhun  []={"׼׻�����"};
const char PY_mb_zhuo  []={"׽������׾����׿��������ߪ��������پ�����"};
const char PY_mb_zi    []={"��������������֨��������������������������������������������������������"};
const char PY_mb_zong  []={"����������������������"};
const char PY_mb_zou   []={"����������۸������"};
const char PY_mb_zu    []={"����������������������"};
const char PY_mb_zuan  []={"����׬߬����"};
const char PY_mb_zui   []={"��������Ѿ���ީ"};
const char PY_mb_zun   []={"����ߤ����"};
const char PY_mb_zuo   []={"�������������������������������������"};
/*"ƴ�����뷨��ѯ���,������ĸ������(index)"*/
struct PY_index  PY_index_a[]={{"",PY_mb_a},
                                    {"i",PY_mb_ai},
                                    {"n",PY_mb_an},
                                    {"ng",PY_mb_ang},
                                    {"o",PY_mb_ao}};
struct PY_index  PY_index_b[]={{"a",PY_mb_ba},
                                    {"ai",PY_mb_bai},
                                    {"an",PY_mb_ban},
                                    {"ang",PY_mb_bang},
                                    {"ao",PY_mb_bao},
                                    {"ei",PY_mb_bei},
                                    {"en",PY_mb_ben},
                                    {"eng",PY_mb_beng},
                                    {"i",PY_mb_bi},
                                    {"ian",PY_mb_bian},
                                    {"iao",PY_mb_biao},
                                    {"ie",PY_mb_bie},
                                    {"in",PY_mb_bin},
                                    {"ing",PY_mb_bing},
                                    {"o",PY_mb_bo},
                                    {"u",PY_mb_bu}};
struct PY_index  PY_index_c[]={{"a",PY_mb_ca},
                                    {"ai",PY_mb_cai},
                                    {"an",PY_mb_can},
                                    {"ang",PY_mb_cang},
                                    {"ao",PY_mb_cao},
                                    {"e",PY_mb_ce},
                                    {"en",PY_mb_cen},
                                    {"eng",PY_mb_ceng},
                                    {"ha",PY_mb_cha},
                                    {"hai",PY_mb_chai},
                                    {"han",PY_mb_chan},
                                    {"hang",PY_mb_chang},
                                    {"hao",PY_mb_chao},
                                    {"he",PY_mb_che},
                                    {"hen",PY_mb_chen},
                                    {"heng",PY_mb_cheng},
                                    {"hi",PY_mb_chi},
                                    {"hong",PY_mb_chong},
                                    {"hou",PY_mb_chou},
                                    {"hu",PY_mb_chu},
                                    {"huai",PY_mb_chuai},
                                    {"huan",PY_mb_chuan},
                                    {"huang",PY_mb_chuang},
                                    {"hui",PY_mb_chui},
                                    {"hun",PY_mb_chun},
                                    {"huo",PY_mb_chuo},
                                    {"i",PY_mb_ci},
                                    {"ong",PY_mb_cong},
                                    {"ou",PY_mb_cou},
                                    {"u",PY_mb_cu},
                                    {"uan",PY_mb_cuan},
                                    {"ui",PY_mb_cui},
                                    {"un",PY_mb_cun},
                                    {"uo",PY_mb_cuo}};
struct PY_index  PY_index_d[]={{"a",PY_mb_da}, //��ǰΪ"a   "���޷���ʾda
                                    {"ai",PY_mb_dai},
                                    {"an",PY_mb_dan},
                                    {"ang",PY_mb_dang},
                                    {"ao",PY_mb_dao},
                                    {"e",PY_mb_de},
                                    {"ei",PY_mb_dei},
                                    {"eng",PY_mb_deng},
                                    {"i",PY_mb_di},
                                    {"ia",PY_mb_dia},
                                    {"ian",PY_mb_dian},
                                    {"iao",PY_mb_diao},
                                    {"ie",PY_mb_die},
                                    {"ing",PY_mb_ding},
                                    {"iu",PY_mb_diu},
                                    {"ong",PY_mb_dong},
                                    {"ou",PY_mb_dou},
                                    {"u",PY_mb_du},
                                    {"uan",PY_mb_duan},
                                    {"ui",PY_mb_dui},
                                    {"un",PY_mb_dun},
                                    {"uo",PY_mb_duo}};
struct PY_index  PY_index_e[]={{"",PY_mb_e},
                                    {"i",PY_mb_ei},
                                    {"n",PY_mb_en},
                                    {"r",PY_mb_er}};
struct PY_index  PY_index_f[]={{"a",PY_mb_fa},
                                    {"an",PY_mb_fan},
                                    {"ang",PY_mb_fang},
                                    {"ei",PY_mb_fei},
                                    {"en",PY_mb_fen},
                                    {"eng",PY_mb_feng},
                                    {"o",PY_mb_fo},
                                    {"ou",PY_mb_fou},
                                    {"u",PY_mb_fu}};
struct PY_index  PY_index_g[]={{"a",PY_mb_ga},
                                    {"ai",PY_mb_gai},
                                    {"an",PY_mb_gan},
                                    {"ang",PY_mb_gang},
                                    {"ao",PY_mb_gao},
                                    {"e",PY_mb_ge},
                                    {"ei",PY_mb_gei},
                                    {"en",PY_mb_gen},
                                    {"eng",PY_mb_geng},
                                    {"ong",PY_mb_gong},
                                    {"ou",PY_mb_gou},
                                    {"u",PY_mb_gu},
                                    {"ua",PY_mb_gua},
                                    {"uai",PY_mb_guai},
                                    {"uan",PY_mb_guan},
                                    {"uang",PY_mb_guang},
                                    {"ui",PY_mb_gui},
                                    {"un",PY_mb_gun},
                                    {"uo",PY_mb_guo}};
struct PY_index  PY_index_h[]={{"a",PY_mb_ha},
                                    {"ai",PY_mb_hai},
                                    {"an",PY_mb_han},
                                    {"ang",PY_mb_hang},
                                    {"ao",PY_mb_hao},
                                    {"e",PY_mb_he},
                                    {"ei",PY_mb_hei},
                                    {"en",PY_mb_hen},
                                    {"eng",PY_mb_heng},
                                    {"ong",PY_mb_hong},
                                    {"ou",PY_mb_hou},
                                    {"u",PY_mb_hu},
                                    {"ua",PY_mb_hua},
                                    {"uai",PY_mb_huai},
                                    {"uan",PY_mb_huan},
                                    {"uang",PY_mb_huang},
                                    {"ui",PY_mb_hui},
                                    {"un",PY_mb_hun},
                                    {"uo",PY_mb_huo}};
struct PY_index  PY_index_i[]={{"",PY_mb_space}};
struct PY_index  PY_index_j[]={{"i",PY_mb_ji},
                                    {"ia",PY_mb_jia},
                                    {"ian",PY_mb_jian},
                                    {"iang",PY_mb_jiang},
                                    {"iao",PY_mb_jiao},
                                    {"ie",PY_mb_jie},
                                    {"in",PY_mb_jin},
                                    {"ing",PY_mb_jing},
                                    {"iong",PY_mb_jiong},
                                    {"iu",PY_mb_jiu},
                                    {"u",PY_mb_ju},
                                    {"uan",PY_mb_juan},
                                    {"ue",PY_mb_jue},
                                    {"un",PY_mb_jun}};
struct PY_index  PY_index_k[]={{"a",PY_mb_ka},
                                    {"ai",PY_mb_kai},
                                    {"an",PY_mb_kan},
                                    {"ang",PY_mb_kang},
                                    {"ao",PY_mb_kao},
                                    {"e",PY_mb_ke},
                                    {"en",PY_mb_ken},
                                    {"eng",PY_mb_keng},
                                    {"ong",PY_mb_kong},
                                    {"ou",PY_mb_kou},
                                    {"u",PY_mb_ku},
                                    {"ua",PY_mb_kua},
                                    {"uai",PY_mb_kuai},
                                    {"uan",PY_mb_kuan},
                                    {"uang",PY_mb_kuang},
                                    {"ui",PY_mb_kui},
                                    {"un",PY_mb_kun},
                                    {"uo",PY_mb_kuo}};
struct PY_index  PY_index_l[]={{"a",PY_mb_la},
                                    {"ai",PY_mb_lai},
                                    {"an",PY_mb_lan},
                                    {"ang",PY_mb_lang},
                                    {"ao",PY_mb_lao},
                                    {"e",PY_mb_le},
                                    {"ei",PY_mb_lei},
                                    {"eng",PY_mb_leng},
                                    {"i",PY_mb_li},
                                    {"ia",PY_mb_lia},
                                    {"ian",PY_mb_lian},
                                    {"iang",PY_mb_liang},
                                    {"iao",PY_mb_liao},
                                    {"ie",PY_mb_lie},
                                    {"in",PY_mb_lin},
                                    {"ing",PY_mb_ling},
                                    {"iu",PY_mb_liu},
                                    {"o",PY_mb_lo},
                                    {"ong",PY_mb_long},
                                    {"ou",PY_mb_lou},
                                    {"u",PY_mb_lu},
                                    {"uan",PY_mb_luan},
                                    {"ue",PY_mb_lue},
                                    {"un",PY_mb_lun},
                                    {"uo",PY_mb_luo},
                                    {"v",PY_mb_lv}};
struct PY_index  PY_index_m[]={{"a",PY_mb_ma},
                                    {"ai",PY_mb_mai},
                                    {"an",PY_mb_man},
                                    {"ang",PY_mb_mang},
                                    {"ao",PY_mb_mao},
                                    {"e",PY_mb_me},
                                    {"ei",PY_mb_mei},
                                    {"en",PY_mb_men},
                                    {"eng",PY_mb_meng},
                                    {"i",PY_mb_mi},
                                    {"ian",PY_mb_mian},
                                    {"iao",PY_mb_miao},
                                    {"ie",PY_mb_mie},
                                    {"in",PY_mb_min},
                                    {"ing",PY_mb_ming},
                                    {"iu",PY_mb_miu},
                                    {"o",PY_mb_mo},
                                    {"ou",PY_mb_mou},
                                    {"u",PY_mb_mu}};
struct PY_index  PY_index_n[]={{"a",PY_mb_na},
                                    {"ai",PY_mb_nai},
                                    {"an",PY_mb_nan},
                                    {"ang",PY_mb_nang},
                                    {"ao",PY_mb_nao},
                                    {"e",PY_mb_ne},
                                    {"ei",PY_mb_nei},
                                    {"en",PY_mb_nen},
                                    {"eng",PY_mb_neng},
                                    {"g",PY_mb_ng},
                                    {"i",PY_mb_ni},
                                    {"ian",PY_mb_nian},
                                    {"iang",PY_mb_niang},
                                    {"iao",PY_mb_niao},
                                    {"ie",PY_mb_nie},
                                    {"in",PY_mb_nin},
                                    {"ing",PY_mb_ning},
                                    {"iu",PY_mb_niu},
                                    {"ong",PY_mb_nong},
                                    {"ou",PY_mb_nou},
                                    {"u",PY_mb_nu},
                                    {"uan",PY_mb_nuan},
                                    {"ue",PY_mb_nue},
                                    {"uo",PY_mb_nuo},
                                    {"v",PY_mb_nv}};
struct PY_index  PY_index_o[]={{"",PY_mb_o},
                                    {"u",PY_mb_ou}};
struct PY_index  PY_index_p[]={{"a",PY_mb_pa},
                                    {"ai",PY_mb_pai},
                                    {"an",PY_mb_pan},
                                    {"ang",PY_mb_pang},
                                    {"ao",PY_mb_pao},
                                    {"ei",PY_mb_pei},
                                    {"en",PY_mb_pen},
                                    {"eng",PY_mb_peng},
                                    {"i",PY_mb_pi},
                                    {"ian",PY_mb_pian},
                                    {"iao",PY_mb_piao},
                                    {"ie",PY_mb_pie},
                                    {"in",PY_mb_pin},
                                    {"ing",PY_mb_ping},
                                    {"o",PY_mb_po},
                                    {"ou",PY_mb_pou},
                                    {"u",PY_mb_pu}};
struct PY_index  PY_index_q[]={{"i",PY_mb_qi},
                                    {"ia",PY_mb_qia},
                                    {"ian",PY_mb_qian},
                                    {"iang",PY_mb_qiang},
                                    {"iao",PY_mb_qiao},
                                    {"ie",PY_mb_qie},
                                    {"in",PY_mb_qin},
                                    {"ing",PY_mb_qing},
                                    {"iong",PY_mb_qiong},
                                    {"iu",PY_mb_qiu},
                                    {"u",PY_mb_qu},
                                    {"uan",PY_mb_quan},
                                    {"ue",PY_mb_que},
                                    {"ui",PY_mb_qui},
                                    {"un",PY_mb_qun}};
struct PY_index  PY_index_r[]={{"an",PY_mb_ran},
                                    {"ang",PY_mb_rang},
                                    {"ao",PY_mb_rao},
                                    {"e",PY_mb_re},
                                    {"en",PY_mb_ren},
                                    {"eng",PY_mb_reng},
                                    {"i",PY_mb_ri},
                                    {"ong",PY_mb_rong},
                                    {"ou",PY_mb_rou},
                                    {"u",PY_mb_ru},
                                    {"uan",PY_mb_ruan},
                                    {"ui",PY_mb_rui},
                                    {"un",PY_mb_run},
                                    {"uo",PY_mb_ruo}};
struct PY_index  PY_index_s[]={{"a",PY_mb_sa},
                                    {"ai",PY_mb_sai},
                                    {"an",PY_mb_san},
                                    {"ang",PY_mb_sang},
                                    {"ao",PY_mb_sao},
                                    {"e",PY_mb_se},
                                    {"en",PY_mb_sen},
                                    {"eng",PY_mb_seng},
                                    {"ha",PY_mb_sha},
                                    {"hai",PY_mb_shai},
                                    {"han",PY_mb_shan},
                                    {"hang",PY_mb_shang},
                                    {"hao",PY_mb_shao},
                                    {"he",PY_mb_she},
                                    {"hei",PY_mb_shei},
                                    {"hen",PY_mb_shen},
                                    {"heng",PY_mb_sheng},
                                    {"hi",PY_mb_shi},
                                    {"hou",PY_mb_shou},
                                    {"hu",PY_mb_shu},
                                    {"hua",PY_mb_shua},
                                    {"huai",PY_mb_shuai},
                                    {"huan",PY_mb_shuan},
                                    {"huang",PY_mb_shuang},
                                    {"hui",PY_mb_shui},
                                    {"hun",PY_mb_shun},
                                    {"huo",PY_mb_shuo},
                                    {"i",PY_mb_si},
                                    {"ong",PY_mb_song},
                                    {"ou",PY_mb_sou},
                                    {"u",PY_mb_su},
                                    {"uan",PY_mb_suan},
                                    {"ui",PY_mb_sui},
                                    {"un",PY_mb_sun},
                                    {"uo",PY_mb_suo}};
struct PY_index  PY_index_t[]={{"a",PY_mb_ta},
                                    {"ai",PY_mb_tai},
                                    {"an",PY_mb_tan},
                                    {"ang",PY_mb_tang},
                                    {"ao",PY_mb_tao},
                                    {"e",PY_mb_te},
                                    {"eng",PY_mb_teng},
                                    {"i",PY_mb_ti},
                                    {"ian",PY_mb_tian},
                                    {"iao",PY_mb_tiao},
                                    {"ie",PY_mb_tie},
                                    {"ing",PY_mb_ting},
                                    {"ong",PY_mb_tong},
                                    {"ou",PY_mb_tou},
                                    {"u",PY_mb_tu},
                                    {"uan",PY_mb_tuan},
                                    {"ui",PY_mb_tui},
                                    {"un",PY_mb_tun},
                                    {"uo",PY_mb_tuo}};
struct PY_index  PY_index_u[]={{"",PY_mb_space}};
struct PY_index  PY_index_v[]={{"",PY_mb_space}};
struct PY_index  PY_index_w[]={{"a",PY_mb_wa},
                                    {"ai",PY_mb_wai},
                                    {"an",PY_mb_wan},
                                    {"ang",PY_mb_wang},
                                    {"ei",PY_mb_wei},
                                    {"en",PY_mb_wen},
                                    {"eng",PY_mb_weng},
                                    {"o",PY_mb_wo},
                                    {"u",PY_mb_wu}};
struct PY_index  PY_index_x[]={{"i",PY_mb_xi},
                                    {"ia",PY_mb_xia},
                                    {"ian",PY_mb_xian},
                                    {"iang",PY_mb_xiang},
                                    {"iao",PY_mb_xiao},
                                    {"ie",PY_mb_xie},
                                    {"in",PY_mb_xin},
                                    {"ing",PY_mb_xing},
                                    {"iong",PY_mb_xiong},
                                    {"iu",PY_mb_xiu},
                                    {"u",PY_mb_xu},
                                    {"uan",PY_mb_xuan},
                                    {"ue",PY_mb_xue},
                                    {"un",PY_mb_xun}};
struct PY_index  PY_index_y[]={{"a",PY_mb_ya},
                                    {"an",PY_mb_yan},
                                    {"ang",PY_mb_yang},
                                    {"ao",PY_mb_yao},
                                    {"e",PY_mb_ye},
                                    {"i",PY_mb_yi},
                                    {"in",PY_mb_yin},
                                    {"ing",PY_mb_ying},
                                    {"o",PY_mb_yo},
                                    {"ong",PY_mb_yong},
                                    {"ou",PY_mb_you},
                                    {"u",PY_mb_yu},
                                    {"uan",PY_mb_yuan},
                                    {"ue",PY_mb_yue},
                                    {"un",PY_mb_yun}};
struct PY_index  PY_index_z[]={{"a",PY_mb_za},
                                    {"ai",PY_mb_zai},
                                    {"an",PY_mb_zan},
                                    {"ang",PY_mb_zang},
                                    {"ao",PY_mb_zao},
                                    {"e",PY_mb_ze},
                                    {"ei",PY_mb_zei},
                                    {"en",PY_mb_zen},
                                    {"eng",PY_mb_zeng},
                                    {"ha",PY_mb_zha},
                                    {"hai",PY_mb_zhai},
                                    {"han",PY_mb_zhan},
                                    {"hang",PY_mb_zhang},
                                    {"hao",PY_mb_zhao},
                                    {"he",PY_mb_zhe},
                                    {"hen",PY_mb_zhen},
                                    {"heng",PY_mb_zheng},
                                    {"hi",PY_mb_zhi},
                                    {"hong",PY_mb_zhong},
                                    {"hou",PY_mb_zhou},
                                    {"hu",PY_mb_zhu},
                                    {"hua",PY_mb_zhua},
                                    {"huai",PY_mb_zhuai},
                                    {"huan",PY_mb_zhuan},
                                    {"huang",PY_mb_zhuang},
                                    {"hui",PY_mb_zhui},
                                    {"hun",PY_mb_zhun},
                                    {"huo",PY_mb_zhuo},
                                    {"i",PY_mb_zi},
                                    {"ong",PY_mb_zong},
                                    {"ou",PY_mb_zou},
                                    {"u",PY_mb_zu},
                                    {"uan",PY_mb_zuan},
                                    {"ui",PY_mb_zui},
                                    {"un",PY_mb_zun},
                                    {"uo",PY_mb_zuo}};
struct PY_index  PY_index_end[]={{"",PY_mb_space}};

unsigned index_number[] = {
    5, //a
    16,//b
    34,//c
    22,//d
    4, //e
    9, //f
    19,//g
    19,//h
    1, //i
    14,//j
    18,//k
    26,//l
    19,//m
    25,//n
    2, //o
    17,//p
    15,//q
    14,//r
    35,//s
    19,//t
    1, //u
    1, //v
    9, //w
    14,//x
    15,//y
    36,//z
};
/*��������ĸ������*/
struct PY_index *PY_index_headletter[]={PY_index_a,
                                        PY_index_b,
                                        PY_index_c,
                                        PY_index_d,
                                        PY_index_e,
                                        PY_index_f,
                                        PY_index_g,
                                        PY_index_h,
                                        PY_index_i,
                                        PY_index_j,
                                        PY_index_k,
                                        PY_index_l,
                                        PY_index_m,
                                        PY_index_n,
                                        PY_index_o,
                                        PY_index_p,
                                        PY_index_q,
                                        PY_index_r,
                                        PY_index_s,
                                        PY_index_t,
                                        PY_index_u,
                                        PY_index_v,
                                        PY_index_w,
                                        PY_index_x,
                                        PY_index_y,
                                        PY_index_z,
                                        PY_index_end};

const char *PYSearch(char *strInput_py_str)
{
    struct PY_index *cpHZ;
    char i, cInputStrLength;
    unsigned char count;

    cInputStrLength = strlen(strInput_py_str);        /*����ƴ��������*/
    if(*strInput_py_str == '\0') return NULL;         /*���������ַ�����0*/

    for(i = 0; i < cInputStrLength; i++)
    {
        *(strInput_py_str+i) |= 0x20;                 /*����ĸ��תΪСд*/
    }

    if(*strInput_py_str == 'i') return NULL;          /*����ƴ������*/
    if(*strInput_py_str == 'u') return NULL;
    if(*strInput_py_str == 'v') return NULL;

    cpHZ  = PY_index_headletter[strInput_py_str[0] - 'a'];              /*������ĸ����*/
    count = index_number[strInput_py_str[0] - 'a'];
//    cpHZedge = PY_index_headletter[strInput_py_str[0] - 'a' + 1];     /*����ָ�����*/
//    printf("%x, %x\n", cpHZ, cpHZedge);
    strInput_py_str++;                              /*ָ��ƴ�����ڶ�����ĸ*/

    while(count--)                                  /*����������*/
    {
        for(i = 0; i < cInputStrLength; i++)
        {
            if( *(strInput_py_str + i) != *((cpHZ->PY)+i) )
                break;                              /*������ĸ������,�˳�*/
        }
        if(i == cInputStrLength)                    /*��ĸ��ȫ��*/
        {
            return (cpHZ->PY_mb);
        }
        cpHZ++;
    }
    return NULL;                                    /*�޹�����*/
}
