_This project has been created as part of the 42 curriculum by pde-alme, rogde-so and skuhlcke._

IRC is not safe due to:
- Plain-text messaging - An ISP or a middle-man can read the connection's traffic (use SSL/TLS for HTTPS and avoid port 80 servers);
- No encryption - Server administrators and other operators can read your messages;
- IP address exposure - IRC servers can expose your IP address to individuals connected on the same channel (use SASL or NickServ);
- Trust based file transfer - Transferring files sent by other connected clients can contain malware (don't be an idiot).

Post all references, websites and documents used here:

Books:
- https://beej.us/guide/bgnet/                                          -> Beej's Guide to Network Programming;

Documents:
- https://www.rfc-editor.org/info/rfc1459/                              -> RFC-1459 (IRC) Standard;
- https://en.wikipedia.org/wiki/IRC                                     -> Internet Relay Chat (IRC);
- https://en.wikipedia.org/wiki/Multiplexing                            -> Multiplexing;
- https://en.wikipedia.org/wiki/Poll_(Unix)                             -> Poll;
- https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form                -> Backus-Naur Form;
- https://en.wikipedia.org/wiki/Bulletin_board_system                   -> BBS (context history);
- https://github.com/bagder/irchistory                                  -> IRC history;
- https://en.wikipedia.org/wiki/ARPANET                                 -> ARPANET;
- https://en.wikipedia.org/wiki/Network_socket                          -> Network Sockets;
- https://en.wikipedia.org/wiki/Lists_of_network_protocols              -> Network Protocols and Ports list;
- https://www.iana.org/assignments/service-names-port-numbers           -> IANA Ports list (or cat /etc/services | less);
- https://en.wikipedia.org/wiki/OSI_model                               -> OSI Model;
- https://en.wikipedia.org/wiki/Connectionless_communication            -> Connectionless Communication;
- https://en.wikipedia.org/wiki/Connection-oriented_communication       -> Connection-Oriented Communication;
- https://en.wikipedia.org/wiki/User_Datagram_Protocol                  -> UDP;
- https://en.wikipedia.org/wiki/Transmission_Control_Protocol           -> TCP;
- https://en.wikipedia.org/wiki/Stream_Control_Transmission_Protocol    -> SCTP;
- https://en.wikipedia.org/wiki/Datagram_Congestion_Control_Protocol    -> DCCP;
- https://en.wikipedia.org/wiki/Trivial_File_Transfer_Protocol          -> TFTP;

IRSSI:
- https://en.wikipedia.org/wiki/Irssi                                   -> IRSSI wikipedia page;
- https://irssi.org/New-users/                                          -> IRSSI quickstart page;

Network:
- https://www.ircnet.com/sasl                                           -> Simple Authentication and Security Layer;
- https://netsplit.de/                                                  -> All networks, servers and channels;

Videos:
- https://www.youtube.com/watch?v=6UbKenFipjo&t=59s                     -> Internet Relay Chat (History);

Q&A:
- https://stackoverflow.com/questions/3229860/what-is-the-meaning-of-so-reuseaddr-setsockopt-option-linux