# WrapAroundDemo for SSD1306

![RoteteDemo](https://user-images.githubusercontent.com/6020549/165236460-e1fd757c-dcff-4601-bce1-b533599b5fc5.JPG)

A 128x32 panel has 4 pages of internal memory, and a 128x64 panel has 8 pages of internal memory.   
PAGE_SCROLL_DOWN/PAGE_SCROLL_UP is page-by-page scrolling and works fast.   


Image of PAGE_SCROLL_DOWN
```
+--------+  +--------+
| Page 1 |  | Page 2 |
+--------+  +--------+
| Page 2 |  | Page 3 |
+--------+  +--------+
| Page 3 |  | Page 4 |
+--------+  +--------+
| Page 4 |  | Page 5 |
+--------+  +--------+
| Page 5 |  | Page 6 |
+--------+  +--------+
| Page 6 |  | Page 7 |
+--------+  +--------+
| Page 7 |  | Page 8 |
+--------+  +--------+
| Page 8 |  | Page 1 |
+--------+  +--------+
```

