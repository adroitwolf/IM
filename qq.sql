/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50634
Source Host           : localhost:3306
Source Database       : qq

Target Server Type    : MYSQL
Target Server Version : 50634
File Encoding         : 65001

Date: 2019-05-26 13:08:14
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for addfriends
-- ----------------------------
DROP TABLE IF EXISTS `addfriends`;
CREATE TABLE `addfriends` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `requestQQ` bigint(20) NOT NULL,
  `receviceQQ` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `requestQQ` (`requestQQ`),
  KEY `receviceQQ` (`receviceQQ`),
  CONSTRAINT `receviceQQ` FOREIGN KEY (`receviceQQ`) REFERENCES `user` (`qq`),
  CONSTRAINT `requestQQ` FOREIGN KEY (`requestQQ`) REFERENCES `user` (`qq`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for chatinfo
-- ----------------------------
DROP TABLE IF EXISTS `chatinfo`;
CREATE TABLE `chatinfo` (
  `cno` int(11) NOT NULL AUTO_INCREMENT,
  `context` varchar(255) NOT NULL,
  `sendqq` bigint(20) NOT NULL,
  `receiveqq` bigint(20) NOT NULL,
  `cdate` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`cno`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for friends
-- ----------------------------
DROP TABLE IF EXISTS `friends`;
CREATE TABLE `friends` (
  `Fno` int(11) NOT NULL AUTO_INCREMENT,
  `fqq` bigint(20) NOT NULL,
  `qq` bigint(20) NOT NULL,
  `fstatus` int(11) NOT NULL COMMENT '1在线-0离线',
  `FNickName` varchar(20) NOT NULL,
  PRIMARY KEY (`Fno`)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for login
-- ----------------------------
DROP TABLE IF EXISTS `login`;
CREATE TABLE `login` (
  `Lno` int(11) NOT NULL AUTO_INCREMENT,
  `Lip` varchar(20) NOT NULL,
  `Lport` int(11) NOT NULL,
  `Ldate` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  `Lstatus` int(11) NOT NULL COMMENT '1在线-0离线',
  `Lqq` bigint(20) NOT NULL,
  `Ldesk` varchar(20) NOT NULL,
  PRIMARY KEY (`Lno`),
  UNIQUE KEY `QQ` (`Lqq`) USING HASH,
  CONSTRAINT `qqId` FOREIGN KEY (`Lqq`) REFERENCES `user` (`qq`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `qq` bigint(20) NOT NULL AUTO_INCREMENT,
  `pwd` varchar(20) NOT NULL,
  `sign` varchar(30) DEFAULT NULL,
  `nickname` varchar(10) NOT NULL,
  `sex` varchar(5) NOT NULL,
  PRIMARY KEY (`qq`)
) ENGINE=InnoDB AUTO_INCREMENT=10014 DEFAULT CHARSET=utf8;
