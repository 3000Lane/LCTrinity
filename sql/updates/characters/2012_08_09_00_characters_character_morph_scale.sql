DROP TABLE IF EXISTS `character_morph`;
CREATE TABLE IF NOT EXISTS `character_morph` (
  `guid` int(11) NOT NULL DEFAULT '0',
  `morph` int(11) DEFAULT NULL,
  `comment` text NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `character_scale`;
CREATE TABLE IF NOT EXISTS `character_scale` (
  `guid` int(11) NOT NULL,
  `scale` float NOT NULL,
  `comment` text,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
