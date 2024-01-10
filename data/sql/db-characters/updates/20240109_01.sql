DROP TABLE IF EXISTS `mod_multi_class_character_queststatus`;
CREATE TABLE `mod_multi_class_character_queststatus` (
	`guid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`class` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`quest` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`status` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`explored` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`timer` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`mobcount1` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`mobcount2` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`mobcount3` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`mobcount4` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`itemcount1` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`itemcount2` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`itemcount3` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`itemcount4` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`itemcount5` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`itemcount6` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	`playercount` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
	PRIMARY KEY (`guid`, `class`, `quest`) USING BTREE,
	INDEX `idx_guidclass` (`guid`, `class`) USING BTREE,
	INDEX `idx_guid` (`guid`) USING BTREE
);

DROP TABLE IF EXISTS `mod_multi_class_character_queststatus_rewarded`;
CREATE TABLE `mod_multi_class_character_queststatus_rewarded` (
	`guid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`class` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`quest` INT(10) UNSIGNED NOT NULL DEFAULT '0' ,
	`active` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
	PRIMARY KEY (`guid`, `class`, `quest`) USING BTREE,
	INDEX `idx_guidclass` (`guid`, `class`) USING BTREE,
	INDEX `idx_guid` (`guid`) USING BTREE
);