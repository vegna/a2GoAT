void DrawCluster(TString sData, Int_t iMinEvn=0, Int_t iMinPart=0, Int_t iMinNaI=0, Int_t iMinBaF=0, TString sNaI="NaI.dat", TString sBaF="BaF2-PbWO4.dat"){

  gROOT->Clear();

  TGraph *gBox = new TGraph(4);
  gBox->SetName("gBox");
  gBox->SetPoint(0,  0,-180);
  gBox->SetPoint(1,  0, 180);
  gBox->SetPoint(2,180,-180);
  gBox->SetPoint(3,180, 180);
  gBox->SetMarkerStyle(1);
  gBox->SetMarkerColor(0);

  TGraph *gBox2 = new TGraph();
  gBox2->SetName("gBox2");
  gBox2->SetMarkerStyle(24);

  TGraph2D *gBox3 = new TGraph2D(8);
  gBox3->SetName("gBox3");
  gBox3->SetPoint(0,-50,-50,-50);
  gBox3->SetPoint(1,-50,-50,150);
  gBox3->SetPoint(2,-50, 50,-50);
  gBox3->SetPoint(3,-50, 50,150);
  gBox3->SetPoint(4, 50,-50,-50);
  gBox3->SetPoint(5, 50,-50,150);
  gBox3->SetPoint(6, 50, 50,-50);
  gBox3->SetPoint(7, 50, 50,150);
  gBox3->SetMarkerStyle(1);
  gBox3->SetMarkerColor(0);
  
  Int_t i,j;

  TTree *tNaI = new TTree("tNaI","NaI");
  tNaI->ReadFile(sNaI,"Ch:X:Y:Z");
  Int_t iNaI = tNaI->Draw("X:Y:Z","","goff");
  Double_t *dNaIX = tNaI->GetV1();
  Double_t *dNaIY = tNaI->GetV2();
  Double_t *dNaIZ = tNaI->GetV3();

  const Int_t cNaI = iNaI;

  Double_t dNaITh[cNaI];
  Double_t dNaIPh[cNaI];
  for(i=0; i<iNaI; i++){
    dNaITh[i] = (TMath::RadToDeg()*TMath::ACos(dNaIZ[i]/TMath::Sqrt(TMath::Power(dNaIX[i],2)+TMath::Power(dNaIY[i],2)+TMath::Power(dNaIZ[i],2))));
    dNaIPh[i] = (TMath::RadToDeg()*TMath::ATan2(dNaIY[i],dNaIX[i]));
  }

  TTree *tBaF = new TTree("tBaF","BaF");
  tBaF->ReadFile(sBaF,"Ch:X:Y:Z");
  Int_t iBaF = tBaF->Draw("X:Y:Z","","goff");
  Double_t *dBaFX = tBaF->GetV1();
  Double_t *dBaFY = tBaF->GetV2();
  Double_t *dBaFZ = tBaF->GetV3();

  const Int_t cBaF = iBaF;

  Double_t dBaFTh[cBaF];
  Double_t dBaFPh[cBaF];
  for(i=0; i<iBaF; i++){
    dBaFTh[i] = (TMath::RadToDeg()*TMath::ACos(dBaFZ[i]/TMath::Sqrt(TMath::Power(dBaFX[i],2)+TMath::Power(dBaFY[i],2)+TMath::Power(dBaFZ[i],2))));
    dBaFPh[i] = (TMath::RadToDeg()*TMath::ATan2(dBaFY[i],dBaFX[i]));
    gBox2->SetPoint(i,dBaFX[i],dBaFY[i]);
  }

  TFile fData(sData,"READ");
  TTree *tData = (TTree*)fData.Get("treeDetectorHits");

  Int_t iNNaI_Hits;
  Int_t* iNaI_Hits;
  Int_t* iNaI_Cluster;

  iNaI_Hits = new Int_t[720];
  iNaI_Cluster = new Int_t[720];

  tData->SetBranchAddress("nNaI_Hits",&iNNaI_Hits);
  tData->SetBranchAddress("NaI_Hits",iNaI_Hits);
  tData->SetBranchAddress("NaI_Cluster",iNaI_Cluster);

  Int_t iNBaF_Hits;
  Int_t* iBaF_Hits;
  Int_t* iBaF_Cluster;

  iBaF_Hits = new Int_t[720];
  iBaF_Cluster = new Int_t[720];

  tData->SetBranchAddress("nBaF2_PbWO4_Hits",&iNBaF_Hits);
  tData->SetBranchAddress("BaF2_PbWO4_Hits",iBaF_Hits);
  tData->SetBranchAddress("BaF2_PbWO4_Cluster",iBaF_Cluster);

  TTree *tEvent = (TTree*)fData.Get("treeRawEvent");

  Int_t iNParticles;
  UChar_t* iClusterSize;
  UChar_t* iApparatus;

  iClusterSize = new UChar_t[128];
  iApparatus = new UChar_t[128];

  tEvent->SetBranchAddress("nParticles",&iNParticles);
  tEvent->SetBranchAddress("clusterSize",iClusterSize);
  tEvent->SetBranchAddress("Apparatus",iApparatus);

  Bool_t bPart = true;
  Bool_t bNaI = true;
  Bool_t bBaF = true;

  Int_t iEvnN;
  for(iEvnN=iMinEvn; iEvnN<(tEvent->GetEntries()); iEvnN++){
    tEvent->GetEvent(iEvnN);

    if(iMinPart) bPart = false;
    if(iMinNaI) bNaI = false;
    if(iMinBaF) bBaF = false;

    if(iNParticles >= iMinPart) bPart = true;
    for(j=0; j<iNParticles; j++){
      if(iClusterSize[j] > iMinNaI && iApparatus[j] == 1) bNaI = true;
      if(iClusterSize[j] > iMinBaF && iApparatus[j] == 2) bBaF = true;
    }
    if(bPart && bNaI && bBaF) break;
  }

  cout << endl << "Plotting event " << iEvnN << endl << endl;

  tData->GetEvent(iEvnN);

  j=-1;
  for(i=0; i<iNNaI_Hits; i++){
    if(iNaI_Cluster[i] > j) j = iNaI_Cluster[i];
  }
  const Int_t iNNaI_Cluster = j+1;

  j=-1;
  for(i=0; i<iNBaF_Hits; i++){
    if(iBaF_Cluster[i] > j) j = iBaF_Cluster[i];
  }
  const Int_t iNBaF_Cluster = j+1;

  cout << iNNaI_Cluster << " NaI Clusters, " << iNBaF_Cluster << " BaF Clusters" << endl;

  gROOT->cd();

  const Int_t iNData = iNNaI_Cluster+iNBaF_Cluster+1;
  Int_t iDataN;

  TGraph *gData[iNData];
  for(i=0; i<iNData; i++){
    gData[i] = new TGraph();
    gData[i]->SetName(Form("gData_%d",i));
    gData[i]->SetMarkerStyle(20);
    gData[i]->SetMarkerColor(i+1);
  }

  TGraph *gData2[iNData];
  for(i=0; i<iNData; i++){
    gData2[i] = new TGraph();
    gData2[i]->SetName(Form("gData_%d",i));
    gData2[i]->SetMarkerStyle(20);
    gData2[i]->SetMarkerColor(i+1);
  }

  TGraph2D *gData3[iNData];
  for(i=0; i<iNData; i++){
    gData3[i] = new TGraph2D();
    gData3[i]->SetName(Form("gData2_%d",i));
    gData3[i]->SetMarkerStyle(20);
    gData3[i]->SetMarkerColor(i+1);
  }

  cout << endl << "NaI" << endl << endl;
  for(Int_t i=0; i<iNNaI_Hits; i++){
    cout << i << "\t" << iNaI_Hits[i] << "\t" << iNaI_Cluster[i] << "\t" << dNaIX[iNaI_Hits[i]] << "\t" << dNaIY[iNaI_Hits[i]] << "\t" << dNaIZ[iNaI_Hits[i]] << endl;
    iDataN = iNaI_Cluster[i]+1;
    gData[iDataN]->SetPoint(gData[iDataN]->GetN(),dNaITh[iNaI_Hits[i]],dNaIPh[iNaI_Hits[i]]);
    gData3[iDataN]->SetPoint(gData3[iDataN]->GetN(),dNaIX[iNaI_Hits[i]],dNaIY[iNaI_Hits[i]],dNaIZ[iNaI_Hits[i]]);
  }
  cout << endl << "BaF" << endl << endl;
  for(Int_t i=0; i<iNBaF_Hits; i++){
    cout << i << "\t" << iBaF_Hits[i] << "\t" << iBaF_Cluster[i] << "\t" << dBaFX[iBaF_Hits[i]] << "\t" << dBaFY[iBaF_Hits[i]] << "\t" << dBaFZ[iBaF_Hits[i]] << "\t" << iBaF_Cluster[i]+iNNaI_Cluster+1 << endl;
    if(iBaF_Cluster[i] < 0) iDataN = 0;
    else iDataN = iBaF_Cluster[i]+iNNaI_Cluster+1;
    gData[iDataN]->SetPoint(gData[iDataN]->GetN(),dBaFTh[iBaF_Hits[i]],dBaFPh[iBaF_Hits[i]]);
    gData2[iDataN]->SetPoint(gData2[iDataN]->GetN(),dBaFX[iBaF_Hits[i]],dBaFY[iBaF_Hits[i]]);
    gData3[iDataN]->SetPoint(gData3[iDataN]->GetN(),dBaFX[iBaF_Hits[i]],dBaFY[iBaF_Hits[i]],dBaFZ[iBaF_Hits[i]]);
    gBox2->SetPoint(iBaF_Hits[i],-100,0);
  }

  if(gROOT->FindObject("c1")) delete (TCanvas*)gROOT->FindObject("c1");
  if(gROOT->FindObject("c2")) delete (TCanvas*)gROOT->FindObject("c2");
  if(gROOT->FindObject("c3")) delete (TCanvas*)gROOT->FindObject("c3");

  TCanvas *c1 = new TCanvas("c1","Clusters in Theta and Phi",0,0,800,600);
  gBox->Draw("ap");
  gBox->SetTitle("Clusters in Theta and Phi");
  gBox->GetXaxis()->SetTitle("Theta (deg)");
  gBox->GetXaxis()->SetTitleOffset(1.2);
  gBox->GetYaxis()->SetTitle("Phi (deg)");
  gBox->GetYaxis()->SetTitleOffset(1.2);
  for(i=0; i<iNData; i++){
    if(gData[i]->GetN() == 1) gData[i]->SetPoint(1,-180,0);
    if(gData[i]->GetN() == 0) gData[i]->SetPoint(0,-180,0);
    gData[i]->Draw("same p");
  }  

  TCanvas *c2 = new TCanvas("c2","Clusters in TAPS",800,0,600,600);
  gBox2->Draw("ap");
  gBox2->SetTitle("Clusters in TAPS");
  gBox2->GetXaxis()->SetRangeUser(-70,70);
  gBox2->GetXaxis()->SetTitle("X (cm)");
  gBox2->GetXaxis()->SetTitleOffset(1.2);
  gBox2->GetYaxis()->SetRangeUser(-70,70);
  gBox2->GetYaxis()->SetTitle("Y (cm)");
  gBox2->GetYaxis()->SetTitleOffset(1.2);
  for(i=0; i<iNData; i++){
    if(gData2[i]->GetN() == 1) gData2[i]->SetPoint(1,-100,0);
    if(gData2[i]->GetN() == 0) gData2[i]->SetPoint(0,-100,0);
    gData2[i]->Draw("same p");
  }

  TCanvas *c3 = new TCanvas("c3","Clusters in X, Y, and Z",300,300,800,600);
  gBox3->Draw("p");
  gBox3->SetTitle("Clusters in X, Y, and Z");
  gBox3->GetXaxis()->SetTitle("X (cm)");
  gBox3->GetXaxis()->SetTitleOffset(1.5);
  gBox3->GetYaxis()->SetTitle("Y (cm)");
  gBox3->GetYaxis()->SetTitleOffset(1.5);
  gBox3->GetZaxis()->SetTitle("Z (cm)");
  gBox3->GetZaxis()->SetTitleOffset(1.5);
  for(i=0; i<iNData; i++){
    if(gData3[i]->GetN() == 1) gData3[i]->SetPoint(1,0,0,-1000);
    if(gData3[i]->GetN() == 0) gData3[i]->SetPoint(0,0,0,-1000);
    gData3[i]->Draw("same p");
  }
}
