DROP TABLE IF EXISTS `mod_auctionator_market_price`;
CREATE TABLE IF NOT EXISTS `mod_auctionator_market_price` (
  `entry` int NOT NULL,
  `average_price` int DEFAULT NULL,
  `buyout` int DEFAULT NULL,
  `bid` int DEFAULT NULL,
  `count` int DEFAULT NULL,
  `scan_datetime` datetime DEFAULT NULL,
  `comments` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`entry`),
  KEY `entry` (`entry`,`scan_datetime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

DELETE FROM `mod_auctionator_market_price`;
INSERT INTO `mod_auctionator_market_price` (`entry`, `average_price`, `buyout`, `bid`, `count`, `scan_datetime`, `comments`) VALUES
	(118, 7, 0, 0, 0, '2024-01-10 00:00:00', 'Minor Healing Potion'),
	(723, 542, 0, 0, 0, '2024-01-10 00:00:00', 'Goretusk Liver'),
	(729, 690, 0, 0, 0, '2024-01-10 00:00:00', 'Stringy Vulture Meat'),
	(730, 24, 0, 0, 0, '2024-01-10 00:00:00', 'Murloc Eye'),
	(731, 73, 0, 0, 0, '2024-01-10 00:00:00', 'Goretusk Snout'),
	(765, 13, 0, 0, 0, '2024-01-10 00:00:00', 'Silverleaf'),
	(769, 27, 0, 0, 0, '2024-01-10 00:00:00', 'Chunk of Boar Meat'),
	(774, 17, 0, 0, 0, '2024-01-10 00:00:00', 'Malachite'),
	(783, 59, 0, 0, 0, '2024-01-10 00:00:00', 'Light Hide'),
	(814, 110, 0, 0, 0, '2024-01-10 00:00:00', 'Flask of Oil'),
	(818, 1089, 0, 0, 0, '2024-01-10 00:00:00', 'Tigerseye'),
	(1015, 366, 0, 0, 0, '2024-01-10 00:00:00', 'Lean Wolf Flank'),
	(1080, 1099, 0, 0, 0, '2024-01-10 00:00:00', 'Tough Condor Meat'),
	(1081, 90, 0, 0, 0, '2024-01-10 00:00:00', 'Crisp Spider Meat'),
	(1206, 6302, 0, 0, 0, '2024-01-10 00:00:00', 'Moss Agate'),
	(1210, 274, 0, 0, 0, '2024-01-10 00:00:00', 'Shadowgem'),
	(1288, 2999, 0, 0, 0, '2024-01-10 00:00:00', 'Large Venom Sac'),
	(1468, 62, 0, 0, 0, '2024-01-10 00:00:00', 'Murloc Fin'),
	(1475, 152, 0, 0, 0, '2024-01-10 00:00:00', 'Small Venom Sac'),
	(1529, 1986, 0, 0, 0, '2024-01-10 00:00:00', 'Jade'),
	(1705, 1395, 0, 0, 0, '2024-01-10 00:00:00', 'Lesser Moonstone'),
	(2251, 211, 0, 0, 0, '2024-01-10 00:00:00', 'Gooey Spider Leg'),
	(2312, 3788, 0, 0, 0, '2024-01-10 00:00:00', 'Fine Leather Gloves'),
	(2318, 24, 0, 0, 0, '2024-01-10 00:00:00', 'Light Leather'),
	(2319, 161, 0, 0, 0, '2024-01-10 00:00:00', 'Medium Leather'),
	(2447, 7, 0, 0, 0, '2024-01-10 00:00:00', 'Peacebloom'),
	(2449, 251, 0, 0, 0, '2024-01-10 00:00:00', 'Earthroot'),
	(2450, 525, 0, 0, 0, '2024-01-10 00:00:00', 'Briarthorn'),
	(2452, 177, 0, 0, 0, '2024-01-10 00:00:00', 'Swiftthistle'),
	(2453, 523, 0, 0, 0, '2024-01-10 00:00:00', 'Bruiseweed'),
	(2457, 3337, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Minor Agility'),
	(2459, 2887, 0, 0, 0, '2024-01-10 00:00:00', 'Swiftness Potion'),
	(2589, 36, 0, 0, 0, '2024-01-10 00:00:00', 'Linen Cloth'),
	(2592, 276, 0, 0, 0, '2024-01-10 00:00:00', 'Wool Cloth'),
	(2672, 195, 0, 0, 0, '2024-01-10 00:00:00', 'Stringy Wolf Meat'),
	(2673, 241, 0, 0, 0, '2024-01-10 00:00:00', 'Coyote Meat'),
	(2674, 120, 0, 0, 0, '2024-01-10 00:00:00', 'Crawler Meat'),
	(2677, 84, 0, 0, 0, '2024-01-10 00:00:00', 'Boar Ribs'),
	(2770, 109, 0, 0, 0, '2024-01-10 00:00:00', 'Copper Ore'),
	(2771, 243, 0, 0, 0, '2024-01-10 00:00:00', 'Tin Ore'),
	(2772, 762, 0, 0, 0, '2024-01-10 00:00:00', 'Iron Ore'),
	(2775, 1887, 0, 0, 0, '2024-01-10 00:00:00', 'Silver Ore'),
	(2776, 1190, 0, 0, 0, '2024-01-10 00:00:00', 'Gold Ore'),
	(2835, 20, 0, 0, 0, '2024-01-10 00:00:00', 'Rough Stone'),
	(2836, 618, 0, 0, 0, '2024-01-10 00:00:00', 'Coarse Stone'),
	(2838, 960, 0, 0, 0, '2024-01-10 00:00:00', 'Heavy Stone'),
	(2840, 123, 0, 0, 0, '2024-01-10 00:00:00', 'Copper Bar'),
	(2841, 497, 0, 0, 0, '2024-01-10 00:00:00', 'Bronze Bar'),
	(2842, 435, 0, 0, 0, '2024-01-10 00:00:00', 'Silver Bar'),
	(2886, 22, 0, 0, 0, '2024-01-10 00:00:00', 'Crag Boar Rib'),
	(2924, 212, 0, 0, 0, '2024-01-10 00:00:00', 'Crocolisk Meat'),
	(2934, 7, 0, 0, 0, '2024-01-10 00:00:00', 'Ruined Leather Scraps'),
	(2996, 67, 0, 0, 0, '2024-01-10 00:00:00', 'Bolt of Linen Cloth'),
	(2997, 845, 0, 0, 0, '2024-01-10 00:00:00', 'Bolt of Woolen Cloth'),
	(3164, 3019, 0, 0, 0, '2024-01-10 00:00:00', 'Discolored Worg Heart'),
	(3172, 30, 0, 0, 0, '2024-01-10 00:00:00', 'Boar Intestines'),
	(3173, 85, 0, 0, 0, '2024-01-10 00:00:00', 'Bear Meat'),
	(3174, 45, 0, 0, 0, '2024-01-10 00:00:00', 'Spider Ichor'),
	(3182, 1180, 0, 0, 0, '2024-01-10 00:00:00', 'Spider\'s Silk'),
	(3355, 4995, 0, 0, 0, '2024-01-10 00:00:00', 'Wild Steelbloom'),
	(3356, 99, 0, 0, 0, '2024-01-10 00:00:00', 'Kingsblood'),
	(3357, 946, 0, 0, 0, '2024-01-10 00:00:00', 'Liferoot'),
	(3358, 632, 0, 0, 0, '2024-01-10 00:00:00', 'Khadgar\'s Whisker'),
	(3369, 3999, 0, 0, 0, '2024-01-10 00:00:00', 'Grave Moss'),
	(3383, 450, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Wisdom'),
	(3389, 6333, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Defense'),
	(3390, 9544, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Lesser Agility'),
	(3391, 1696, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Ogre\'s Strength'),
	(3404, 752, 0, 0, 0, '2024-01-10 00:00:00', 'Buzzard Wing'),
	(3470, 24, 0, 0, 0, '2024-01-10 00:00:00', 'Rough Grinding Stone'),
	(3478, 2962, 0, 0, 0, '2024-01-10 00:00:00', 'Coarse Grinding Stone'),
	(3486, 8394, 0, 0, 0, '2024-01-10 00:00:00', 'Heavy Grinding Stone'),
	(3575, 1316, 0, 0, 0, '2024-01-10 00:00:00', 'Iron Bar'),
	(3576, 336, 0, 0, 0, '2024-01-10 00:00:00', 'Tin Bar'),
	(3577, 992, 0, 0, 0, '2024-01-10 00:00:00', 'Gold Bar'),
	(3667, 74, 0, 0, 0, '2024-01-10 00:00:00', 'Tender Crocolisk Meat'),
	(3685, 312, 0, 0, 0, '2024-01-10 00:00:00', 'Raptor Egg'),
	(3712, 276, 0, 0, 0, '2024-01-10 00:00:00', 'Turtle Meat'),
	(3730, 515, 0, 0, 0, '2024-01-10 00:00:00', 'Big Bear Meat'),
	(3731, 846, 0, 0, 0, '2024-01-10 00:00:00', 'Lion Meat'),
	(3818, 2613, 0, 0, 0, '2024-01-10 00:00:00', 'Fadeleaf'),
	(3819, 2789, 0, 0, 0, '2024-01-10 00:00:00', 'Wintersbite'),
	(3820, 300, 0, 0, 0, '2024-01-10 00:00:00', 'Stranglekelp'),
	(3821, 3890, 0, 0, 0, '2024-01-10 00:00:00', 'Goldthorn'),
	(3823, 6999, 0, 0, 0, '2024-01-10 00:00:00', 'Lesser Invisibility Potion'),
	(3824, 14935, 0, 0, 0, '2024-01-10 00:00:00', 'Shadow Oil'),
	(3829, 15187, 0, 0, 0, '2024-01-10 00:00:00', 'Frost Oil'),
	(3858, 1801, 0, 0, 0, '2024-01-10 00:00:00', 'Mithril Ore'),
	(3859, 2998, 0, 0, 0, '2024-01-10 00:00:00', 'Steel Bar'),
	(3860, 2195, 0, 0, 0, '2024-01-10 00:00:00', 'Mithril Bar'),
	(3864, 1693, 0, 0, 0, '2024-01-10 00:00:00', 'Citrine'),
	(4096, 662, 0, 0, 0, '2024-01-10 00:00:00', 'Coarse Gorilla Hair'),
	(4231, 944, 0, 0, 0, '2024-01-10 00:00:00', 'Cured Light Hide'),
	(4232, 582, 0, 0, 0, '2024-01-10 00:00:00', 'Medium Hide'),
	(4233, 1384, 0, 0, 0, '2024-01-10 00:00:00', 'Cured Medium Hide'),
	(4234, 869, 0, 0, 0, '2024-01-10 00:00:00', 'Heavy Leather'),
	(4235, 711, 0, 0, 0, '2024-01-10 00:00:00', 'Heavy Hide'),
	(4236, 2587, 0, 0, 0, '2024-01-10 00:00:00', 'Cured Heavy Hide'),
	(4243, 4665, 0, 0, 0, '2024-01-10 00:00:00', 'Fine Leather Tunic'),
	(4304, 545, 0, 0, 0, '2024-01-10 00:00:00', 'Thick Leather'),
	(4305, 1896, 0, 0, 0, '2024-01-10 00:00:00', 'Bolt of Silk Cloth'),
	(4306, 215, 0, 0, 0, '2024-01-10 00:00:00', 'Silk Cloth'),
	(4337, 753, 0, 0, 0, '2024-01-10 00:00:00', 'Thick Spider\'s Silk'),
	(4338, 400, 0, 0, 0, '2024-01-10 00:00:00', 'Mageweave Cloth'),
	(4339, 3859, 0, 0, 0, '2024-01-10 00:00:00', 'Bolt of Mageweave'),
	(4357, 83, 0, 0, 0, '2024-01-10 00:00:00', 'Rough Blasting Powder'),
	(4359, 280, 0, 0, 0, '2024-01-10 00:00:00', 'Handful of Copper Bolts'),
	(4361, 244, 0, 0, 0, '2024-01-10 00:00:00', 'Copper Tube'),
	(4363, 320, 0, 0, 0, '2024-01-10 00:00:00', 'Copper Modulator'),
	(4364, 450, 0, 0, 0, '2024-01-10 00:00:00', 'Coarse Blasting Powder'),
	(4368, 1457, 0, 0, 0, '2024-01-10 00:00:00', 'Flying Tiger Goggles'),
	(4371, 1168, 0, 0, 0, '2024-01-10 00:00:00', 'Bronze Tube'),
	(4375, 578, 0, 0, 0, '2024-01-10 00:00:00', 'Whirring Bronze Gizmo'),
	(4377, 2246, 0, 0, 0, '2024-01-10 00:00:00', 'Heavy Blasting Powder'),
	(4382, 3070, 0, 0, 0, '2024-01-10 00:00:00', 'Bronze Framework'),
	(4387, 2245, 0, 0, 0, '2024-01-10 00:00:00', 'Iron Strut'),
	(4402, 3999, 0, 0, 0, '2024-01-10 00:00:00', 'Small Flame Sac'),
	(4404, 40, 0, 0, 0, '2024-01-10 00:00:00', 'Silver Contact'),
	(4461, 211, 0, 0, 0, '2024-01-10 00:00:00', 'Raptor Hide'),
	(4589, 1176, 0, 0, 0, '2024-01-10 00:00:00', 'Long Elegant Feather'),
	(4603, 556, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Spotted Yellowtail'),
	(4611, 7720, 0, 0, 0, '2024-01-10 00:00:00', 'Blue Pearl'),
	(4625, 1786, 0, 0, 0, '2024-01-10 00:00:00', 'Firebloom'),
	(4655, 540, 0, 0, 0, '2024-01-10 00:00:00', 'Giant Clam Meat'),
	(5051, 25, 0, 0, 0, '2024-01-10 00:00:00', 'Dig Rat'),
	(5082, 90, 0, 0, 0, '2024-01-10 00:00:00', 'Thin Kodo Leather'),
	(5116, 320, 0, 0, 0, '2024-01-10 00:00:00', 'Long Tail Feather'),
	(5373, 598, 0, 0, 0, '2024-01-10 00:00:00', 'Lucky Charm'),
	(5465, 20, 0, 0, 0, '2024-01-10 00:00:00', 'Small Spider Leg'),
	(5466, 15, 0, 0, 0, '2024-01-10 00:00:00', 'Scorpid Stinger'),
	(5467, 437, 0, 0, 0, '2024-01-10 00:00:00', 'Kodo Meat'),
	(5468, 335, 0, 0, 0, '2024-01-10 00:00:00', 'Soft Frenzy Flesh'),
	(5469, 1799, 0, 0, 0, '2024-01-10 00:00:00', 'Strider Meat'),
	(5470, 3493, 0, 0, 0, '2024-01-10 00:00:00', 'Thunder Lizard Tail'),
	(5471, 327, 0, 0, 0, '2024-01-10 00:00:00', 'Stag Meat'),
	(5498, 233, 0, 0, 0, '2024-01-10 00:00:00', 'Small Lustrous Pearl'),
	(5500, 4125, 0, 0, 0, '2024-01-10 00:00:00', 'Iridescent Pearl'),
	(5503, 70, 0, 0, 0, '2024-01-10 00:00:00', 'Clam Meat'),
	(5504, 36, 0, 0, 0, '2024-01-10 00:00:00', 'Tangy Clam Meat'),
	(5633, 1879, 0, 0, 0, '2024-01-10 00:00:00', 'Great Rage Potion'),
	(5635, 293, 0, 0, 0, '2024-01-10 00:00:00', 'Sharp Claw'),
	(5636, 1213, 0, 0, 0, '2024-01-10 00:00:00', 'Delicate Feather'),
	(5637, 5095, 0, 0, 0, '2024-01-10 00:00:00', 'Large Fang'),
	(5784, 403, 0, 0, 0, '2024-01-10 00:00:00', 'Slimy Murloc Scale'),
	(5785, 796, 0, 0, 0, '2024-01-10 00:00:00', 'Thick Murloc Scale'),
	(5966, 13577, 0, 0, 0, '2024-01-10 00:00:00', 'Guardian Gloves'),
	(6037, 11494, 0, 0, 0, '2024-01-10 00:00:00', 'Truesilver Bar'),
	(6048, 5994, 0, 0, 0, '2024-01-10 00:00:00', 'Shadow Protection Potion'),
	(6289, 21, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Longjaw Mud Snapper'),
	(6291, 60, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Brilliant Smallfish'),
	(6303, 13, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Slitherskin Mackerel'),
	(6308, 45, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Bristle Whisker Catfish'),
	(6317, 52, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Loch Frenzy'),
	(6358, 382, 0, 0, 0, '2024-01-10 00:00:00', 'Oily Blackmouth'),
	(6359, 222, 0, 0, 0, '2024-01-10 00:00:00', 'Firefin Snapper'),
	(6361, 26, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Rainbow Fin Albacore'),
	(6362, 7, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Rockscale Cod'),
	(6370, 2171, 0, 0, 0, '2024-01-10 00:00:00', 'Blackmouth Oil'),
	(6371, 909, 0, 0, 0, '2024-01-10 00:00:00', 'Fire Oil'),
	(6470, 512, 0, 0, 0, '2024-01-10 00:00:00', 'Deviate Scale'),
	(6471, 555, 0, 0, 0, '2024-01-10 00:00:00', 'Perfect Deviate Scale'),
	(6522, 8452, 0, 0, 0, '2024-01-10 00:00:00', 'Deviate Fish'),
	(6889, 19, 0, 0, 0, '2024-01-10 00:00:00', 'Small Egg'),
	(7067, 15712, 0, 0, 0, '2024-01-10 00:00:00', 'Elemental Earth'),
	(7068, 7885, 0, 0, 0, '2024-01-10 00:00:00', 'Elemental Fire'),
	(7069, 1918, 0, 0, 0, '2024-01-10 00:00:00', 'Elemental Air'),
	(7070, 5230, 0, 0, 0, '2024-01-10 00:00:00', 'Elemental Water'),
	(7071, 2198, 0, 0, 0, '2024-01-10 00:00:00', 'Iron Buckle'),
	(7072, 150, 0, 0, 0, '2024-01-10 00:00:00', 'Naga Scale'),
	(7075, 3435, 0, 0, 0, '2024-01-10 00:00:00', 'Core of Earth'),
	(7076, 160000, 0, 0, 0, '2024-01-10 00:00:00', 'Essence of Earth'),
	(7077, 4441, 0, 0, 0, '2024-01-10 00:00:00', 'Heart of Fire'),
	(7078, 134482, 0, 0, 0, '2024-01-10 00:00:00', 'Essence of Fire'),
	(7079, 2166, 0, 0, 0, '2024-01-10 00:00:00', 'Globe of Water'),
	(7080, 69945, 0, 0, 0, '2024-01-10 00:00:00', 'Essence of Water'),
	(7081, 5111, 0, 0, 0, '2024-01-10 00:00:00', 'Breath of Wind'),
	(7082, 127424, 0, 0, 0, '2024-01-10 00:00:00', 'Essence of Air'),
	(7191, 1994, 0, 0, 0, '2024-01-10 00:00:00', 'Fused Wiring'),
	(7286, 100, 0, 0, 0, '2024-01-10 00:00:00', 'Black Whelp Scale'),
	(7287, 797, 0, 0, 0, '2024-01-10 00:00:00', 'Red Whelp Scale'),
	(7387, 19497, 0, 0, 0, '2024-01-10 00:00:00', 'Dusky Belt'),
	(7392, 3492, 0, 0, 0, '2024-01-10 00:00:00', 'Green Whelp Scale'),
	(7428, 739, 0, 0, 0, '2024-01-10 00:00:00', 'Shadowcat Hide'),
	(7909, 6520, 0, 0, 0, '2024-01-10 00:00:00', 'Aquamarine'),
	(7910, 592, 0, 0, 0, '2024-01-10 00:00:00', 'Star Ruby'),
	(7911, 1796, 0, 0, 0, '2024-01-10 00:00:00', 'Truesilver Ore'),
	(7912, 12495, 0, 0, 0, '2024-01-10 00:00:00', 'Solid Stone'),
	(7966, 1647, 0, 0, 0, '2024-01-10 00:00:00', 'Solid Grinding Stone'),
	(7971, 2289, 0, 0, 0, '2024-01-10 00:00:00', 'Black Pearl'),
	(7972, 985, 0, 0, 0, '2024-01-10 00:00:00', 'Ichor of Undeath'),
	(7974, 134, 0, 0, 0, '2024-01-10 00:00:00', 'Zesty Clam Meat'),
	(8146, 3627, 0, 0, 0, '2024-01-10 00:00:00', 'Wicked Claw'),
	(8150, 496, 0, 0, 0, '2024-01-10 00:00:00', 'Deeprock Salt'),
	(8151, 331, 0, 0, 0, '2024-01-10 00:00:00', 'Flask of Mojo'),
	(8152, 1181, 0, 0, 0, '2024-01-10 00:00:00', 'Flask of Big Mojo'),
	(8153, 197, 0, 0, 0, '2024-01-10 00:00:00', 'Wildvine'),
	(8154, 3993, 0, 0, 0, '2024-01-10 00:00:00', 'Scorpid Scale'),
	(8165, 562, 0, 0, 0, '2024-01-10 00:00:00', 'Worn Dragonscale'),
	(8167, 2894, 0, 0, 0, '2024-01-10 00:00:00', 'Turtle Scale'),
	(8168, 1065, 0, 0, 0, '2024-01-10 00:00:00', 'Jet Black Feather'),
	(8169, 7399, 0, 0, 0, '2024-01-10 00:00:00', 'Thick Hide'),
	(8170, 238, 0, 0, 0, '2024-01-10 00:00:00', 'Rugged Leather'),
	(8171, 94394, 0, 0, 0, '2024-01-10 00:00:00', 'Rugged Hide'),
	(8172, 9230, 0, 0, 0, '2024-01-10 00:00:00', 'Cured Thick Hide'),
	(8365, 385, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Mithril Head Trout'),
	(8368, 1979, 0, 0, 0, '2024-01-10 00:00:00', 'Thick Wolfhide'),
	(8831, 997, 0, 0, 0, '2024-01-10 00:00:00', 'Purple Lotus'),
	(8836, 1123, 0, 0, 0, '2024-01-10 00:00:00', 'Arthas\' Tears'),
	(8838, 1987, 0, 0, 0, '2024-01-10 00:00:00', 'Sungrass'),
	(8839, 4084, 0, 0, 0, '2024-01-10 00:00:00', 'Blindweed'),
	(8845, 3427, 0, 0, 0, '2024-01-10 00:00:00', 'Ghost Mushroom'),
	(8846, 6960, 0, 0, 0, '2024-01-10 00:00:00', 'Gromsblood'),
	(8949, 5976, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Agility'),
	(8951, 10121, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Greater Defense'),
	(9060, 39683, 0, 0, 0, '2024-01-10 00:00:00', 'Inlaid Mithril Cylinder'),
	(9061, 14176, 0, 0, 0, '2024-01-10 00:00:00', 'Goblin Rocket Fuel'),
	(9210, 13223, 0, 0, 0, '2024-01-10 00:00:00', 'Ghost Dye'),
	(9224, 11792, 0, 0, 0, '2024-01-10 00:00:00', 'Elixir of Demonslaying'),
	(10285, 1080, 0, 0, 0, '2024-01-10 00:00:00', 'Shadow Silk'),
	(10286, 1252, 0, 0, 0, '2024-01-10 00:00:00', 'Heart of the Wild'),
	(10502, 199999, 0, 0, 0, '2024-01-10 00:00:00', 'Spellpower Goggles Xtreme'),
	(10505, 1189, 0, 0, 0, '2024-01-10 00:00:00', 'Solid Blasting Powder'),
	(10507, 1900, 0, 0, 0, '2024-01-10 00:00:00', 'Solid Dynamite'),
	(10546, 28771, 0, 0, 0, '2024-01-10 00:00:00', 'Deadly Scope'),
	(10558, 796, 0, 0, 0, '2024-01-10 00:00:00', 'Gold Power Core'),
	(10559, 5142, 0, 0, 0, '2024-01-10 00:00:00', 'Mithril Tube'),
	(10560, 5555, 0, 0, 0, '2024-01-10 00:00:00', 'Unstable Trigger'),
	(10561, 10564, 0, 0, 0, '2024-01-10 00:00:00', 'Mithril Casing'),
	(10577, 120482, 0, 0, 0, '2024-01-10 00:00:00', 'Goblin Mortar'),
	(10592, 2069, 0, 0, 0, '2024-01-10 00:00:00', 'Catseye Elixir'),
	(10620, 1868, 0, 0, 0, '2024-01-10 00:00:00', 'Thorium Ore'),
	(10938, 494, 0, 0, 0, '2024-01-10 00:00:00', 'Lesser Magic Essence'),
	(10939, 1722, 0, 0, 0, '2024-01-10 00:00:00', 'Greater Magic Essence'),
	(10940, 273, 0, 0, 0, '2024-01-10 00:00:00', 'Strange Dust'),
	(10978, 989, 0, 0, 0, '2024-01-10 00:00:00', 'Small Glimmering Shard'),
	(10998, 967, 0, 0, 0, '2024-01-10 00:00:00', 'Lesser Astral Essence'),
	(11082, 5442, 0, 0, 0, '2024-01-10 00:00:00', 'Greater Astral Essence'),
	(11083, 1991, 0, 0, 0, '2024-01-10 00:00:00', 'Soul Dust'),
	(11084, 3337, 0, 0, 0, '2024-01-10 00:00:00', 'Large Glimmering Shard'),
	(11099, 6001, 0, 0, 0, '2024-01-10 00:00:00', 'Dark Iron Ore'),
	(11134, 1438, 0, 0, 0, '2024-01-10 00:00:00', 'Lesser Mystic Essence'),
	(11135, 4285, 0, 0, 0, '2024-01-10 00:00:00', 'Greater Mystic Essence'),
	(11137, 991, 0, 0, 0, '2024-01-10 00:00:00', 'Vision Dust'),
	(11138, 5499, 0, 0, 0, '2024-01-10 00:00:00', 'Small Glowing Shard'),
	(11139, 28999, 0, 0, 0, '2024-01-10 00:00:00', 'Large Glowing Shard'),
	(11174, 6990, 0, 0, 0, '2024-01-10 00:00:00', 'Lesser Nether Essence'),
	(11175, 22613, 0, 0, 0, '2024-01-10 00:00:00', 'Greater Nether Essence'),
	(11176, 4964, 0, 0, 0, '2024-01-10 00:00:00', 'Dream Dust'),
	(11177, 54335, 0, 0, 0, '2024-01-10 00:00:00', 'Small Radiant Shard'),
	(11178, 53715, 0, 0, 0, '2024-01-10 00:00:00', 'Large Radiant Shard'),
	(11184, 755, 0, 0, 0, '2024-01-10 00:00:00', 'Blue Power Crystal'),
	(11185, 634, 0, 0, 0, '2024-01-10 00:00:00', 'Green Power Crystal'),
	(11186, 2021, 0, 0, 0, '2024-01-10 00:00:00', 'Red Power Crystal'),
	(11188, 2011, 0, 0, 0, '2024-01-10 00:00:00', 'Yellow Power Crystal'),
	(11370, 6001, 0, 0, 0, '2024-01-10 00:00:00', 'Dark Iron Ore'),
	(11371, 130242, 0, 0, 0, '2024-01-10 00:00:00', 'Dark Iron Bar'),
	(11382, 710997, 0, 0, 0, '2024-01-10 00:00:00', 'Blood of the Mountain'),
	(12037, 128, 0, 0, 0, '2024-01-10 00:00:00', 'Mystery Meat'),
	(12184, 218, 0, 0, 0, '2024-01-10 00:00:00', 'Raptor Flesh'),
	(12202, 23, 0, 0, 0, '2024-01-10 00:00:00', 'Tiger Meat'),
	(12203, 132, 0, 0, 0, '2024-01-10 00:00:00', 'Red Wolf Meat'),
	(12204, 1637, 0, 0, 0, '2024-01-10 00:00:00', 'Heavy Kodo Meat'),
	(12206, 1454, 0, 0, 0, '2024-01-10 00:00:00', 'Tender Crab Meat'),
	(12207, 1489, 0, 0, 0, '2024-01-10 00:00:00', 'Giant Egg'),
	(12213, 1127, 0, 0, 0, '2024-01-10 00:00:00', 'Carrion Surprise'),
	(12214, 1013, 0, 0, 0, '2024-01-10 00:00:00', 'Mystery Stew'),
	(12223, 52, 0, 0, 0, '2024-01-10 00:00:00', 'Meaty Bat Wing'),
	(12359, 2104, 0, 0, 0, '2024-01-10 00:00:00', 'Thorium Bar'),
	(12360, 399164, 0, 0, 0, '2024-01-10 00:00:00', 'Arcanite Bar'),
	(12361, 169241, 0, 0, 0, '2024-01-10 00:00:00', 'Blue Sapphire'),
	(12363, 249952, 0, 0, 0, '2024-01-10 00:00:00', 'Arcane Crystal'),
	(12364, 27981, 0, 0, 0, '2024-01-10 00:00:00', 'Huge Emerald'),
	(12365, 3190, 0, 0, 0, '2024-01-10 00:00:00', 'Dense Stone'),
	(12644, 18650, 0, 0, 0, '2024-01-10 00:00:00', 'Dense Grinding Stone'),
	(12655, 25771, 0, 0, 0, '2024-01-10 00:00:00', 'Enchanted Thorium Bar'),
	(12662, 59898, 0, 0, 0, '2024-01-10 00:00:00', 'Demonic Rune'),
	(12799, 19781, 0, 0, 0, '2024-01-10 00:00:00', 'Large Opal'),
	(12800, 65100, 0, 0, 0, '2024-01-10 00:00:00', 'Azerothian Diamond'),
	(12803, 95896, 0, 0, 0, '2024-01-10 00:00:00', 'Living Essence'),
	(12804, 7999, 0, 0, 0, '2024-01-10 00:00:00', 'Powerful Mojo'),
	(12808, 22799, 0, 0, 0, '2024-01-10 00:00:00', 'Essence of Undeath'),
	(12809, 73320, 0, 0, 0, '2024-01-10 00:00:00', 'Guardian Stone'),
	(12810, 22123, 0, 0, 0, '2024-01-10 00:00:00', 'Enchanted Leather'),
	(12811, 599998, 0, 0, 0, '2024-01-10 00:00:00', 'Righteous Orb'),
	(13422, 8145, 0, 0, 0, '2024-01-10 00:00:00', 'Stonescale Eel'),
	(13423, 12923, 0, 0, 0, '2024-01-10 00:00:00', 'Stonescale Oil'),
	(13463, 1970, 0, 0, 0, '2024-01-10 00:00:00', 'Dreamfoil'),
	(13464, 246, 0, 0, 0, '2024-01-10 00:00:00', 'Golden Sansam'),
	(13465, 9276, 0, 0, 0, '2024-01-10 00:00:00', 'Mountain Silversage'),
	(13466, 4950, 0, 0, 0, '2024-01-10 00:00:00', 'Plaguebloom'),
	(13467, 2925, 0, 0, 0, '2024-01-10 00:00:00', 'Icecap'),
	(13468, 265134, 0, 0, 0, '2024-01-10 00:00:00', 'Black Lotus'),
	(13510, 830261, 0, 0, 0, '2024-01-10 00:00:00', 'Flask of the Titans'),
	(13511, 697484, 0, 0, 0, '2024-01-10 00:00:00', 'Flask of Distilled Wisdom'),
	(13512, 673198, 0, 0, 0, '2024-01-10 00:00:00', 'Flask of Supreme Power'),
	(13754, 114, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Glossy Mightfish'),
	(13755, 2544, 0, 0, 0, '2024-01-10 00:00:00', 'Winter Squid'),
	(13756, 5443, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Summer Bass'),
	(13758, 554, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Redgill'),
	(13759, 6583, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Nightfin Snapper'),
	(13760, 981, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Sunscale Salmon'),
	(13888, 921, 0, 0, 0, '2024-01-10 00:00:00', 'Darkclaw Lobster'),
	(13889, 1723, 0, 0, 0, '2024-01-10 00:00:00', 'Raw Whitescale Salmon'),
	(13893, 1853, 0, 0, 0, '2024-01-10 00:00:00', 'Large Raw Mightfish'),
	(13926, 62500, 0, 0, 0, '2024-01-10 00:00:00', 'Golden Pearl'),
	(14047, 1197, 0, 0, 0, '2024-01-10 00:00:00', 'Runecloth'),
	(14048, 8270, 0, 0, 0, '2024-01-10 00:00:00', 'Bolt of Runecloth'),
	(14227, 5232, 0, 0, 0, '2024-01-10 00:00:00', 'Ironweb Spider Silk'),
	(14256, 32119, 0, 0, 0, '2024-01-10 00:00:00', 'Felcloth'),
	(14342, 212490, 0, 0, 0, '2024-01-10 00:00:00', 'Mooncloth'),
	(14343, 14724, 0, 0, 0, '2024-01-10 00:00:00', 'Small Brilliant Shard'),
	(14344, 48010, 0, 0, 0, '2024-01-10 00:00:00', 'Large Brilliant Shard'),
	(15407, 106133, 0, 0, 0, '2024-01-10 00:00:00', 'Cured Rugged Hide'),
	(15408, 1900, 0, 0, 0, '2024-01-10 00:00:00', 'Heavy Scorpid Scale'),
	(15409, 89394, 0, 0, 0, '2024-01-10 00:00:00', 'Refined Deeprock Salt'),
	(15410, 3000000, 0, 0, 0, '2024-01-10 00:00:00', 'Scale of Onyxia'),
	(15412, 1378, 0, 0, 0, '2024-01-10 00:00:00', 'Green Dragonscale'),
	(15414, 15294, 0, 0, 0, '2024-01-10 00:00:00', 'Red Dragonscale'),
	(15415, 3446, 0, 0, 0, '2024-01-10 00:00:00', 'Blue Dragonscale'),
	(15416, 9208, 0, 0, 0, '2024-01-10 00:00:00', 'Black Dragonscale'),
	(15417, 53877, 0, 0, 0, '2024-01-10 00:00:00', 'Devilsaur Leather'),
	(15419, 5433, 0, 0, 0, '2024-01-10 00:00:00', 'Warbear Leather'),
	(15420, 1856, 0, 0, 0, '2024-01-10 00:00:00', 'Ironfeather'),
	(15422, 11051, 0, 0, 0, '2024-01-10 00:00:00', 'Frostsaber Leather'),
	(15423, 1989, 0, 0, 0, '2024-01-10 00:00:00', 'Chimera Leather'),
	(15992, 7795, 0, 0, 0, '2024-01-10 00:00:00', 'Dense Blasting Powder'),
	(15994, 12784, 0, 0, 0, '2024-01-10 00:00:00', 'Thorium Widget'),
	(16000, 41497, 0, 0, 0, '2024-01-10 00:00:00', 'Thorium Tube'),
	(16006, 401585, 0, 0, 0, '2024-01-10 00:00:00', 'Delicate Arcanite Converter'),
	(16202, 9866, 0, 0, 0, '2024-01-10 00:00:00', 'Lesser Eternal Essence'),
	(16203, 47034, 0, 0, 0, '2024-01-10 00:00:00', 'Greater Eternal Essence'),
	(16204, 14844, 0, 0, 0, '2024-01-10 00:00:00', 'Illusion Dust'),
	(17010, 511688, 0, 0, 0, '2024-01-10 00:00:00', 'Fiery Core'),
	(17011, 721018, 0, 0, 0, '2024-01-10 00:00:00', 'Lava Core'),
	(17012, 218676, 0, 0, 0, '2024-01-10 00:00:00', 'Core Leather'),
	(17771, 4000000, 0, 0, 0, '2024-01-10 00:00:00', 'Elementium Bar'),
	(18512, 88498, 0, 0, 0, '2024-01-10 00:00:00', 'Larval Acid'),
	(18562, 890000, 0, 0, 0, '2024-01-10 00:00:00', 'Elementium Ore'),
	(19726, 478387, 0, 0, 0, '2024-01-10 00:00:00', 'Bloodvine'),
	(20520, 81436, 0, 0, 0, '2024-01-10 00:00:00', 'Dark Rune'),
	(21217, 2378, 0, 0, 0, '2024-01-10 00:00:00', 'Sagefish Delight'),
	(813512, 797484, 0, 0, 0, '2024-01-10 00:00:00', 'Flask of Battle Prowess');

