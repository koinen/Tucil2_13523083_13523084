# Invinciquadtree

**Invinciquadtree** adalah sebuah program kompresi gambar menggunakan metode Quadtree Compression. Program ini dirancang untuk membaca dan melakukan kompresi terhadap citra gambar dengan membagi area gambar menjadi bagian-bagian kuadran hingga mencapai tingkat homogenitas yang sesuai dengan threshold yang ditentukan. Program ini dibuat untuk memenuhi Tugas Kecil 2 mata kuliah Strategi Algoritma (IF2211).

## Requirement dan Instalasi  
Program ini membutuhkan tools dan dependency berikut untuk proses build:

- [CMake](https://cmake.org/)
- [vcpkg](https://github.com/microsoft/vcpkg)
- [Ninja](https://ninja-build.org/)

Pastikan semua requirement di atas telah terinstal dan tersedia di environment PATH.

## Cara Mengkompilasi Program  
Build dapat dilakukan dengan menjalankan skrip berikut:

- **Windows**:  
  Jalankan `./run.bat` di Command Prompt atau PowerShell.
  
- **Linux / WSL**:  
  Jalankan `./run.sh` di terminal.

Setelah proses build selesai, file executable `App.exe` akan tersedia di folder `bin`.

## Cara Menjalankan dan Menggunakan Program  
Setelah build selesai, jalankan program melalui terminal/command prompt dengan format:

```bash
./bin/App.exe
```

Contoh:
```bash
./bin/App.exe
```

Setelah program berhasil dimulai, masukkan parameter-parameter berikut sesuai kebutuhan:
- Alamat absolut gambar yang akan dikompresi.  
- Metode perhitungan error
- Ambang batas (Nilai threshold)
- Ukuran blok minimum
- Target persentase kompresi
- Alamat absolut gambar hasil kompresi
- Alamat absolut GIF hasil animasi


Jika mengalami kesulitan dalam proses build atau tidak memenuhi requirement, pengguna dapat langsung menggunakan file aplikasi yang telah disediakan melalui halaman GitHub Release terbaru dari repository ini.

## Author  
Program ini dibuat oleh:

- David Bakti Lodinato 13523083
- Lutfi Hakim Yusra 13523084


