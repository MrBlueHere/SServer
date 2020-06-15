# SServer
Simple HTTP Server or simply: **Simple Server**

Author: Ladislav Floriš

## Original assignment
HTTP server

Úkolem je naprogramovat jednoduchý HTTP server s podporou různých generátorů obsahu. Generátor obsahu musí podporovat:

1. výpis obsahu adresáře
2. konkrétní html stránka (statický obsah)
3. externí skript nebo program

Server musí implementovat:

1. načítání konfiguračního souboru
2. parametry naslouchání na síti (IP adresa, m_port)
3. omezení na práci s konkrétním adresářem
4. log přenosů (kam se má ukládat, v jakém formátu, jak má vypadat hlavička každého záznamu, ...)
5. vypnutí serveru na (konfigurovatelné) URL adrese

HTTP server může umět obsloužit více domén nebo poskytovat virtuální filesystém (mapování virtuálních URL na fyzické cesty na disku)

Volitelně: Podpora HTTPS (openssl), vícevláknové obsloužení klientů

Kde lze využít polymorfismus? (doporučené)

- Druh souboru: adresář, HTML soubor, obrázek, skript, nepodporovaný formát, ...
- Logování: na konzoli, do souboru, do databáze, ...
- Styl logování: jednoduchá hlavička, kompletní požadavek (např. pouze pro chybové stavy), statistika přístupů, ...

## Specification
I will create a Simple HTTP Server serving static files (html, images and other) as well as running executable scripts.
The server will support HTTP Version 1.1 and it will be limited to GET requests only.
Due to usage of system calls like `sendfile()`, it is portable only to Unix/Linux.

It will be possible to customize server configuration by modifying a config file (logic implemented in `CConfiguration` class).

Each connection will get a dedicated thread (for simplicity purposes, we won't use thread pools or in any way reuse
already created threads) to make serving multiple clients faster.

### Polymorphism 
Polymorphism is used in class `CLogger`. `CLogger` is an abstract class with 2 derived classes `CConsoleLogger` and `CFileLogger`
which implement logging to console and file respectively. `CServer` class instantiates an appropriate logger class in `Startup` 
based on the configuration and then uses method `Log` to log messages irrespective of the instantiated logger.

Polymorphism used in class `CFile`. `CFile` is an abstract class with derived classes `CStaticFile` `CDirectory` and `CExecutableScript`.
`CFile` contains a pure virtual function `Log` which is overloaded in the derived classes.