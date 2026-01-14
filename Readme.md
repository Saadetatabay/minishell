# minishell

Bu proje, **Unix tabanlı sistemlerde bir shell’in temel çalışma mantığını** öğrenmek amacıyla geliştirilmiş, **bash benzeri** bir komut satırı uygulamasıdır.  
Proje süresince odak noktam; **sistem programlama, process yönetimi ve düşük seviyeli mimariyi** anlamak olmuştur.

## 🎯 Projenin Kapsamı

- Komut satırı girdisinin ayrıştırılması (parsing)
- Built-in ve harici komutların ayrımı
- `fork`, `execve`, `wait` kullanarak process yönetimi
- Pipe (`|`) ve redirect (`<`, `>`, `>>`) mekanizmaları
- Ortam değişkenlerinin yönetimi
- Terminal sinyallerinin doğru şekilde ele alınması

## 🧠 Kazanılan Teknik Yetkinlikler

- **Sistem çağrıları ve process lifecycle**
- **Dosya tanımlayıcıları (file descriptors)**
- **Pipe & redirect zincirleri**
- **Signal handling**
- **Bellek yönetimi ve hata senaryoları**
- **Modüler C kodu yazımı**
- **Shell mimarisine giriş**

## ⚙️ Desteklenen Özellikler

- Harici komut çalıştırma (`ls`, `cat`, `grep` vb.)
- Built-in komutlar:
  - `cd`, `echo`, `pwd`
  - `export`, `unset`, `env`
  - `exit`
- Pipe (`|`)
- Redirect (`<`, `>`, `>>`)
- Ortam değişkenleri (`$VAR`)
- `Ctrl+C`, `Ctrl+D`, `Ctrl+\` sinyalleri

## 🛠️ Derleme ve Çalıştırma

```bash
make
./minishell
