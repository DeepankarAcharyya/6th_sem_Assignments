
genetic_code_table={
    "ttt":"F","ttc":"F","tta":"L","ttg":"L",
    "ctt":"L","ctc":"L","cta":"L","ctg":"L",
    "att":"I","atc":"I","ata":"I","atg":"M",
    "gtt":"V","gtc":"V","gta":"V","gtg":"V",
    
    "tct":"S","tcc":"S","tca":"S","tcg":"S",
    "cct":"P","ccc":"P","cca":"P","ccg":"P",
    "act":"T","acc":"T","aca":"T","acg":"T",
    "gct":"A","gcc":"A","gca":"A","gcg":"A",
    
    "tat":"Y","tac":"Y","taa":"*","tag":"*",
    "cat":"H","cac":"H","caa":"Q","cag":"Q",
    "aat":"N","aac":"N","aaa":"K","aag":"K",
    "gat":"D","gac":"D","gaa":"E","gag":"E",
    
    "tgt":"C","tgc":"C","tga":"*","tgg":"W",
    "cgt":"R","cgc":"R","cga":"R","cgg":"R",
    "agt":"S","agc":"S","aga":"R","agg":"R",
    "ggt":"G","ggc":"G","gga":"G","ggg":"G",
}


class aminoAcid_Counter:
    aminoAcid_Map ={
        "I":"Ile", 
        "L":"Leu",
        "V":"Val", 
        "F":"Phe",
        "M":"Met",
        "C":"Cys", 
        "A":"Ala", 
        "G":"Gly", 
        "P":"Pro", 
        "T":"Thr", 
        "S":"Ser", 
        "Y":"Tyr", 
        "W":"Trp",  
        "Q":"Gln", 
        "N":"Asn", 
        "H":"His",
        "E":"Glu",    
        "D":"Asp",
        "K":"Lys",
        "R":"Arg",
        "*":"Stop"
    }
    aminoAcid_Count ={ "I":0, "L":0, "V":0, "F":0, "M":0, "C":0,  "A":0, "G":0, "P":0, "T":0, "S":0, "Y":0, "W":0, "Q":0, "N":0, 
                       "H":0, "E":0, "D":0, "K":0, "R":0, "*":0
    }
    def record(self,aminoAcid_Block):
        self.aminoAcid_Count[aminoAcid_Block] = self.aminoAcid_Count[aminoAcid_Block] + 1
    def retriveAmino_Count(self):
        return self.aminoAcid_Count
    def getShortName(self):
        return self.aminoAcid_Map 

