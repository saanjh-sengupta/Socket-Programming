## Socket-Programming

Implementation of Multi - Client and Single Server code design implemntation using Modern CPP constructs

CODE DESIGN PATTERN DIAGRAM

            Server Socket
                |
  ------- Socket Created  ---- Bind -----
   |                                  |
   |                                  |
   |                                  |
   |                               Listen
   |                                  |
Connect                               | ----------- Buffer Created  
   |                                                    |
   |                                                    |                                                
   |                                    Incoming request stored inside the buffer
   |                                                    |
   |                                                 Reply back
   |    Client Socket --------------------------------- |                           
   |         |  
   |     Client Socket Created -----
   |                            |
   |                            |
   |                            |
Connect ------------  Server Socket Created --------
   |                            |                  |
   |                            |                  |
   |                            |                  |
   ------------------------ Send Data              |
                                                   |
                                                Buffer Creation
                                                      |
                                                      |
                                        Incoming data information stored
                                                      |
                                                      |
                                                  Displayed