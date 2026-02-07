/**
 * @file fal_cfg.h
 * @brief FAL (Flash Abstraction Layer) 配置文件 - FM33LG04x平台
 * @version 1.1.0
 * @date 2026-01-05
 *
 * FM33LG04x Flash布局 (256KB总容量):
 * ┌───────────────────────────────────────────────────┐
 * │ 0x00000 - 0x03FFF │ Bootloader (16KB)             │
 * ├───────────────────────────────────────────────────┤
 * │ 0x04000 - 0x3BFFF │ APP (224KB)                   │
 * ├───────────────────────────────────────────────────┤
 * │ 0x3C000 - 0x3DFFF │ test_stats (8KB/4扇区)        │ ← 测试统计日志
 * ├───────────────────────────────────────────────────┤
 * │ 0x3E000 - 0x3EFFF │ upgrade_params (4KB/2扇区)    │ ← 升级参数
 * ├───────────────────────────────────────────────────┤
 * │ 0x3F000 - 0x3FFFF │ kvdb (4KB/2扇区)              │ ← FlashDB KVDB
 * └───────────────────────────────────────────────────┘
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

/*============================================================================
 * Flash 设备定义
 *===========================================================================*/

#define FM33LG04_FLASH_DEV_NAME "fm33lg04_onchip"

/* 声明 Flash 设备 */
extern const struct fal_flash_dev fm33lg04_onchip_flash;

/* Flash 设备表 */
#define FAL_FLASH_DEV_TABLE                                                    \
  { &fm33lg04_onchip_flash, }

/*============================================================================
 * 分区表配置
 *===========================================================================*/

/* 启用分区表配置 */
#define FAL_PART_HAS_TABLE_CFG

#ifdef FAL_PART_HAS_TABLE_CFG

/**
 * 分区表定义
 * 格式: {FAL_PART_MAGIC_WORD, "分区名", "设备名", 偏移, 大小, 标志}
 *
 * 注意:
 * - 偏移和大小必须是扇区(2KB)的整数倍
 * - test_stats 分区用于存储测试统计信息 (支持磨损均衡)
 * - upgrade_params 分区用于存储升级参数，Bootloader和APP共享
 * - kvdb 分区用于FlashDB的KVDB存储
 */
#define FAL_PART_TABLE                                                         \
  {                                                                            \
    {FAL_PART_MAGIC_WORD,                                                      \
     "test_stats",                                                             \
     FM33LG04_FLASH_DEV_NAME,                                                  \
     0x3C000,                                                                  \
     8 * 1024,                                                                 \
     0},                                                                       \
        {FAL_PART_MAGIC_WORD,                                                  \
         "upgrade_params",                                                     \
         FM33LG04_FLASH_DEV_NAME,                                              \
         0x3E000,                                                              \
         4 * 1024,                                                             \
         0},                                                                   \
        {FAL_PART_MAGIC_WORD,                                                  \
         "kvdb",                                                               \
         FM33LG04_FLASH_DEV_NAME,                                              \
         0x3F000,                                                              \
         4 * 1024,                                                             \
         0},                                                                   \
  }

#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
