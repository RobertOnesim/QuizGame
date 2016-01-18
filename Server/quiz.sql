PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE general(
ID int primary key not null,
intrebare char(2000) not null,
raspuns1 char(2000) not null,
raspuns2 char(2000) not null,
raspuns3 char(2000) not null,
raspuns4 char(2000) not null,
corect int not null);
INSERT INTO "general" VALUES(1,'Care este capitala Romaniei?','Paris','Londra','Bucuresti','Iasi',3);
INSERT INTO "general" VALUES(2,'Cati cromozomi are un om?','49','46','44','48',2);
INSERT INTO "general" VALUES(3,'Din cati jucatori este formata o echipa de handbal?','cinci','sase','sapte','opt',3);
INSERT INTO "general" VALUES(4,'Unde au fost filmate peisajele din Nemuritorul','Irlanda','Grecia','Marea Britanie','Scotia',4);
INSERT INTO "general" VALUES(5,'Care este cel mai lung fluviu din Europa?','Dunarea','Volga','Nil','Ural',2);
INSERT INTO "general" VALUES(6,'Care este capitala statului Muntenegru?','Podgorita','Bruxelles','Lisabona','Dublin',1);
INSERT INTO "general" VALUES(7,'Care este capitala statului Letoniei?','Riga','Vilnius','Talin','Oslo',2);
INSERT INTO "general" VALUES(8,'Pe ce continent se afla cea mai mare cascada din lume?','Africa','Europa','America de Nord','Australia',3);
INSERT INTO "general" VALUES(9,'Care este al doilea varf de munte ca inaltime din lume?','Nanga Parbat','Makalu','Lhotse','K2',4);
INSERT INTO "general" VALUES(10,'In ce tara se afla cei mai activi vulcani?','Indonezi','Noua Zeelanda','Japonia','Italia',1);
INSERT INTO "general" VALUES(11,'Tegucigalpa este capitala?','Guatemala','Honduras','Panama','El Salvador',2);
INSERT INTO "general" VALUES(12,'Care este cel mai usacat desert din lume?','Taklamakan','Kalahari','Sahara','Atacama',4);
INSERT INTO "general" VALUES(13,'Care este cel mai mic stat de pe mapamond?','Andora','Monaco','Vatican','Liechtenstein',3);
INSERT INTO "general" VALUES(14,'Cat este pi?','4.23','2.223','3,14','3,24',3);
INSERT INTO "general" VALUES(15,'Cate laturi egale are un triunghi isoscel?','2','3','1','0',1);
INSERT INTO "general" VALUES(16,'Cat face 2+2/2?','1','2','6','3',4);
INSERT INTO "general" VALUES(17,'Pe o sarma sunt 10 pasari. Daca un vanator impusca una, cate pasari raman?','9','0','3','10',2);
INSERT INTO "general" VALUES(18,'Cate laturi are un octogon?','10','9','8','7',3);
INSERT INTO "general" VALUES(19,'Care este cel mai lung os al corpului?','femurul','tibia','antebratul','humerusul',1);
INSERT INTO "general" VALUES(20,'Ce secreta glanda tiroida?','tirozina','cortizonul','tiroxina','aldosteron',3);
INSERT INTO "general" VALUES(21,'Care este cel mai mare viscer?','stomacul','inima','splina','ficatul',4);
INSERT INTO "general" VALUES(22,'Cine a descoperit insulina?','Paulescu','Paunescu','Cantacuzino','Danaila',1);
INSERT INTO "general" VALUES(23,'Ce parte a plante realizeaza fotosinteza?','tulpina','frunza','sepala','pistil',2);
INSERT INTO "general" VALUES(24,'Ce animal isi hraneste puii cu lapte si depune oua?','Pinguinul','Broasca testoasa','Cangurul','Oritoringul',4);
INSERT INTO "general" VALUES(25,'Care este cel mai rapid animal din lume?','leul','pantera','ghepardul','antilopa',3);
INSERT INTO "general" VALUES(26,'Oasele degetelor se numesc?','carpiene','tarsiene','humulus','semilunar',1);
INSERT INTO "general" VALUES(27,'Gonada feminina este?','ovulul','trompa uterina','uterul','ovarul',4);
CREATE TABLE biology(
ID int PRIMARY KEY NOT NULL,
intrebare char(2000) not null,
raspuns1 char(2000) not null,
raspuns2 char(2000) not null,
raspuns3 char(2000) not null,
raspuns4 char(2000) not null,
corect int not null);
INSERT INTO "biology" VALUES(1,'Cati cromozomi are un om?','49','46','44','48',2);
INSERT INTO "biology" VALUES(2,'Care este cel mai lung os al corpului?','femurul','tibia','antebratul','humerusul',1);
INSERT INTO "biology" VALUES(3,'Ce secreta glanda tiroida?','tirozina','cortizonul','tiroxina','aldosteron',3);
INSERT INTO "biology" VALUES(4,'Care este cel mai mare viscer?','stomacul','inima','splina','ficatul',4);
INSERT INTO "biology" VALUES(5,'Cine a descoperit insulina?','Paulescu','Paunescu','Cantacuzino','Danaila',1);
INSERT INTO "biology" VALUES(6,'Ce parte a plante realizeaza fotosinteza?','tulpina','frunza','sepala','pistil',2);
INSERT INTO "biology" VALUES(7,'Ce animal isi hraneste puii cu lapte si depune oua?','Pinguinul','Broasca testoasa','Cangurul','Oritoringul',4);
INSERT INTO "biology" VALUES(8,'Care este cel mai rapid animal din lume?','leul','pantera','ghepardul','antilopa',3);
INSERT INTO "biology" VALUES(9,'Oasele degetelor se numesc?','carpiene','tarsiene','humulus','semilunar',1);
INSERT INTO "biology" VALUES(10,'Gonada feminina este?','ovulul','trompa uterina','uterul','ovarul',4);
CREATE TABLE geography(
ID int PRIMARY KEY NOT NULL,
intrebare char(2000) not null,
raspuns1 char(2000) not null,
raspuns2 char(2000) not null,
raspuns3 char(2000) not null,
raspuns4 char(2000) not null,
corect int not null);
INSERT INTO "geography" VALUES(1,'Care este cel mai lung fluviu din Europa?','Dunarea','Volga','Nil','Ural',2);
INSERT INTO "geography" VALUES(2,'Care este capitala statului Muntenegru?','Podgorita','Bruxelles','Lisabona','Dublin',1);
INSERT INTO "geography" VALUES(3,'Care este capitala statului Letoniei?','Riga','Vilnius','Talin','Oslo',2);
INSERT INTO "geography" VALUES(4,'Care este capitala Romaniei?','Paris','Londra','Bucuresti','Iasi',3);
INSERT INTO "geography" VALUES(5,'Pe ce continent se afla cea mai mare cascada din lume?','Africa','Europa','America de Nord','Australia',3);
INSERT INTO "geography" VALUES(6,'Care este al doilea varf de munte ca inaltime din lume?','Nanga Parbat','Makalu','Lhotse','K2',4);
INSERT INTO "geography" VALUES(7,'In ce tara se afla cei mai activi vulcani?','Indonezi','Noua Zeelanda','Japonia','Italia',1);
INSERT INTO "geography" VALUES(8,'Tegucigalpa este capitala?','Guatemala','Honduras','Panama','El Salvador',2);
INSERT INTO "geography" VALUES(9,'Care este cel mai usacat desert din lume?','Taklamakan','Kalahari','Sahara','Atacama',4);
INSERT INTO "geography" VALUES(10,'Care este cel mai mic stat de pe mapamond?','Andora','Monaco','Vatican','Liechtenstein',3);
CREATE TABLE math(
ID int PRIMARY KEY NOT NULL,
intrebare char(2000) not null,
raspuns1 char(2000) not null,
raspuns2 char(2000) not null,
raspuns3 char(2000) not null,
raspuns4 char(2000) not null,
corect int not null);
INSERT INTO "math" VALUES(1,'Cat este pi?','4.23','2.223','3,14','3,24',3);
INSERT INTO "math" VALUES(2,'Cate laturi egale are un triunghi isoscel?','2','3','1','0',1);
INSERT INTO "math" VALUES(3,'Cat face 2+2/2?','1','2','6','3',4);
INSERT INTO "math" VALUES(4,'Pe o sarma sunt 10 pasari. Daca un vanator impusca una, cate pasari raman?','9','0','3','10',2);
INSERT INTO "math" VALUES(5,'Cate laturi are un octogon?','10','9','8','7',3);
INSERT INTO "math" VALUES(6,'Cate laturi egale are un triunghi echilateral?','0','3','2','1',2);
COMMIT;
