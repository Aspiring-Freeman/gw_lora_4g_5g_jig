# 发布检查清单

每次发布新版本前，按此清单检查。

## 发布前检查

### 代码

- [ ] 所有功能测试通过
- [ ] Debug 日志已关闭或设为合适级别
- [ ] 无硬编码的测试串口号、IP 地址
- [ ] `requirements.txt` 已更新（如有新依赖）
- [ ] 代码已 commit，工作区干净

### 文档

- [ ] `VERSION` 文件已更新
- [ ] `CHANGELOG.md` 已更新，记录本次变更
- [ ] `README.md` 如有需要已更新
- [ ] 协议文档如有变更已同步

### 硬件（如本次有硬件更新）

- [ ] 原理图/PCB 已提交
- [ ] BOM 已更新
- [ ] Gerber 已生成并验证

### 固件（如本次有固件更新）

- [ ] 固件版本号已更新
- [ ] 固件已测试验证
- [ ] 与上位机协议兼容性已确认

---

## 版本号确定

根据变更类型确定版本号：

| 变更类型 | 版本号变化 | 示例 |
|----------|------------|------|
| Bug 修复、小优化 | 修订号 +1 | 1.0.0 → 1.0.1 |
| 新功能、向下兼容 | 次版本 +1 | 1.0.1 → 1.1.0 |
| 重大变更、不兼容 | 主版本 +1 | 1.1.0 → 2.0.0 |

---

## 打包内容

### 软件包

```bash
# 打包目录
software/
├── src/
├── config/
│   ├── default.yaml
│   └── products/
├── requirements.txt
└── README.md
```

打包命名：`{项目名}-software-v{版本}.zip`

### Gerber 包（如有硬件更新）

```
包含：
- 所有 Gerber 层
- 钻孔文件
- 坐标文件（如需 SMT）
- BOM（可选）
```

打包命名：`{项目名}-gerber-v{版本}-{日期}.zip`

### 固件（如有更新）

命名：`{项目名}-firmware-v{版本}.bin`

---

## 发布步骤

### 1. 更新版本文件

```bash
# 修改 VERSION 文件
echo "1.1.0" > VERSION

# 修改代码中的版本号（如有）
# software/src/__version__.py
```

### 2. 更新 CHANGELOG

```markdown
## [1.1.0] - 2024-12-20

### Added
- 新增 xxx 功能

### Changed
- 优化 xxx

### Fixed
- 修复 xxx 问题
```

### 3. 提交并打 Tag

```bash
git add .
git commit -m "release: v1.1.0"
git tag v1.1.0
git push origin main
git push origin v1.1.0
```

### 4. 创建 GitHub Release

1. 进入 GitHub 仓库 → Releases → Draft a new release
2. 选择刚才的 tag：`v1.1.0`
3. Release 标题：`{项目名} v1.1.0`
4. 描述：复制 CHANGELOG 中对应版本的内容
5. 附件上传：
   - [ ] `{项目名}-software-v1.1.0.zip`
   - [ ] `{项目名}-gerber-v1.1.0-20241220.zip`（如有）
   - [ ] `{项目名}-firmware-v1.1.0.bin`（如有）
6. 发布

---

## 发布后

- [ ] 通知相关人员（产线、嵌软等）
- [ ] 如有产线部署，确认部署完成
- [ ] 记录本次发布遇到的问题（便于后续改进）

---

## 快速命令参考

```bash
# 查看当前版本
cat VERSION

# 查看所有 tag
git tag -l

# 删除本地 tag（如果打错了）
git tag -d v1.1.0

# 删除远程 tag（如果打错了）
git push origin :refs/tags/v1.1.0
```
