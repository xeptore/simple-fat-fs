#include "constants.h"
#include "directory.h"
#include "fat.h"
#include "formatter.h"
#include "handlers.h"
#include "logger.h"
#include <stdbool.h>
#include <stdlib.h>

#ifdef APP_ENV_TEST

void __test__update_fat_entires() {
  FatTableEntry fat_table[16] = {0};
  int empty_entries[10] = {0, 2, 4, 6, 7, 8, 9, 10, 13, 14};
  update_fat_entires(fat_table, empty_entries);
  if (!(fat_table[0] == 2 && fat_table[2] == 4 && fat_table[4] == 6 &&
        fat_table[6] == 7 && fat_table[7] == 8 && fat_table[8] == 9 &&
        fat_table[9] == 10 && fat_table[10] == 13 && fat_table[13] == 14 &&
        fat_table[14] == FAT_END_OF_FILE_ENTRY)) {
    printf("Test failed.");
    return;
  }
  printf("Works fine!");
}

void __test__serialize_fat_entry_entry(const FatTableEntry entry) {
  unsigned char serialized_entry[3] = {0};
  serialize_fat_entry(entry, serialized_entry);
  const FatTableEntry deserialized = deserialize_fat_entry(serialized_entry);
  if (deserialized == entry) {
    info("WORKS FINE :)");
    return;
  }
  info("TEST FAILED :(");
}

void __test__serialize_fat_entry() {
  __test__serialize_fat_entry_entry(58876);
  __test__serialize_fat_entry_entry(312528);
  __test__serialize_fat_entry_entry(710810);
  __test__serialize_fat_entry_entry(574170);
  __test__serialize_fat_entry_entry(204488);
  __test__serialize_fat_entry_entry(66667);
  __test__serialize_fat_entry_entry(467221);
  __test__serialize_fat_entry_entry(624856);
  __test__serialize_fat_entry_entry(1001213);
  __test__serialize_fat_entry_entry(273379);
  __test__serialize_fat_entry_entry(45504);
  __test__serialize_fat_entry_entry(434414);
  __test__serialize_fat_entry_entry(300923);
  __test__serialize_fat_entry_entry(297055);
  __test__serialize_fat_entry_entry(926783);
  __test__serialize_fat_entry_entry(609626);
  __test__serialize_fat_entry_entry(1047832);
  __test__serialize_fat_entry_entry(864189);
  __test__serialize_fat_entry_entry(798903);
  __test__serialize_fat_entry_entry(479341);
  __test__serialize_fat_entry_entry(200148);
  __test__serialize_fat_entry_entry(749183);
  __test__serialize_fat_entry_entry(278051);
  __test__serialize_fat_entry_entry(537337);
  __test__serialize_fat_entry_entry(910578);
  __test__serialize_fat_entry_entry(182642);
  __test__serialize_fat_entry_entry(604821);
  __test__serialize_fat_entry_entry(467450);
  __test__serialize_fat_entry_entry(409946);
  __test__serialize_fat_entry_entry(222032);
  __test__serialize_fat_entry_entry(435589);
  __test__serialize_fat_entry_entry(727645);
  __test__serialize_fat_entry_entry(977617);
  __test__serialize_fat_entry_entry(652358);
  __test__serialize_fat_entry_entry(864024);
  __test__serialize_fat_entry_entry(535244);
  __test__serialize_fat_entry_entry(235647);
  __test__serialize_fat_entry_entry(138338);
  __test__serialize_fat_entry_entry(426934);
  __test__serialize_fat_entry_entry(256262);
  __test__serialize_fat_entry_entry(870356);
  __test__serialize_fat_entry_entry(721063);
  __test__serialize_fat_entry_entry(400356);
  __test__serialize_fat_entry_entry(346556);
  __test__serialize_fat_entry_entry(593126);
  __test__serialize_fat_entry_entry(258942);
  __test__serialize_fat_entry_entry(617921);
  __test__serialize_fat_entry_entry(220090);
  __test__serialize_fat_entry_entry(534154);
  __test__serialize_fat_entry_entry(803845);
  __test__serialize_fat_entry_entry(206760);
  __test__serialize_fat_entry_entry(1032560);
  __test__serialize_fat_entry_entry(152496);
  __test__serialize_fat_entry_entry(1019358);
  __test__serialize_fat_entry_entry(597386);
  __test__serialize_fat_entry_entry(527328);
  __test__serialize_fat_entry_entry(247195);
  __test__serialize_fat_entry_entry(51320);
  __test__serialize_fat_entry_entry(669116);
  __test__serialize_fat_entry_entry(189368);
  __test__serialize_fat_entry_entry(732437);
  __test__serialize_fat_entry_entry(404849);
  __test__serialize_fat_entry_entry(302233);
  __test__serialize_fat_entry_entry(838706);
  __test__serialize_fat_entry_entry(325657);
  __test__serialize_fat_entry_entry(483111);
  __test__serialize_fat_entry_entry(401106);
  __test__serialize_fat_entry_entry(195147);
  __test__serialize_fat_entry_entry(122299);
  __test__serialize_fat_entry_entry(357095);
  __test__serialize_fat_entry_entry(864788);
  __test__serialize_fat_entry_entry(119905);
  __test__serialize_fat_entry_entry(567460);
  __test__serialize_fat_entry_entry(995201);
  __test__serialize_fat_entry_entry(111093);
  __test__serialize_fat_entry_entry(976411);
  __test__serialize_fat_entry_entry(391154);
  __test__serialize_fat_entry_entry(699302);
  __test__serialize_fat_entry_entry(377847);
  __test__serialize_fat_entry_entry(179591);
  __test__serialize_fat_entry_entry(242224);
  __test__serialize_fat_entry_entry(395616);
  __test__serialize_fat_entry_entry(530941);
  __test__serialize_fat_entry_entry(1016279);
  __test__serialize_fat_entry_entry(1041463);
  __test__serialize_fat_entry_entry(1041297);
  __test__serialize_fat_entry_entry(875590);
  __test__serialize_fat_entry_entry(763428);
  __test__serialize_fat_entry_entry(38369);
  __test__serialize_fat_entry_entry(24684);
  __test__serialize_fat_entry_entry(999795);
  __test__serialize_fat_entry_entry(598277);
  __test__serialize_fat_entry_entry(30346);
  __test__serialize_fat_entry_entry(170644);
  __test__serialize_fat_entry_entry(735410);
  __test__serialize_fat_entry_entry(927857);
  __test__serialize_fat_entry_entry(51859);
  __test__serialize_fat_entry_entry(645533);
  __test__serialize_fat_entry_entry(573904);
  __test__serialize_fat_entry_entry(998998);
  __test__serialize_fat_entry_entry(746269);
  __test__serialize_fat_entry_entry(476565);
  __test__serialize_fat_entry_entry(1045813);
  __test__serialize_fat_entry_entry(171225);
  __test__serialize_fat_entry_entry(105239);
  __test__serialize_fat_entry_entry(112501);
  __test__serialize_fat_entry_entry(521549);
  __test__serialize_fat_entry_entry(655152);
  __test__serialize_fat_entry_entry(614392);
  __test__serialize_fat_entry_entry(15534);
  __test__serialize_fat_entry_entry(1045935);
  __test__serialize_fat_entry_entry(805899);
  __test__serialize_fat_entry_entry(284446);
  __test__serialize_fat_entry_entry(866165);
  __test__serialize_fat_entry_entry(803448);
  __test__serialize_fat_entry_entry(324885);
  __test__serialize_fat_entry_entry(744164);
  __test__serialize_fat_entry_entry(642588);
  __test__serialize_fat_entry_entry(135323);
  __test__serialize_fat_entry_entry(698780);
  __test__serialize_fat_entry_entry(727122);
  __test__serialize_fat_entry_entry(1030326);
  __test__serialize_fat_entry_entry(601349);
  __test__serialize_fat_entry_entry(128218);
  __test__serialize_fat_entry_entry(642217);
  __test__serialize_fat_entry_entry(283223);
  __test__serialize_fat_entry_entry(517010);
  __test__serialize_fat_entry_entry(698270);
  __test__serialize_fat_entry_entry(450082);
  __test__serialize_fat_entry_entry(996684);
  __test__serialize_fat_entry_entry(367214);
  __test__serialize_fat_entry_entry(32867);
  __test__serialize_fat_entry_entry(573338);
  __test__serialize_fat_entry_entry(644965);
  __test__serialize_fat_entry_entry(871025);
  __test__serialize_fat_entry_entry(981217);
  __test__serialize_fat_entry_entry(1042036);
  __test__serialize_fat_entry_entry(361999);
  __test__serialize_fat_entry_entry(240811);
  __test__serialize_fat_entry_entry(810126);
  __test__serialize_fat_entry_entry(400246);
  __test__serialize_fat_entry_entry(591137);
  __test__serialize_fat_entry_entry(756185);
  __test__serialize_fat_entry_entry(466698);
  __test__serialize_fat_entry_entry(587062);
  __test__serialize_fat_entry_entry(446342);
  __test__serialize_fat_entry_entry(352332);
  __test__serialize_fat_entry_entry(796309);
  __test__serialize_fat_entry_entry(434385);
  __test__serialize_fat_entry_entry(747993);
  __test__serialize_fat_entry_entry(645409);
  __test__serialize_fat_entry_entry(428707);
  __test__serialize_fat_entry_entry(571506);
  __test__serialize_fat_entry_entry(97799);
  __test__serialize_fat_entry_entry(295083);
  __test__serialize_fat_entry_entry(303986);
  __test__serialize_fat_entry_entry(183600);
  __test__serialize_fat_entry_entry(1010089);
  __test__serialize_fat_entry_entry(521141);
  __test__serialize_fat_entry_entry(167119);
  __test__serialize_fat_entry_entry(374638);
  __test__serialize_fat_entry_entry(473422);
  __test__serialize_fat_entry_entry(931657);
  __test__serialize_fat_entry_entry(656695);
  __test__serialize_fat_entry_entry(530702);
  __test__serialize_fat_entry_entry(371790);
  __test__serialize_fat_entry_entry(1014345);
  __test__serialize_fat_entry_entry(869897);
  __test__serialize_fat_entry_entry(403480);
  __test__serialize_fat_entry_entry(324719);
  __test__serialize_fat_entry_entry(974468);
  __test__serialize_fat_entry_entry(1038569);
  __test__serialize_fat_entry_entry(1012691);
  __test__serialize_fat_entry_entry(17734);
  __test__serialize_fat_entry_entry(29794);
  __test__serialize_fat_entry_entry(634427);
  __test__serialize_fat_entry_entry(811107);
  __test__serialize_fat_entry_entry(608236);
  __test__serialize_fat_entry_entry(166151);
  __test__serialize_fat_entry_entry(713916);
  __test__serialize_fat_entry_entry(345571);
  __test__serialize_fat_entry_entry(245729);
  __test__serialize_fat_entry_entry(471759);
  __test__serialize_fat_entry_entry(727575);
  __test__serialize_fat_entry_entry(626603);
  __test__serialize_fat_entry_entry(609044);
  __test__serialize_fat_entry_entry(687068);
  __test__serialize_fat_entry_entry(468998);
  __test__serialize_fat_entry_entry(13620);
  __test__serialize_fat_entry_entry(157329);
  __test__serialize_fat_entry_entry(616470);
  __test__serialize_fat_entry_entry(660908);
  __test__serialize_fat_entry_entry(865394);
  __test__serialize_fat_entry_entry(968099);
  __test__serialize_fat_entry_entry(646299);
  __test__serialize_fat_entry_entry(11374);
  __test__serialize_fat_entry_entry(1045540);
  __test__serialize_fat_entry_entry(407221);
  __test__serialize_fat_entry_entry(98882);
  __test__serialize_fat_entry_entry(242770);
  __test__serialize_fat_entry_entry(926158);
  __test__serialize_fat_entry_entry(788019);
  __test__serialize_fat_entry_entry(893596);
  __test__serialize_fat_entry_entry(9047);
  __test__serialize_fat_entry_entry(942844);
  __test__serialize_fat_entry_entry(456294);
  __test__serialize_fat_entry_entry(547940);
  __test__serialize_fat_entry_entry(237839);
  __test__serialize_fat_entry_entry(588009);
  __test__serialize_fat_entry_entry(1011761);
  __test__serialize_fat_entry_entry(53107);
  __test__serialize_fat_entry_entry(10842);
  __test__serialize_fat_entry_entry(344388);
  __test__serialize_fat_entry_entry(478175);
  __test__serialize_fat_entry_entry(156456);
  __test__serialize_fat_entry_entry(776209);
  __test__serialize_fat_entry_entry(85263);
  __test__serialize_fat_entry_entry(455383);
  __test__serialize_fat_entry_entry(31809);
  __test__serialize_fat_entry_entry(745392);
  __test__serialize_fat_entry_entry(516967);
  __test__serialize_fat_entry_entry(365696);
  __test__serialize_fat_entry_entry(620853);
  __test__serialize_fat_entry_entry(443950);
  __test__serialize_fat_entry_entry(932690);
  __test__serialize_fat_entry_entry(264098);
  __test__serialize_fat_entry_entry(395555);
  __test__serialize_fat_entry_entry(196172);
  __test__serialize_fat_entry_entry(307209);
  __test__serialize_fat_entry_entry(746933);
  __test__serialize_fat_entry_entry(754394);
  __test__serialize_fat_entry_entry(646270);
  __test__serialize_fat_entry_entry(570831);
  __test__serialize_fat_entry_entry(31616);
  __test__serialize_fat_entry_entry(7082);
  __test__serialize_fat_entry_entry(37949);
  __test__serialize_fat_entry_entry(168445);
  __test__serialize_fat_entry_entry(418974);
  __test__serialize_fat_entry_entry(467251);
  __test__serialize_fat_entry_entry(981445);
  __test__serialize_fat_entry_entry(305852);
  __test__serialize_fat_entry_entry(1034222);
  __test__serialize_fat_entry_entry(1042565);
  __test__serialize_fat_entry_entry(36649);
  __test__serialize_fat_entry_entry(595552);
  __test__serialize_fat_entry_entry(543654);
  __test__serialize_fat_entry_entry(565810);
  __test__serialize_fat_entry_entry(882161);
  __test__serialize_fat_entry_entry(684922);
  __test__serialize_fat_entry_entry(15152);
  __test__serialize_fat_entry_entry(556910);
  __test__serialize_fat_entry_entry(1022476);
  __test__serialize_fat_entry_entry(677645);
  __test__serialize_fat_entry_entry(21922);
  __test__serialize_fat_entry_entry(857865);
  __test__serialize_fat_entry_entry(711978);
  __test__serialize_fat_entry_entry(917630);
  __test__serialize_fat_entry_entry(146124);
  __test__serialize_fat_entry_entry(490190);
  __test__serialize_fat_entry_entry(767143);
}

#endif

int main() {
  // FIXME: check whether partition exists or not.
  // if does not exist, create it first.

  // format_partition();
  // format_directory();

  // FatTableEntry fat_table[FAT_ENTRIES] = {0};
  // load_fat_table(fat_table);

  // DirectoryFile directory_file = load_directory_file();
  // return handle_new_filename(&directory_file, fat_table);
}
