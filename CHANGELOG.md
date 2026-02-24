# Changelog

本项目所有版本变更记录。

格式基于 [Keep a Changelog](https://keepachangelog.com/)，版本号遵循 [语义化版本](https://semver.org/)。

---

## [Unreleased]

### Added
- 

### Changed
- 

### Fixed
- 

---

## [1.1.0] - 2025-02-24

### Added
- 启动横幅信息，显示版本号、当前工位和调试模式状态
- 周期性心跳调试打印（每10秒输出一次存活信息）
- PC 协议解析增加详细调试日志（接收数据、帧头定位、工位匹配等）
- 测试流程各阶段增加调试日志输出
- 工位检测增加 100ms 延时，确保 GPIO 状态稳定
- PC 协议中增加工位不匹配告警打印
- 定时器增加 `Debug_print_time` 倒计时支持

### Changed
- UART 结构体 `TxLen/TxOpc/RxLen/RxOpc` 类型从 `uint8_t` 扩展为 `uint16_t`，支持更大数据包
- `chaoshi_dengdai` 变量增加 `volatile` 修饰符，确保中断安全
- `Debug_Mode` 默认值从 1 改为 0（默认关闭调试模式）
- 全局代码格式化统一：缩进对齐、运算符前后加空格
- 调试信息从中文改为英文标识，提升日志可读性

### Fixed
- 修复 `main()` 中缩进不一致问题
- 修复 `time.c` 中 ATIM_IRQHandler 缩进混乱问题

---

## [1.0.0] - YYYY-MM-DD

### Added
- 初始版本
- 基础测试流程
- MCU 通信协议实现
- MES 对接功能

---

<!-- 
变更类型说明：
- Added: 新功能
- Changed: 现有功能的变更
- Deprecated: 即将移除的功能
- Removed: 已移除的功能
- Fixed: Bug 修复
- Security: 安全相关修复
-->
