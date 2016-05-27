//Programa que chequea si el switch S1 esta activado y prende el led D1 con el boton P1


while(1)
{
    if(ORT_BB01_SWGetState(S1)==1)
    {
                ORT_BB01_LedsToggle(D1);
                delay(100);
    }
    else if(ORT_BB01_PBGetState(P1)==1)
    {
        ORT_BB01_LedSet(D1)
    }
    else ORT_BB01_ledReset(D1);

}
