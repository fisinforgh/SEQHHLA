// ============================================================================ 
// QHHLA SoftEdu - Quantum HHL Algorithm Educational Software                   
// ============================================================================ 
//
// Copyright (C) 2026
//
//   [1] Esteban Pico Rueda*						                       
//   [2] Julian Andrés Salamanca Bernal**                                      
//   [3] Diego Julián Rodríguez Patarroyo***				                   		           
//                                                                             
//   [1] smagudelog@udistrital.edu.co (Licenciada Universidad Distrital)        
//   [2] jasalamanca@udistrital.edu.co (profesor Universidad Distrital)        
//   [3] djrodriguezp@udistrital.edu.co (profesor Universidad Distrital)       
//									                                           
//  *,** Grupo de Física e Informática (FISINFOR)		                       
//  *** Grupo de Laboratorio de Fuentes Alternas de Energía (LIFAE)	           
//  *,**,*** Universidad Distrital Francisco José de Caldas (Bogotá, Colombia) 
//
//  
// Web page: https://github.com/fisinforgh/SEQHHLA.git 
//
// LICENSE: GNU General Public License v3.0 (GPLv3) or later
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================

#include "QHHLA_SoftEdu.h"
#include <TApplication.h>
#include <TGClient.h>
#include <TROOT.h> 
#include <TString.h>
#include <TGFrame.h>
#include <GuiTypes.h>
#include "TObjString.h"
#include "TObjArray.h"

const TString pathDIR_ICONS = "Icons/";

//* ==============================  -GUI DISING-  ============================= 
QHHLA_SoftEdu::QHHLA_SoftEdu(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p,w,h){

    // Color pallete for the background of the frames -------------------------
    Pixel_t colorWhite, colorLightBlue, colorLightGreen, colorGreen;
    gClient->GetColorByName("#ffffff", colorWhite);
    gClient->GetColorByName("#9cc1ec", colorLightBlue);
    gClient->GetColorByName("#aae9bf", colorLightGreen);
    gClient->GetColorByName("#66ccad", colorGreen);

    // Fonts 
    TGFont *menuFont = gClient->GetFont("-*-helvetica-bold-r-*-*-18-*-*-*-*-*-*-*");
    TGFont *submenuFont = gClient->GetFont("-*-arial-bold-r-narrow--16-*-*-*-*-*-iso8859-1");
    TGFont *labelFont = gClient->GetFont("-*-arial-medium-r-normal--14-*-*-*-*-*-iso8859-1");
    TGFont *buttonFont = gClient->GetFont("-*-helvetica-bold-r-*-*-12-*-*-*-*-*-*-*");

    //! Since this class IS the MainFrame, we call the methods directly -------
    SetBackgroundColor(colorWhite);

    // Intermediate container to organize Vframe1 (left) and Vframe2 (right).
    TGHorizontalFrame* HframeMiddle = new TGHorizontalFrame(this, 100, 100, kHorizontalFrame, colorWhite);

    //? HFRAME1: Title and logos layout ---------------------------------------
    Hframe1 = new TGHorizontalFrame(this,975,100, kHorizontalFrame | kRaisedFrame, colorWhite);
    Hframe1->SetName("Hframe1");
        LogoAPP = new TGIcon(Hframe1, pathDIR_ICONS + "APP.png");
        Hframe1->AddFrame(LogoAPP, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 5, 5, 5, 5));
        LogoAPP->MoveResize(30,10,190,90);

        LogoFINSIFOR = new TGIcon(Hframe1, pathDIR_ICONS + "logoFisinfor.png");
        Hframe1->AddFrame(LogoFINSIFOR, new TGLayoutHints(kLHintsRight | kLHintsCenterY, 10, 10, 10, 10));   
        LogoFINSIFOR->MoveResize(830,10,160,80);

        ECanvasTitle = new TRootEmbeddedCanvas("ECanvasTitle", Hframe1, 600, 50, 0);
        Hframe1->AddFrame(ECanvasTitle, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY | kLHintsExpandX, 5, 5, 5, 5));
            TCanvas *cTitle = ECanvasTitle->GetCanvas();
            cTitle->cd();
            cTitle->SetFillColor(colorWhite);
            cTitle->SetBorderMode(0);
                TPTTitle = new TPaveText(0, 0, 1, 1, "NDC"); 
                TPTTitle->SetTextFont(62);
                TPTTitle->SetTextAlign(22);
                TPTTitle->SetBorderSize(0);
                TPTTitle->SetFillStyle(0);
                TPTTitle->AddText("Quantum HHL Algorithm #color[2]{Soft}ware #color[4]{Edu}cation");
                TPTTitle->Draw();
            cTitle->Update();

    //? VFRAME1: Matrix and vector input layout -------------------------------
    Vframe1 = new TGVerticalFrame(HframeMiddle, 200, 560, kVerticalFrame | kRaisedFrame, colorWhite);
    Vframe1->SetName("Vframe1");

        LogoUD = new TGIcon(Vframe1, pathDIR_ICONS + "logoUD.png");
        Vframe1->AddFrame(LogoUD, new TGLayoutHints(kLHintsLeft | kLHintsBottom, 2, 2, 0, 5));
        LogoUD->SetBackgroundColor(colorWhite);
        LogoUD->MoveResize(10,460,245,70);

        GCValues_t valGFrameMENU;
        valGFrameMENU.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
        valGFrameMENU.fFillStyle = kFillSolid;
        valGFrameMENU.fFont = menuFont->GetFontHandle();
        valGFrameMENU.fGraphicsExposures = kFALSE;
        TGGC *uGC = gClient->GetGC(&valGFrameMENU, kTRUE);

        GFrameMENU = new TGGroupFrame(Vframe1, "MENU", kVerticalFrame | kRaisedFrame, uGC->GetGC(), menuFont->GetFontStruct(), colorWhite);        
        GFrameMENU->SetLayoutManager(new TGVerticalLayout(GFrameMENU));

            Vframe1a = new TGVerticalFrame(GFrameMENU,160,150, kVerticalFrame | kRaisedFrame, colorLightBlue);
            Vframe1a->SetLayoutManager(new TGVerticalLayout(Vframe1a));

                MatrixLabel = new TGLabel(Vframe1a, "Matrix A", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightBlue);
                MatrixLabel->SetTextJustify(kTextCenterX | kTextCenterY);
                MatrixLabel->SetTextFont(submenuFont->GetFontStruct());
                MatrixLabel->SetMargins(10, 10, 30, 0);
                Vframe1a->AddFrame(MatrixLabel, new TGLayoutHints(kLHintsCenterX | kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));

                    TGHorizontalFrame *RowA1 = new TGHorizontalFrame(Vframe1a, 160, 35, kHorizontalFrame | kOwnBackground, colorLightBlue);
                    RowA1->SetLayoutManager(new TGHorizontalLayout(RowA1));

                    A11Label = new TGLabel(RowA1, "A11", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightBlue);
                    A11Label->SetTextJustify(kTextCenterX | kTextCenterY);
                    A11Label->SetTextFont(labelFont->GetFontStruct());
                    A11Label->SetMargins(15,0,0,0);
                    RowA1->AddFrame(A11Label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 8, 5, 0, 0));

                    A11ComboBox = new TGComboBox(RowA1, -1, kHorizontalFrame | kOwnBackground, colorLightBlue);
                    A11ComboBox->AddEntry("", -1);
                    A11ComboBox->AddEntry(" -2", 0);
                    A11ComboBox->AddEntry(" -1", 1);
                    A11ComboBox->AddEntry("  0", 2);
                    A11ComboBox->AddEntry("  1", 3);
                    A11ComboBox->AddEntry("  2", 4);
                    A11ComboBox->AddEntry("  i", 5);
                    A11ComboBox->AddEntry(" 2i", 6);
                    A11ComboBox->AddEntry(" -i", 7);
                    A11ComboBox->AddEntry("-2i", 8);
                    A11ComboBox->Resize(35, 25);
                    A11ComboBox->Select(-1);
                    RowA1->AddFrame(A11ComboBox, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 3, 5, 0, 0));

                    A12Label = new TGLabel(RowA1, "A12", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightBlue);
                    A12Label->SetTextJustify(kTextCenterX | kTextCenterY);
                    A12Label->SetTextFont(labelFont->GetFontStruct());
                    A12Label->SetMargins(0,0,0,0);
                    RowA1->AddFrame(A12Label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 18, 5, 0, 0));

                    A12ComboBox = new TGComboBox(RowA1, -1, kHorizontalFrame | kOwnBackground, colorLightBlue);
                    A12ComboBox->AddEntry("", -1);
                    A12ComboBox->AddEntry(" -2", 0);
                    A12ComboBox->AddEntry(" -1", 1);
                    A12ComboBox->AddEntry("  0", 2);
                    A12ComboBox->AddEntry("  1", 3);
                    A12ComboBox->AddEntry("  2", 4);
                    A12ComboBox->AddEntry("  i", 5);
                    A12ComboBox->AddEntry(" 2i", 6);
                    A12ComboBox->AddEntry(" -i", 7);
                    A12ComboBox->AddEntry("-2i", 8);
                    A12ComboBox->Resize(35, 25);
                    A12ComboBox->Select(-1);
                    RowA1->AddFrame(A12ComboBox, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 3, 5, 0, 0));

            Vframe1a->AddFrame(RowA1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 0, 0, 0, 5));

                    TGHorizontalFrame *RowA2 = new TGHorizontalFrame(Vframe1a, 160, 35, kHorizontalFrame | kOwnBackground, colorLightBlue);
                    RowA2->SetLayoutManager(new TGHorizontalLayout(RowA2));

                    A21Label = new TGLabel(RowA2, "A21", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightBlue);
                    A21Label->SetTextJustify(kTextCenterX | kTextCenterY);
                    A21Label->SetTextFont(labelFont->GetFontStruct());
                    A21Label->SetMargins(15,0,0,0);
                    RowA2->AddFrame(A21Label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 8, 5, 0, 0));

                    A21ComboBox = new TGComboBox(RowA2, -1, kHorizontalFrame | kOwnBackground, colorLightBlue);
                    A21ComboBox->AddEntry("", -1);
                    A21ComboBox->AddEntry(" -2", 0);
                    A21ComboBox->AddEntry(" -1", 1);
                    A21ComboBox->AddEntry("  0", 2);
                    A21ComboBox->AddEntry("  1", 3);
                    A21ComboBox->AddEntry("  2", 4);
                    A21ComboBox->AddEntry("  i", 5);
                    A21ComboBox->AddEntry(" 2i", 6);
                    A21ComboBox->AddEntry(" -i", 7);
                    A21ComboBox->AddEntry("-2i", 8);
                    A21ComboBox->Resize(35, 25);
                    A21ComboBox->Select(-1);
                    RowA2->AddFrame(A21ComboBox, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 3, 5, 0, 0));

                    A22Label = new TGLabel(RowA2, "A22", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightBlue);
                    A22Label->SetTextJustify(kTextCenterX | kTextCenterY);
                    A22Label->SetTextFont(labelFont->GetFontStruct());
                    A22Label->SetMargins(0,0,0,0);
                    RowA2->AddFrame(A22Label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 18, 5, 0, 0));

                    A22ComboBox = new TGComboBox(RowA2, -1, kHorizontalFrame | kOwnBackground, colorLightBlue);
                    A22ComboBox->AddEntry("", -1);
                    A22ComboBox->AddEntry(" -2", 0);
                    A22ComboBox->AddEntry(" -1", 1);
                    A22ComboBox->AddEntry("  0", 2);
                    A22ComboBox->AddEntry("  1", 3);
                    A22ComboBox->AddEntry("  2", 4);
                    A22ComboBox->AddEntry("  i", 5);
                    A22ComboBox->AddEntry(" 2i", 6);
                    A22ComboBox->AddEntry(" -i", 7);
                    A22ComboBox->AddEntry("-2i", 8);
                    A22ComboBox->Resize(35, 25);
                    A22ComboBox->Select(-1);
                    RowA2->AddFrame(A22ComboBox, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 3, 5, 0, 0));

            Vframe1a->AddFrame(RowA2, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 0, 0, 5, 30));

        GFrameMENU->AddFrame(Vframe1a, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
        Vframe1a->MoveResize(10, 10, 170, 150);

            Vframe1b = new TGVerticalFrame(GFrameMENU,160,150, kVerticalFrame | kRaisedFrame, colorLightGreen);
            Vframe1b->SetLayoutManager(new TGVerticalLayout(Vframe1b));

                VectorLabel = new TGLabel(Vframe1b, "Vector b", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightGreen);
                VectorLabel->SetTextJustify(kTextCenterX | kTextCenterY);
                VectorLabel->SetTextFont(submenuFont->GetFontStruct());
                VectorLabel->SetMargins(10, 10, 30, 0);
                Vframe1b->AddFrame(VectorLabel, new TGLayoutHints(kLHintsCenterX | kLHintsTop | kLHintsExpandX, 2, 2, 2, 2));

                    TGHorizontalFrame *RowB1 = new TGHorizontalFrame(Vframe1b, 160, 35, kHorizontalFrame | kOwnBackground, colorLightGreen);
                    RowB1->SetLayoutManager(new TGHorizontalLayout(RowB1));

                    b1Label = new TGLabel(RowB1, "b1", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightGreen);
                    b1Label->SetTextJustify(kTextCenterX | kTextCenterY);
                    b1Label->SetTextFont(labelFont->GetFontStruct());
                    b1Label->SetMargins(5,0,0,0);
                    RowB1->AddFrame(b1Label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 60, 5, 0, 0));

                    b1ComboBox = new TGComboBox(RowB1, -1, kHorizontalFrame | kOwnBackground, colorLightGreen);
                    b1ComboBox->AddEntry("", -1);
                    b1ComboBox->AddEntry("-2", 0);
                    b1ComboBox->AddEntry("-1", 1);
                    b1ComboBox->AddEntry("0", 2);
                    b1ComboBox->AddEntry("1", 3);
                    b1ComboBox->AddEntry("2", 4);
                    b1ComboBox->Resize(35, 25);
                    b1ComboBox->Select(-1);
                    RowB1->AddFrame(b1ComboBox, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 3, 5, 0, 0));

            Vframe1b->AddFrame(RowB1, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 0, 0, 0, 5));

                    TGHorizontalFrame *RowB2 = new TGHorizontalFrame(Vframe1b, 160, 35, kHorizontalFrame | kOwnBackground, colorLightGreen);
                    RowB2->SetLayoutManager(new TGHorizontalLayout(RowB2));

                    b2Label = new TGLabel(RowB2, "b2", TGLabel::GetDefaultGC()(), TGLabel::GetDefaultFontStruct(), kChildFrame, colorLightGreen);
                    b2Label->SetTextJustify(kTextCenterX | kTextCenterY);
                    b2Label->SetTextFont(labelFont->GetFontStruct());
                    b2Label->SetMargins(5,0,0,0);
                    RowB2->AddFrame(b2Label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 60, 5, 0, 0));

                    b2ComboBox = new TGComboBox(RowB2, -1, kHorizontalFrame | kOwnBackground, colorLightGreen);
                    b2ComboBox->AddEntry("", -1);
                    b2ComboBox->AddEntry("-2", 0);
                    b2ComboBox->AddEntry("-1", 1);
                    b2ComboBox->AddEntry("0", 2);
                    b2ComboBox->AddEntry("1", 3);
                    b2ComboBox->AddEntry("2", 4);
                    b2ComboBox->Resize(35, 25);
                    b2ComboBox->Select(-1);
                    RowB2->AddFrame(b2ComboBox, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 3, 5, 0, 0));

            Vframe1b->AddFrame(RowB2, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 0, 0, 5, 30));

        GFrameMENU->AddFrame(Vframe1b, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
        Vframe1b->MoveResize(10, 185, 170, 125);

            HDivider = new TGHorizontal3DLine(GFrameMENU, 160, 2);
            GFrameMENU->AddFrame(HDivider, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,10,12));
            HDivider->MoveResize(10,338,210,2);

                ButtonSTART = new TGTextButton(GFrameMENU, "START",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kChildFrame);
                ButtonSTART->SetTextJustify(kTextCenterX | kTextCenterY);
                ButtonSTART->SetFont(buttonFont->GetFontStruct());
                ButtonSTART->SetMargins(0,0,5,5);
                ButtonSTART->SetWrapLength(-1);
                ButtonSTART->ChangeBackground(colorGreen);
                GFrameMENU->AddFrame(ButtonSTART, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,2,2,2,2));
                ButtonSTART->MoveResize(10,350,75,32);

                ButtonRESET = new TGTextButton(GFrameMENU, "RESET",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kChildFrame);
                ButtonRESET->SetTextJustify(kTextCenterX | kTextCenterY);
                ButtonRESET->SetFont(buttonFont->GetFontStruct());
                ButtonRESET->SetMargins(0,0,5,5);
                ButtonRESET->SetWrapLength(-1);
                ButtonRESET->ChangeBackground(colorGreen);
                GFrameMENU->AddFrame(ButtonRESET, new TGLayoutHints(kLHintsRight | kLHintsTop | kLHintsExpandX,2,2,2,2));
                ButtonRESET->MoveResize(10,390,75,32);

                ButtonHELP = new TGTextButton(GFrameMENU, "HELP",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kChildFrame);
                ButtonHELP->SetTextJustify(kTextCenterX | kTextCenterY);
                ButtonHELP->SetFont(buttonFont->GetFontStruct());
                ButtonHELP->SetMargins(0,0,5,5);
                ButtonHELP->SetWrapLength(-1);
                ButtonHELP->ChangeBackground(colorGreen);
                GFrameMENU->AddFrame(ButtonHELP, new TGLayoutHints(kLHintsRight | kLHintsTop | kLHintsExpandX,2,2,2,2));
                ButtonHELP->MoveResize(95,350,75,32);

                ButtonEXIT = new TGTextButton(GFrameMENU, "EXIT",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kChildFrame);
                ButtonEXIT->SetTextJustify(kTextCenterX | kTextCenterY);
                ButtonEXIT->SetFont(buttonFont->GetFontStruct());
                ButtonEXIT->SetMargins(0,0,5,5);
                ButtonEXIT->SetWrapLength(-1);
                ButtonEXIT->ChangeBackground(colorGreen);
                GFrameMENU->AddFrame(ButtonEXIT, new TGLayoutHints(kLHintsRight | kLHintsTop | kLHintsExpandX,2,2,2,10));
                ButtonEXIT->MoveResize(95,390,75,32); 

        GFrameMENU->Resize(180,590);
        Vframe1->AddFrame(GFrameMENU, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY,5,5,5,5));
        GFrameMENU->MoveResize(10,10,220,480);
    
    //? VFRAME2: Canvas tabs layout -------------------------------------------
    TGVerticalFrame* VframeRight = new TGVerticalFrame(HframeMiddle, 775, 560, kVerticalFrame, colorWhite);
    Vframe2 = new TGVerticalFrame(VframeRight, 775, 520, kVerticalFrame | kRaisedFrame, colorWhite);
    Vframe2->SetName("Vframe2");

        TabAlls = new TGTab(Vframe2, 96, 25);
        TabAlls->SetBackgroundColor(colorWhite);

            TabHOME = TabAlls->AddTab("HOME");
            TabHOME->SetLayoutManager(new TGVerticalLayout(TabHOME));
                ECanvasHOME = new TRootEmbeddedCanvas("ECanvasHOME", TabHOME, 750, 480);
                ECanvasHOME->SetName("ECanvasWELCOME");
                Int_t wECanvasHOME = ECanvasHOME->GetCanvasWindowId();
                TCanvas *c0 = new TCanvas("cWelcome", 10, 10, wECanvasHOME);
                ECanvasHOME->AdoptCanvas(c0);
            TabHOME->AddFrame(ECanvasHOME, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

            TabMATH = TabAlls->AddTab("MATH");
            TabMATH->SetLayoutManager(new TGVerticalLayout(TabMATH));
                ECanvasMATH = new TRootEmbeddedCanvas("ECanvasMATH", TabMATH, 750, 480);
                ECanvasMATH->SetName("ECanvasMATH");
                Int_t wECanvasMATH = ECanvasMATH->GetCanvasWindowId();
                TCanvas *c1 = new TCanvas("c1", 10, 10, wECanvasMATH);
                ECanvasMATH->AdoptCanvas(c1);
            TabMATH->AddFrame(ECanvasMATH, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

            TabMATRIX = TabAlls->AddTab("MATRIX");
            TabMATRIX->SetLayoutManager(new TGVerticalLayout(TabMATRIX));
                ECanvasMATRIX = new TRootEmbeddedCanvas("ECanvasMATRIX", TabMATRIX, 750, 480);
                ECanvasMATRIX->SetName("ECanvasMATRIX");
                Int_t wECanvasMATRIX = ECanvasMATRIX->GetCanvasWindowId();
                TCanvas *c2 = new TCanvas("c2", 10, 10, wECanvasMATRIX);
                ECanvasMATRIX->AdoptCanvas(c2);
            TabMATRIX->AddFrame(ECanvasMATRIX, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

            TabCIRCUIT = TabAlls->AddTab("CIRCUIT");
            TabCIRCUIT->SetLayoutManager(new TGVerticalLayout(TabCIRCUIT));
                ECanvasCIRCUIT = new TRootEmbeddedCanvas("ECanvasCIRCUIT", TabCIRCUIT, 750, 480);
                ECanvasCIRCUIT->SetName("ECanvasCIRCUIT");
                Int_t wECanvasCIRCUIT = ECanvasCIRCUIT->GetCanvasWindowId();
                TCanvas *c3 = new TCanvas("c3", 10, 10, wECanvasCIRCUIT);
                ECanvasCIRCUIT->AdoptCanvas(c3);
            TabCIRCUIT->AddFrame(ECanvasCIRCUIT, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

            TabGRAPH = TabAlls->AddTab("GRAPH");
            TabGRAPH->SetLayoutManager(new TGVerticalLayout(TabGRAPH));
                ECanvasGRAPH = new TRootEmbeddedCanvas("ECanvasGRAPH", TabGRAPH, 750, 480);
                ECanvasGRAPH->SetName("ECanvasGRAPH");
                Int_t wECanvasGRAPH = ECanvasGRAPH->GetCanvasWindowId();
                TCanvas *c4 = new TCanvas("c4", 10, 10, wECanvasGRAPH);
                ECanvasGRAPH->AdoptCanvas(c4);
            TabGRAPH->AddFrame(ECanvasGRAPH, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

        Vframe2->AddFrame(TabAlls, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

    //? HFRAME2: Lower buttons layout -----------------------------------------
    Hframe2 = new TGHorizontalFrame(VframeRight, 775, 30, kHorizontalFrame | kRaisedFrame, colorWhite);
    Hframe2->SetName("Hframe2");
    Hframe2->SetLayoutManager(new TGHorizontalLayout(Hframe2));

        ButtonPREVSTEP = new TGTextButton(Hframe2, "PREV STEP",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kChildFrame);
        ButtonPREVSTEP->SetTextJustify(kTextCenterX | kTextCenterY);
        ButtonPREVSTEP->SetFont(buttonFont->GetFontStruct());
        ButtonPREVSTEP->SetMargins(0,0,1,1);
        ButtonPREVSTEP->ChangeBackground(colorGreen);
        Hframe2->AddFrame(ButtonPREVSTEP, new TGLayoutHints(kLHintsLeft | kLHintsExpandX | kLHintsCenterY, 5, 2, 5, 5));

        ButtonNEXTSTEP = new TGTextButton(Hframe2, "NEXT STEP",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kChildFrame);
        ButtonNEXTSTEP->SetTextJustify(kTextCenterX | kTextCenterY);
        ButtonNEXTSTEP->SetFont(buttonFont->GetFontStruct());
        ButtonNEXTSTEP->SetMargins(0,0,1,1);
        ButtonNEXTSTEP->ChangeBackground(colorGreen);
        Hframe2->AddFrame(ButtonNEXTSTEP, new TGLayoutHints(kLHintsLeft | kLHintsExpandX | kLHintsCenterY, 2, 5, 5, 5));

        PButtonNEXT = new TGPictureButton(Hframe2, gClient->GetPicture(pathDIR_ICONS + "Next-Button.png"),-1,TGPictureButton::GetDefaultGC()(),kRaisedFrame);
        Hframe2->AddFrame(PButtonNEXT, new TGLayoutHints(kLHintsRight | kLHintsCenterY, 5, 2, 2, 2));
        
        PButtonCONCEPTS = new TGPictureButton(Hframe2, gClient->GetPicture(pathDIR_ICONS + "question-mark-button.png"),-1,TGPictureButton::GetDefaultGC()(),kRaisedFrame);
        Hframe2->AddFrame(PButtonCONCEPTS, new TGLayoutHints(kLHintsRight | kLHintsCenterY, 5, 2, 2, 2));

        PButtonBACK = new TGPictureButton(Hframe2, gClient->GetPicture(pathDIR_ICONS + "Back-Button.png"),-1,TGPictureButton::GetDefaultGC()(),kRaisedFrame);
        Hframe2->AddFrame(PButtonBACK, new TGLayoutHints(kLHintsRight | kLHintsCenterY, 5, 2, 2, 2));
        

    //? FINAL DESIGN ASSEMBLY -------------------------------------------------
    this->SetLayoutManager(new TGVerticalLayout(this));

    this->AddFrame(Hframe1, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 0, 0, 0, 0));

    HframeMiddle->AddFrame(Vframe1, new TGLayoutHints(kLHintsLeft | kLHintsExpandY, 0, 0, 0, 0));
    
    VframeRight->AddFrame(Vframe2, new TGLayoutHints(kLHintsTop | kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
    VframeRight->AddFrame(Hframe2, new TGLayoutHints(kLHintsBottom | kLHintsExpandX, 0, 0, 0, 0));
    
    HframeMiddle->AddFrame(VframeRight, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
    this->AddFrame(HframeMiddle, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));

    //? SIGNAL-SLOT CONNECTIONS -----------------------------------------------
    ButtonEXIT->Connect("Clicked()", "TApplication", gApplication, "Terminate(=0)");
    ButtonNEXTSTEP->Connect("Clicked()", "QHHLA_SoftEdu", this, "NextMacroStep()");
    ButtonPREVSTEP->Connect("Clicked()", "QHHLA_SoftEdu", this, "PrevMacroStep()");
    PButtonNEXT->Connect("Clicked()", "QHHLA_SoftEdu", this, "NextMicroStep()");
    PButtonBACK->Connect("Clicked()", "QHHLA_SoftEdu", this, "PrevMicroStep()");
    PButtonCONCEPTS->Connect("Clicked()", "QHHLA_SoftEdu", this, "DoConcepts()");
    ButtonSTART->Connect("Clicked()", "QHHLA_SoftEdu", this, "DoStart()");
    ButtonRESET->Connect("Clicked()", "QHHLA_SoftEdu", this, "DoReset()");
    ButtonHELP->Connect("Clicked()", "QHHLA_SoftEdu", this, "DoHelp()");

    //? STATE MACHINE CONFIGURATION (Micro-steps by Macro-steps) --------------
    // Initialization pointers to algebraic structures
    m_macroStep = 0;
    m_microStep = 0;
    m_isRunning = false;
    
    m_maxMicroSteps[0] = 0;
    m_maxMicroSteps[1] = 12;
    m_maxMicroSteps[2] = 10;
    m_maxMicroSteps[3] = 10;
    m_maxMicroSteps[4] = 20;
    m_maxMicroSteps[5] = 26;
    m_maxMicroSteps[6] = 14;
    m_maxMicroSteps[7] = 15;
    m_maxMicroSteps[8] = 17;

    
    //? INITIAL STATE: All navigation buttons disabled until START is pressed --
    DisableNavigationButtons();
    ButtonSTART->SetState(kButtonUp, kTRUE);   // START is active at the beginning

    // Go to CENTRAL RENDERING DIRECTOR
    UpdateVisuals();
    
    // Final window configuration ---------------------------------------------
    SetWindowName("Quantum HHL Algorithm SoftEdu");
    MapSubwindows();
    Resize(GetDefaultSize()); 
    MapWindow();

}

//* ========================= -BUTTON STATE CONTROL- ==========================
void QHHLA_SoftEdu::DisableNavigationButtons(){
    ButtonPREVSTEP->SetState(kButtonDisabled, kTRUE);
    ButtonNEXTSTEP->SetState(kButtonDisabled, kTRUE);
    PButtonBACK->SetState(kButtonDisabled, kTRUE);
    PButtonNEXT->SetState(kButtonDisabled, kTRUE);
    PButtonCONCEPTS->SetState(kButtonDisabled, kTRUE);
}

void QHHLA_SoftEdu::EnableNavigationButtons(){
    ButtonNEXTSTEP->SetState(kButtonUp, kTRUE);
    PButtonNEXT->SetState(kButtonUp, kTRUE);
    PButtonCONCEPTS->SetState(kButtonUp, kTRUE);
    //! PREV and BACK depend on the current step (step 1 = disabled)
    UpdateNavigationButtons();
}

//* ============================= -STATE CONTROL- =============================
void QHHLA_SoftEdu::UpdateNavigationButtons(){

    // Total blocking if we are in the initial state or the algorithm has not started
    if (m_macroStep == 0 || !m_isRunning) {
        DisableNavigationButtons();
        return;
    }

    // Logic for the BACK buttons (disabled in step 1)
    if (m_macroStep == 1 && m_microStep == 0) {
        ButtonPREVSTEP->SetState(kButtonDisabled, kTRUE);
        PButtonBACK->SetState(kButtonDisabled, kTRUE);
    } else {
        ButtonPREVSTEP->SetState(kButtonUp, kTRUE);
        PButtonBACK->SetState(kButtonUp, kTRUE);
    }
    
    // Logic for the ADVANCE buttons (disabled in step 8)
    if (m_macroStep == 8) {
        ButtonNEXTSTEP->SetState(kButtonDisabled, kTRUE);
        if (m_microStep == 17) {
            PButtonNEXT->SetState(kButtonDisabled, kTRUE);
        }
    } else {
        ButtonNEXTSTEP->SetState(kButtonUp, kTRUE);
        PButtonNEXT->SetState(kButtonUp, kTRUE);
    }
    
    // The CONCEPTS button is always enabled during the normal flow.
    PButtonCONCEPTS->SetState(kButtonUp, kTRUE);

}

void QHHLA_SoftEdu::NextMacroStep(){

    if (!m_isRunning || m_macroStep == 0) return; // Safety lock
    if (m_macroStep < 8) {
        m_macroStep++;
        m_microStep = 0;
        UpdateVisuals();
    }

}

void QHHLA_SoftEdu::PrevMacroStep(){

    if (!m_isRunning || m_macroStep <= 1) return; // Do not allow going back to step 0
    m_macroStep--;
    m_microStep = 0;
    UpdateVisuals();

}

void QHHLA_SoftEdu::NextMicroStep(){

    if (!m_isRunning || m_macroStep == 0) return; // Safety lock

    if (m_microStep < m_maxMicroSteps[m_macroStep]) {
        m_microStep++;
    } else if (m_macroStep < 8) {
        m_macroStep++; 
        m_microStep = 0;
    }

    UpdateVisuals();

}

void QHHLA_SoftEdu::PrevMicroStep(){

    if (!m_isRunning || m_macroStep == 0) return;

    if (m_microStep > 0) {
        m_microStep--;
    } else if (m_macroStep > 1) {
        m_macroStep--;
        m_microStep = m_maxMicroSteps[m_macroStep]; // Go to the last sub-step of the previous step
    }

    UpdateVisuals();
}

//* ============================ -WELCOME SCREEN- =============================
void QHHLA_SoftEdu::DoWelcome(){
    DisableNavigationButtons();
    std::cout << "[HOME] Welcome to Quantum HHL Algorithm" << std::endl;
    TabAlls->SetTab(0);
    
    // Get the 5 embedded canvases
    TCanvas *cWelcome = ECanvasHOME->GetCanvas();
    TCanvas *cMATH    = ECanvasMATH->GetCanvas();
    TCanvas *cMATRIX  = ECanvasMATRIX->GetCanvas();
    TCanvas *cCIRCUIT = ECanvasCIRCUIT->GetCanvas();
    TCanvas *cGRAPH   = ECanvasGRAPH->GetCanvas();
    
    // Clear all canvases
    cWelcome->Clear(); cWelcome->SetFillColor(0); cWelcome->SetEditable(1);
    cMATH->Clear();    cMATH->SetFillColor(0);    cMATH->SetEditable(1);
    cMATRIX->Clear();  cMATRIX->SetFillColor(0);  cMATRIX->SetEditable(1);
    cCIRCUIT->Clear(); cCIRCUIT->SetFillColor(0); cCIRCUIT->SetEditable(1);
    cGRAPH->Clear();   cGRAPH->SetFillColor(0);   cGRAPH->SetEditable(1);

    // ========================================================================
    // Helper lambda to build the two PaveText boxes
    // ========================================================================
    auto BuildDescriptionBox = [&]() -> TPaveText* {
        TPaveText *pt = new TPaveText(0.05, 0.25, 0.95, 0.95, "NDC");
        pt->SetFillColor(kTeal-9);
        pt->SetShadowColor(kGray+2);
        pt->SetTextAlign(12);
        pt->SetTextFont(42); 
        //pt->SetTextSize(0.03); 
        pt->SetMargin(0.05);
        pt->AddText(" ");
        pt->AddText("          #color[600]{#font[62]{#scale[1.8]{The Harrow-Hassidim-Lloyd (HHL) Quantum Algorithm}}}");
        pt->AddText(" ");
        pt->AddText("#font[62]{What it does:} The HHL algorithm solves systems of linear equations #font[62]{A#vec{x} = #vec{b}}  by harnessing quantum mechanical principles. Unlike ");
        pt->AddText("classical methods that scale polynomially with matrix size N, HHL offers an exponential speedup, scaling as O(log(N)) under ideal conditions.");
        pt->AddText("The algorithm encodes the classical vector #vec{b} into a quantum state |b#GT, performs Quantum Phase Estimation (QPE) to extract eigenvalues of ");
        pt->AddText("A, rotates an ancilla qubit to encode the inverse eigenvalues 1/#lambda_{j}, and finally applies uncomputation to isolate the solution state |x#GT.");
        pt->AddText("For more information about the HHL algorithm, please refer to the original paper: Harrow, A. W., Hassidim, A., & Lloyd, S. (2009). Quantum");
        pt->AddText("algorithm for linear systems of equations. Physical Review Letters, 103(15), 150502. https://doi.org/10.1103/PhysRevLett.103.150502");
        pt->AddText(" ");
        pt->AddText("#font[62]{Software Tour:} This educational laboratory guides you through #font[62]{8 sequential steps} of the algorithm, visualized simultaneously through");
        pt->AddText("#font[62]{4 complementary lenses}:");   
        pt->AddText("   #bullet  MATH: Analytical Dirac notation and algebraic derivations.");
        pt->AddText("   #bullet  MATRIX: Unitary matrices and column-vector state representations.");
        pt->AddText("   #bullet  CIRCUIT: Dynamic quantum circuit diagrams (Clock, Index & Ancilla registers).");
        pt->AddText("   #bullet  GRAPH: Bloch spheres, phasors, histograms and 2D geometric planes.");
        pt->AddText(" ");
        pt->AddText("                            #color[635]{#font[62]{#scale[1.4]{Press START to begin.}}}");
        return pt;
    };

    auto BuildAuthorsBox = [&]() -> TPaveText* {
        TPaveText *pt = new TPaveText(0.05, 0.05, 0.95, 0.23, "NDC");
        pt->SetFillColor(kAzure-8);
        pt->SetShadowColor(kGray+2);
        pt->SetTextAlign(22);
        pt->SetTextFont(42);
        pt->SetMargin(0.02);
        pt->AddText("#font[62]{#scale[1.2]{Authors}}");
        pt->AddText("Esteban Pico Rueda#font[62]{#scale[0.8]{^{1}}},  Julian A. Salamanca Bernal#font[62]{#scale[0.8]{^{2}}},  Diego J. Rodriguez Patarroyo#font[62]{#scale[0.8]{^{3}}}");
        pt->AddText("#scale[0.80]{Facultad Ciencias y Educacion#font[62]{#scale[0.7]{^{1,2}}},  Facultad Ingenieria#font[62]{#scale[0.7]{^{3}}},  Grupo de Fisica e Informatica  Fisinfor#font[62]{#scale[0.7]{^{1,2}}}, Grupo de Laboratorio de Fuentes Alternas de Energia  LIFAE#font[62]{#scale[0.7]{^{2,3}}}}");
        pt->AddText("Universidad Distrital Francisco Jose de Caldas.#font[62]{#scale[0.7]{^{1,2,3}}}");
        return pt;
    };

    // ========================================================================
    // HOME canvas
    // ========================================================================
    cWelcome->cd();
    TPaveText *ptDescHome = BuildDescriptionBox();
    TPaveText *ptAuthHome = BuildAuthorsBox();
    ptDescHome->Draw();
    ptAuthHome->Draw();
    cWelcome->Update();

    // ========================================================================
    // MATH canvas
    // ========================================================================
    cMATH->cd();
    TPaveText *ptDescMath = BuildDescriptionBox();
    TPaveText *ptAuthMath = BuildAuthorsBox();
    ptDescMath->Draw();
    ptAuthMath->Draw();
    cMATH->Update();

    // ========================================================================
    // MATRIX canvas
    // ========================================================================
    cMATRIX->cd();
    TPaveText *ptDescMatrix = BuildDescriptionBox();
    TPaveText *ptAuthMatrix = BuildAuthorsBox();
    ptDescMatrix->Draw();
    ptAuthMatrix->Draw();
    cMATRIX->Update();

    // ========================================================================
    // CIRCUIT canvas
    // ========================================================================
    cCIRCUIT->cd();
    TPaveText *ptDescCircuit = BuildDescriptionBox();
    TPaveText *ptAuthCircuit = BuildAuthorsBox();
    ptDescCircuit->Draw();
    ptAuthCircuit->Draw();
    cCIRCUIT->Update();

    // ========================================================================
    // GRAPH canvas
    // ========================================================================
    cGRAPH->cd();
    TPaveText *ptDescGraph = BuildDescriptionBox();
    TPaveText *ptAuthGraph = BuildAuthorsBox();
    ptDescGraph->Draw();
    ptAuthGraph->Draw();
    cGRAPH->Update();

    TabAlls->SetTab(0);
}

//* ============================== -HELP BUTTON- ==============================
void QHHLA_SoftEdu::DoHelp(){

    std::cout << "[HELP] Opening help TAB for te Sotware" << std::endl;

    // Create main help window
    TGTransientFrame* helpWindow = new TGTransientFrame(gClient->GetRoot(), this, 1050, 750);
    helpWindow->SetWindowName("HHL Algorithm - Help & Suggested Systems");
    helpWindow->SetMWMHints(kMWMDecorAll, kMWMFuncAll, 0);
    helpWindow->SetLayoutManager(new TGVerticalLayout(helpWindow));
    
    // Embedded canvas occupying the main area
    TRootEmbeddedCanvas *eCanvas = new TRootEmbeddedCanvas("eHelp", helpWindow, 1030, 680);
    helpWindow->AddFrame(eCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
    
    TCanvas *cHelp = eCanvas->GetCanvas();
    cHelp->SetFillColor(kWhite);
    cHelp->SetBorderMode(0);
    cHelp->cd();
    
    // ========================================================================
    // Split canvas into two vertical panels
    // ========================================================================
    TPad *padLeft = new TPad("padLeft", "User Guide", 0.00, 0.00, 0.50, 1.00);
    TPad *padRight = new TPad("padRight", "Suggested Systems", 0.50, 0.00, 1.00, 1.00);
    
    padLeft->SetFillColor(kWhite);
    padRight->SetFillColor(kWhite);
    padLeft->SetBorderMode(0);
    padRight->SetBorderMode(0);
    padLeft->SetLeftMargin(0.08);
    padLeft->SetRightMargin(0.04);
    padRight->SetLeftMargin(0.04);
    padRight->SetRightMargin(0.08);
    
    padLeft->Draw();
    padRight->Draw();
    
    // ========================================================================
    // LEFT PANEL: User Guide
    // ========================================================================
    padLeft->cd();
    
    TPaveText *ptLeft = new TPaveText(0.02, 0.02, 0.98, 0.98, "NDC");
    ptLeft->SetFillColor(kWhite);
    ptLeft->SetBorderSize(2);
    ptLeft->SetLineColor(kBlue-3);
    ptLeft->SetLineWidth(2);
    ptLeft->SetShadowColor(kGray+1);
    ptLeft->SetTextAlign(12);
    ptLeft->SetTextFont(42);
    ptLeft->SetTextSize(0.022);
    ptLeft->SetMargin(0.04);
    
    ptLeft->AddText(" ");
    ptLeft->AddText("#font[62]{#color[600]{#scale[1.35]{Quantum HHL Algorithm - User Guide}}}");
    ptLeft->AddText(" ");
    ptLeft->AddText("#font[62]{#color[419]{#scale[1.1]{Getting Started}}}");
    ptLeft->AddText(" ");
    ptLeft->AddText("1. Use the dropdown menus in the left panel to select the values for Matrix A (2x2) and Vector b.");
    ptLeft->AddText("   Available values: integers {-2,-1,0,1,2} and imaginary units {i, 2i, -i, -2i} for the off-diagonal entries.");
    ptLeft->AddText(" ");
    ptLeft->AddText("2. The software validates that A is #font[62]{Hermitian} (A = A^{+}):");
    ptLeft->AddText("   #bullet Diagonal entries must be strictly real.");
    ptLeft->AddText("   #bullet A12 must equal the complex conjugate of A21.");
    ptLeft->AddText("   #bullet The determinant must be non-zero (invertible matrix).");
    ptLeft->AddText("   #bullet Vector b cannot be the zero vector.");
    ptLeft->AddText(" ");
    ptLeft->AddText("3. Press #font[62]{START} to initialize the algorithm. Navigation buttonswill activate and the tour will begin at Step 1.");
    ptLeft->AddText(" ");
    ptLeft->AddText("#font[62]{#color[419]{#scale[1.1]{Navigation Controls}}}");
    ptLeft->AddText(" ");
    ptLeft->AddText("#bullet #font[62]{START:}  Validates input and launches the HHL simulation.");
    ptLeft->AddText("#bullet #font[62]{RESET:}  Clears all data and returns to the welcome screen.");
    ptLeft->AddText("#bullet #font[62]{NEXT STEP:}  Advances to the next major step (1 to 8).");
    ptLeft->AddText("#bullet #font[62]{PREV STEP:}  Goes back to the previous major step.");
    ptLeft->AddText("#bullet #font[62]{NEXT >>:}  Advances one micro-step within the current stage.");
    ptLeft->AddText("#bullet #font[62]{BACK <<:}  Retreats one micro-step.");
    ptLeft->AddText("#bullet #font[62]{CONCEPTS (?):}  Opens context-sensitive help for the current step, explaining the math, matrix,");
    ptLeft->AddText("   circuit and graph views.");
    ptLeft->AddText("#bullet #font[62]{HELP:}  Opens this guide window.");
    ptLeft->AddText("#bullet #font[62]{EXIT:}  Closes the application.");
    ptLeft->AddText(" ");
    ptLeft->AddText("#font[62]{#color[419]{#scale[1.1]{Visualization Tabs}}}");
    ptLeft->AddText(" ");
    ptLeft->AddText("#bullet #font[62]{HOME:}  Welcome screen with project overview and authors.");
    ptLeft->AddText("#bullet #font[62]{MATH:}  Real-time Dirac notation and algebraic derivations.");
    ptLeft->AddText("#bullet #font[62]{MATRIX:}  Unitary matrices and column-vector states.");
    ptLeft->AddText("#bullet #font[62]{CIRCUIT:}  Dynamic quantum circuit diagrams.");
    ptLeft->AddText("#bullet #font[62]{GRAPH:}  Bloch spheres, phasors, histograms and 2D geometry.");
    ptLeft->AddText(" ");
    ptLeft->AddText("#font[62]{#color[419]{#scale[1.1]{Context-Sensitive Concepts}}}");
    ptLeft->AddText(" ");
    ptLeft->AddText("Press the #font[62]{CONCEPTS} button at any time to open a detailed panel tailored to your current step and ");
    ptLeft->AddText("micro-step. It provides specific insight into the Overview, Math, Matrix, Circuit and Graph perspectives.");
    ptLeft->AddText(" ");
    ptLeft->AddText("#font[62]{#color[635]{Tip:}} Use the micro-step navigation to follow the algorithm at your own pace and observe how each operation");
    ptLeft->AddText("transforms the quantum state across all four visualization dimensions.");
    ptLeft->AddText(" ");
    ptLeft->Draw();
    
    // ========================================================================
    // RIGHT PANEL: Suggested Systems
    // ========================================================================
    padRight->cd();
    
    // Title for the right panel
    TLatex *titleRight = new TLatex(0.5, 0.96, 
        "#font[62]{#color[600]{#scale[1.1]{Suggested Practice Systems}}}");
    titleRight->SetNDC();
    titleRight->SetTextAlign(22);
    titleRight->SetTextSize(0.040);
    titleRight->Draw();
    
    // Subtitle
    TLatex *subRight = new TLatex(0.5, 0.92, 
        "#color[635]{Enter these values in Matrix A and Vector b, then press START}");
    subRight->SetNDC();
    subRight->SetTextAlign(22);
    subRight->SetTextSize(0.025);
    subRight->Draw();
    
    // Lambda to draw each suggested system using TString values.
    // You can replace any value with integers, 'i', '2i', '-i', '1+i', etc.
    auto DrawSystem = [&](Double_t yPos, 
                        const char* a11, const char* a12, 
                        const char* a21, const char* a22,
                        const char* x1,  const char* x2,
                        const char* b1,  const char* b2) 
    {
        // Background box for visual grouping
        TBox *sysBox = new TBox(0.05, yPos - 0.02, 0.95, yPos + 0.11);
        sysBox->SetFillColor(kCyan-9);
        sysBox->SetLineColor(kBlue-3);
        sysBox->SetLineWidth(1);
        sysBox->Draw("l");
        
        
        // Matrix equation: A * x = b (using provided TString values)
        TString eq = TString::Format(
            "#color[1]{#left[ #splitline{%s}{%s} #splitline{%s}{%s} #right]} "
            "#color[632]{#left[ #splitline{%s}{%s} #right]} "
            "#color[1]{=} "
            "#color[1]{#left[ #splitline{%s}{%s} #right]}",
            a11, a21, a12, a22,   // Matrix A (column-major in splitline)
            x1, x2,               // Solution vector x
            b1, b2                // Vector b
        );
        
        TLatex *lEq = new TLatex(0.50, yPos + 0.045, eq.Data());
        lEq->SetNDC();
        lEq->SetTextAlign(22);
        lEq->SetTextFont(42);
        lEq->SetTextSize(0.040);
        lEq->SetTextColor(kBlack);
        lEq->Draw();
    
    };
    
    // System 1:
    TString s1_a11="2", s1_a12="1", s1_a21="1", s1_a22="2";
    TString s1_x1="x_{1}",  s1_x2="x_{2}";
    TString s1_b1="1",  s1_b2="0";
    DrawSystem(0.78, s1_a11, s1_a12, s1_a21, s1_a22, s1_x1, s1_x2, s1_b1, s1_b2);
    
    // System 2: 
    TString s2_a11="1", s2_a12="2", s2_a21="2", s2_a22="1";
    TString s2_x1="x_{1}",  s2_x2="x_{2}";
    TString s2_b1="1",  s2_b2="-2";
    DrawSystem(0.60, s2_a11, s2_a12, s2_a21, s2_a22, s2_x1, s2_x2, s2_b1, s2_b2);
    
    // System 3: 
    TString s3_a11="2", s3_a12="i", s3_a21="-i", s3_a22="2";
    TString s3_x1="x_{1}",  s3_x2="x_{2}";
    TString s3_b1="0",  s3_b2="-2";
    DrawSystem(0.42, s3_a11, s3_a12, s3_a21, s3_a22, s3_x1, s3_x2, s3_b1, s3_b2);
    
    // System 4: 
    TString s4_a11="-1", s4_a12="2i", s4_a21="-2i", s4_a22="-1";
    TString s4_x1="x_{1}",  s4_x2="x_{2}";
    TString s4_b1="2",  s4_b2="0";
    DrawSystem(0.24, s4_a11, s4_a12, s4_a21, s4_a22, s4_x1, s4_x2, s4_b1, s4_b2);
    
    // System 5:
    TString s5_a11="0", s5_a12="-2i", s5_a21="2i", s5_a22="0";
    TString s5_x1="x_{1}",  s5_x2="x_{2}";
    TString s5_b1="-1",  s5_b2="0";
    DrawSystem(0.06, s5_a11, s5_a12, s5_a21, s5_a22, s5_x1, s5_x2, s5_b1, s5_b2);

    // ========================================================================
    // Close button
    // ========================================================================
    TGTextButton* closeButton = new TGTextButton(helpWindow, "Close Help", 1);
    closeButton->Connect("Clicked()", "TGTransientFrame", helpWindow, "CloseWindow()");
    helpWindow->Connect("CloseWindow()", "TGTransientFrame", helpWindow, "DeleteWindow()");
    helpWindow->AddFrame(closeButton, new TGLayoutHints(kLHintsCenterX | kLHintsBottom, 5, 5, 5, 12));
    
    helpWindow->SetCleanup(kDeepCleanup);
    helpWindow->MapSubwindows();
    helpWindow->Resize(GetDefaultSize());
    helpWindow->MapWindow();

}

//* ================================ -CONCEPTS- ===============================
void QHHLA_SoftEdu::DoConcepts() {

    std::cout << "[Concepts] Opening context-sensitive help for Step " << m_macroStep << std::endl;
    
    // Create main concepts window
    TGTransientFrame* conceptsWindow = new TGTransientFrame(gClient->GetRoot(), this, 850, 650);
    conceptsWindow->SetWindowName("HHL Algorithm - Step Concepts");
    conceptsWindow->SetMWMHints(kMWMDecorAll, kMWMFuncAll, 0);
    conceptsWindow->SetLayoutManager(new TGVerticalLayout(conceptsWindow));
    
    // Create embedded canvas for concepts display  
    TRootEmbeddedCanvas *eCanvas = new TRootEmbeddedCanvas("eConcepts", conceptsWindow, 830, 550);
    conceptsWindow->AddFrame(eCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));
    
    TCanvas *cConcepts = eCanvas->GetCanvas();
    cConcepts->SetFillColor(kWhite);
    cConcepts->SetBorderMode(0);
    cConcepts->cd();
    
    // Create a TPaveText to display the concepts
    TPaveText *pt = new TPaveText(0.02, 0.02, 0.98, 0.98, "NDC");
    pt->SetFillColor(kWhite);
    pt->SetBorderSize(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    pt->SetMargin(0.02);
    
    // ------------------------------------------------------------------------
    // Populate the TPaveText with content based on the current macro step
    // ------------------------------------------------------------------------
    
    // --- STEP TITLE ---
    TString stepTitle = GetStepTitle(m_macroStep);
    pt->AddText(" ");
    pt->AddText(TString::Format("#color[600]{#font[62]{#scale[1.3]{%s}}}", stepTitle.Data()));
    pt->AddText(" ");
    
    // --- SECTION: OVERVIEW ---
    pt->AddText("#font[62]{#color[419]{OVERVIEW}}");
    AddConceptLines(pt, GetOverviewText(m_macroStep, m_microStep));
    pt->AddText(" ");
    
    // --- SECTION: MATH TAB ---
    pt->AddText("#font[62]{#color[419]{MATH TAB}}");
    AddConceptLines(pt, GetMathText(m_macroStep, m_microStep));
    pt->AddText(" ");
    
    // --- SECTION: MATRIX TAB ---
    pt->AddText("#font[62]{#color[419]{MATRIX TAB}}");
    AddConceptLines(pt, GetMatrixText(m_macroStep, m_microStep));
    pt->AddText(" ");

    // --- SECTION: CIRCUIT TAB ---
    pt->AddText("#font[62]{#color[419]{CIRCUIT TAB}}");
    AddConceptLines(pt, GetCircuitText(m_macroStep, m_microStep));
    pt->AddText(" ");

    // --- SECTION: GRAPH TAB ---
    pt->AddText("#font[62]{#color[419]{GRAPH TAB}}");
    AddConceptLines(pt, GetGraphText(m_macroStep, m_microStep));
    pt->AddText(" ");
    
    pt->Draw();
    cConcepts->Update();

    // Close button to exit the concepts window 
    TGTextButton* closeButton = new TGTextButton(conceptsWindow, "Close Concepts", 1);
    closeButton->Connect("Clicked()", "TGTransientFrame", conceptsWindow, "CloseWindow()");
    conceptsWindow->Connect("CloseWindow()", "TGTransientFrame", conceptsWindow, "DeleteWindow()");
    conceptsWindow->AddFrame(closeButton, new TGLayoutHints(kLHintsCenterX | kLHintsBottom, 5, 5, 10, 15));
    
    // Final configuration and display of the concepts window
    conceptsWindow->SetCleanup(kDeepCleanup);
    conceptsWindow->MapSubwindows();
    conceptsWindow->Resize(GetDefaultSize());
    conceptsWindow->MapWindow();

}

// Helper function to add multiple lines to TPaveText while respecting \n.  
void QHHLA_SoftEdu::AddConceptLines(TPaveText *pt, const TString& text) {

    // Split the text by '\n' and add each line separately.
    TObjArray *lines = text.Tokenize("\n");
    TIter next(lines);
    TObject *obj;

    while ((obj = next())) {
        TString line = ((TObjString*)obj)->GetString().Strip(TString::kBoth);
        if (line.Length() > 0) {
            pt->AddText(line.Data());
        }
    }

    delete lines;

}

// HELPER: Get step title
TString QHHLA_SoftEdu::GetStepTitle(Int_t step) {

    switch(step) {
        case 1: return "Step 1: Quantum Problem Preparation";
        case 2: return "Step 2: Quantum System Initialization";
        case 3: return "Step 3: Time Superposition";
        case 4: return "Step 4: Controlled Unitary Evolution";
        case 5: return "Step 5: Inverse Quantum Fourier Transform (IQFT)";
        case 6: return "Step 6: Controlled Rotation & Eigenvalue Inversion";
        case 7: return "Step 7: Uncomputing (IQPE)";
        case 8: return "Step 8: Measurement & Post-selection";
        default: return "Unknown Step";
    }

}

// HELPER: Overview text (general description)
TString QHHLA_SoftEdu::GetOverviewText(Int_t step, Int_t microStep) {

    if (step == 1) {
        return  
            "Step 1 transforms the classical linear system #font[52]{#font[62]{A}#vec{x}=#vec{b}} into a quantum-ready format through classical preprocessing. The software demonstrates vector #font[52]{#vec{b}}\n"
            "normalization to ensure unit norm, performs spectral decomposition of matrix #font[52]{#font[62]{A}} to find its eigenvalues #font[52]{(#lambda_{1}, #lambda_{2})} and corresponding eigenvectors, calculates\n" 
            "expansion coefficients #font[52]{#beta=#LTu#scale[0.7]{j}|b#GT}, and prepares the Index Register with the quantum state #font[52]{|b#GT=#beta_{1}|u_{1}#GT+#beta_{2}|u_{2}#GT}. This classical foundation is essential for the\n"
            "quantum algorithm to encode and solve the problem.";
        }

    if (step == 2) {
        return 
            "Step 2 initializes the complete quantum system by defining three fundamental registers and preparing the global initial state. The software demonstrates clock register\n"
            "resolution (determining the number of qubits m needed to encode eigenvalues in binary), defines the Clock Register (#font[52]{|0#GT_{C}}), Index Register (#font[52]{|b#GT_{I}}), and Ancilla Register (#font[52]{|0#GT_{A}}),\n"
            "and constructs the global initial state #font[52]{|#Psi_{0}#GT=|0#GT_{C}#otimes|b#GT_{I}#otimes|0#GT_{A}} through tensor product. This step establishes the quantum architecture that will evolve through the HHL algorithm.";
    }

    if (step == 3) {
        return 
            "Step 3 applies Hadamard gates to each qubit of the Clock Register, creating an equiprobable superposition of all possible time states #font[52]{|t#GT} from 0 to #font[52]{2^{m-1}}. This quantum\n"
            "parallelism allows the algorithm to evaluate the unitary evolution #font[52]{U^{t}} for all values of t simultaneously. The Index and Ancilla registers remain unchanged during this step,\n" 
            "preserving the encoded problem data while the Clock Register becomes the source of quantum speedup in the HHL algorithm.";
    }

    if (step == 4) {
        return 
            "Step 4 implements the core of the Quantum Phase Estimation (QPE) subroutine through controlled unitary evolution. The system applies the operator #font[52]{U=e^{iA#tau}} controlled by the Clock\n" 
            "Register, encoding the eigenvalues #font[52]{#lambda_{j}} into phase factors. This creates entanglement between the Clock and Index registers, where each time state #font[52]{|t#GT} controls a different power \n"
            "of the unitary evolution. The critical time scale factor #tau is chosen to prevent phase aliasing (wrap-around), ensuring #font[52]{#lambda_{max}#tau<2#pi} so that all phases remain uniquely distinguishable in the\n"
            "range [0, 2#pi).";
    }

    if (step == 5 ) {
        return 
            "Step 5 applies the Inverse Quantum Fourier Transform (IQFT) to the Clock Register, acting as a frequency decoder that converts the phase information encoded in Step 4 into\n" 
            "measurable computational basis states. The IQFT reverses the phase spreading, generating pure constructive interference at the binary state corresponding to the eigenvalue #font[52]{#lambda_{j}},\n"
            "while canceling (destructive interference) all other probabilities. This step is the mathematical heart of Quantum Phase Estimation (QPE), where the combined operations of\n"
            "Steps 3 (Hadamard), 4 (Controlled Unitary Evolution), and 5 (IQFT) form the complete QPE subroutine that extracts eigenvalue information from the quantum system.";
    }
    
    if (step == 6) {
        return 
            "Step 6 implements the core eigenvalue inversion mechanism of the HHL algorithm through controlled Y-rotation on the ancilla qubit. The software demonstrates how applying a rotation\n"
            "R_{y}(#theta_j) with angle #font[52]{θ_{j}=2arcsin(C/#lambda_{j})} encodes the inverse eigenvalue #font[52]{1/#lambda_{j}} into the probability amplitude of the #font[52]{|1#GT_{A}} state. The normalization constant #font[52]{C#leqmin|#lambda_{j}|} ensures physically\n"
            "valid rotation angles. This step creates entanglement between the Clock Register (holding eigenvalue information) and the Ancilla qubit, where smaller eigenvalues produce larger \n"
            "rotations (more amplitude in #font[52]{1/#lambda_{j}}) and larger eigenvalues produce smaller rotations (less amplitude in #font[52]{1/#lambda_{j}}), achieving the eigenvalue inversion required to solve #font[52]{A#vec{x}=#vec{b}}.";
    }

    if (step == 7) {
        return 
            "Step 7 applies the Inverse Quantum Phase Estimation (IQPE), which is the exact inverse of the QPE subroutine performed in Steps 3, 4, and 5. Its purpose is to disentangle the Clock\n"
            "Register from the Index Register by reversing the phase encoding, returning the Clock to its initial state #font[52]{|0#GT^{#otimesm}}. This uncomputing step is crucial because it isolates the eigenvalue\n"
            "inversion information (encoded in the Ancilla amplitudes) from the eigenvalue labels (stored in the Clock), making the system separable and preparing it for the final measurement in Step 8.";
    }
    
    if (step == 8) {
        return 
            "Step 8 is the final stage of the HHL algorithm where the quantum solution is extracted through measurement and post-selection. The software demonstrates the factorization of the global\n"
            "state by ancilla branches, calculates the success probability #font[52]{P(|1#GT)} of measuring the ancilla in state #font[52]{|1#GT}, shows the wave function collapse when post-selecting the #font[52]{|1#GT} outcome, and presents \n"
            "the normalized solution state #font[52]{|x#GT}. Finally, it validates the quantum result by comparing it with the classical solution, demonstrating that both vectors are parallel and differ only by a normalization\n"
            "factor #font[52]{N}, confirming that the quantum state encodes #font[52]{A^{-1}|b#GT}.";
    }

    return "Overview not available for this microstep.";

}

// HELPER: Math text descriptions
TString QHHLA_SoftEdu::GetMathText(Int_t step, Int_t microStep) {

    if (step == 1) {
        return 
            "The tab displays real-time Dirac notation and algebraic equations. It shows vector #font[52]{#vec{b}} normalization using #font[52]{||b||=#sum|b#scale[0.7]{i}|^{2}} to create the normalized quantum \n"
            "state, the characteristic equation #font[52]{det(A-#lambdaI)=0} yielding the eigenvalues #font[52]{#lambda_{1}} and #font[52]{#lambda_{2}}, the corresponding orthonormal eigenvectors #font[52]{|u_{1}#GT} and #font[52]{|u_{2}#GT},\n" 
            "and the expansion #font[52]{|b#GT=#beta_{1}|u_{1}#GT+#beta_{2}|u_{2}#GT} where #font[52]{#beta = #LTu_{j}|b#GT}.";
    }

    if (step == 2) {
        return 
            "The tab shows clock register resolution calculations including eigenvalue binary representation (#font[52]{#lambda_{1}} and #font[52]{#lambda_{2}} in binary), phase resolution values (#font[52]{0/2^{m}}, #font[52]{1/2^{m}}, ..., #font[52]{(2^{m-1})/2^{m}}),\n"
            "quantum register definitions for Clock (#font[52]{|0#GT_{C}^{#otimes m}}), Index (#font[52]{|b#GT_{I}}), and Ancilla (#font[52]{|0#GT_{A}}) registers, the global initial state #font[52]{|#Psi_{0}#GT = |0#GT_{C}^{#otimes m} #otimes |b#GT_{I} #otimes |0#GT_{A}} and eigenvector expansion ,\n"
            "substituting #font[52]{|b#GT} by its spectral decomposition #font[52]{#beta_{1}|u_{1}#GT + #beta_{2}|u_{2}#GT}.\n"
            "#color[635]{When eigenvalues can be negative, an extra qubit is added as a sign bit (two's complement representation) With m=3 qubits: range is -4 to +3. #font[62]{Binary states: |011#GT=+3,}}\n"
            "#color[635]{#font[62]{|010#GT=+2, |001#GT=+1, |000#GT=0, |111#GT=-1, |110#GT=-2, |101#GT=-3, |100#GT=-4.}}";
    }

    if (step == 3) {
        return 
            "The tab displays the Hadamard action on the Clock Register #font[52]{H^{#otimesm}|0...0#GT_{C}^{m}}. It shows the time interpretation as an equiprobable superposition of integer times t with both,\n"
            "decimal and binary representations of the states. The resulting global state #font[52]{|#Psi_{1}#GT} is displayed, combining the Clock superposition with the Index Register spectral\n" 
            "decomposition #font[52]{#beta_{1}|u_{1}#GT+#beta_{2}|u_{2}#GT} and the Ancilla state #font[52]{|0#GT_{A}}, demonstrating how quantum parallelism enables simultaneous evaluation of all time steps.";
    }

    if (step == 4) {
        return
            "The tab displays the time scale factor calculation #font[52]{#tau=2#pi/2^{m}} to prevent phase aliasing. It shows the Hamiltonian evolution #font[52]{e^{iA#tau}|u_{j}#GT=e^{i#lambda_{j}#tau}|u_{j}#GT} the clock-index connection #font[52]{#hat{U}^{t}|b#GT = e^{i#lambda_{j}t#tau}|b#GT},\n"
            "and the evolved global state #font[52]{|#Psi_{2}#GT} as a sum over all time steps with phase factors. The unitary operator matrix #font[52]{#hat{U} = e^{iA#tau}} is displayed in the eigenbasis as a diagonal matrix with entries\n"
            "#font[52]{e^{i#lambda_{1}#tau}} and #font[52]{e^{i#lambda_{2}#tau}} showing how each eigenvalue branch accumulates phase independently.";
    }

    if (step == 5 && microStep <= 11) {
        return 
            "The tab displays the complete algebraic development of the IQFT application. Starting from the clock register state #scale[1.3]{|#phi_{j}#GT = #frac{1}{#sqrt{2^{m}}}}#sum_{#scale[1.3]{t=0}}^{#scale[1.3]{2^{m}-1}}#scale[1.3]{e^{(2#pii#theta_{j}t)}|t#GT_{C}} where #scale[1.3]{#theta_{j}=#lambda_{j}#tau/2#pi},\n" 
            "\\quad\n"
            "\\quad\n"
            "the IQFT operator is #scale[1.3]{IQFT(|t#GT) = #frac{1}{#sqrt{2^{m}}}}#sum_{#scale[1.5]{y=0}}^{#scale[1.3]{2^{m}-1}}#scale[1.3]{e^{(-2#piity/2^{m})}|y#GT_{C}} "
            "applying the operator: #scale[1.3]{IQFT|#phi_{j}#GT #Rightarrow}  #scale[1.3]{#frac{1}{#sqrt{2^{m}}}}#sum_{#scale[1.3]{t=0}}^{#scale[1.3]{2^{m}-1}}#scale[1.3]{e^{(2#pii#theta_{j}t)}}#scale[1.3]{ #upoint #frac{1}{#sqrt{2^{m}}}}#sum_{#scale[1.5]{y=0}}^{#scale[1.3]{2^{m}-1}}#scale[1.3]{e^{(-2#piity/2^{m})}|y#GT_{C}}\n"
            "\\quad\n"
            "\\quad\n"
            "the expression becomes a double summation. Grouping the summations and factoring the common exponent #scale[1.3]{2#piit}, the final form is "
            "#scale[1.3]{|#phi_{j}#GT=#frac{1}{2^{m}}}#sum_{#scale[1.3]{y=0}}^{#scale[1.3]{2^{m}-1}} #sum_{#scale[1.3]{t=0}}^{#scale[1.3]{2^{m}-1}}#scale[1.3]{e^{2#piit#left(#theta_{j} - #frac{y}{2^{m}}#right)}|y#GT_{C}}.\n"
            "\\quad\n"
            "#font[62]{PHYSICAL PHENOMENON:} The key is the phase difference #scale[1.3]{#Delta = #theta_{j} - y/2^{m}}. The inner sum becomes a geometric series with ratio #scale[1.3]{r = e^{2#pii#Delta}}.\n"
            "#bullet Constructive interferenciente: When #scale[1.3]{y = #tilde{y}} (the resonant state), #scale[1.3]{#Delta = 0}, so all #font[52]{2^{m}} vectors point in the same direction (positive real axis), forming a straight line \n"
            "  of length #scale[1.3]{2^{m}}, giving amplitude 1 and probability 100%.\n" 
            "#bullet Destructive interference: When #scale[1.3]{y #neq #tilde{y}}, #scale[1.3]{#Delta = k/2^{m}} (k integer), each successive vector rotates by angle #scale[1.3]{2#pik/2^{m}}, tracing a regular polygon that closes exactly \n"
            "  at the origin after #scale[1.3]{2^{m}} terms, giving amplitude 0 and probability 0. This is why only the eigenvalue state survives after IQFT.";   
    }

    if (step == 6 && microStep <= 4) {
        return 
            "The tab displays the complete mathematical derivation of the eigenvalue inversion angle. Starting from the rotation angle definition #font[52]{#theta_{j}=2arcsin(C/#lambda_{j})} where #font[52]{C#leqmin|#lambda_{j}|} ensures valid\n"
            "arguments, the software shows the rotation operation #font[52]{R_{y}(#theta_{j})|0#GT_{A}=cos(#theta_{j}/2)|0#GT_{A}+sin(#theta_{j}/2)|1#GT_{A}}. Using the trigonometric identity #font[52]{sin(arcsin(x))=x}, the amplitude of #font[52]{|1#GT} becomes\n"
            "#font[52]{sin(#theta_{j}/2)=C/#lambda_{j}}, directly encoding the inverse eigenvalue. The cosine term uses #font[52]{cos(arcsin(x))=#sqrt{1 - x^{2}}}, giving #font[52]{cos(#theta_{j}/2)=#sqrt{1 - C^{2}/#lambda_{j}^{2}}}. The resulting global state\n"
            "\\quad\n"
            "#font[52]{|#Psi_{4}#GT=}#sum_{j}#font[52]{#beta_{j}|#lambda_{j}#GT_{C} #otimes |u_{j}#GT_{I} #otimes #left(#sqrt{1 - C^{2}/#lambda_{j}^{2}}|0#GT_{A} + C/#lambda_{j}|1#GT_{A}#right)} shows how each eigenvalue branch produces different ancilla amplitudes, with the #font[52]{|1#GT} probability proportional to #font[52]{1/#lambda_{j}^{2}}.";
    }

    if (step == 7) {
        return 
            "The tab displays the anatomy of the uncomputing operator #font[52]{#hat{U}_{IQPE}}, which is the product of the three inverses applied in reverse order. It shows the mathematical unraveling of #font[52]{#hat{U}_{IQPE}}\n"
            "acting on #font[52]{|#Psi_{4}#GT}, demonstrating how the Clock Register returns to #font[52]{|0#GT^{#otimesm}} while the Index and Ancilla registers retain the eigenvalue inversion information. The resulting global state \n"
            "#font[52]{|#Psi_{5}#GT} shows that the Clock has been factorized out of the summation, making the system separable.";
    }
    
    if (step == 8) {
        return
            "The tab displays the complete mathematical derivation of the final solution. First, the state #font[52]{|#Psi_{5}#GT} is rewritten by factorization, grouping terms by ancilla states #font[52]{|0#GT_{A}} and #font[52]{|1#GT_{A}}: #font[52]{|#Psi_{6}#GT}. The success \n"
            "probability is calculated as #font[52]{P(|1#GT) =} #sum_{j} #font[52]{|#beta_{j} C/#lambda_{j}|^{2}}. After measuring #font[52]{|1#GT}, the #font[52]{|0#GT} branch vanishes (collapses to zero) and only the #font[52]{|1#GT_{A}} branch survives, giving the post-selected state\n"
            "#font[52]{|#Psi_{post}#GT =} #sum_{j} #font[52]{#beta_{j}(C/#lambda_{j})|u_{j}#GT_{I}}. The normalized solution state is #font[52]{|x#GT = (1/#sqrt{P(|1#GT)})} #sum_{j} #font[52]{#beta_{j}(C/#lambda_{j})|u_{j}#GT_{I}}, which is proportional to #font[52]{A^{-1}|b#GT}.";
    }

    return "Mathematical development not available for this microstep.";

}

// HELPER: Matrix text descriptions 
TString QHHLA_SoftEdu::GetMatrixText(Int_t step, Int_t microStep) {

    if (step == 1) {
        return
            "The tab shows the classical matrix system #font[52]{#font[62]{A}#vec{x}=#vec{b}} in standard form, followed by the spectral expansion #font[52]{#font[62]{A}=#sum#lambda#scale[0.7]{i}|u_{i}#GT#LTu_{i}|} expressed as a sum of outer products\n" 
            "with explicit numerical matrices. It also displays vector |b#GT as a superposition with explicit column vectors showing the components of each eigenvector scaled\n"
            "by their corresponding coefficients. Also shows the complete matrix decomposition that is equivalent to the quantum state representation.";
    }

    if (step == 2) {
        return 
            "The tab displays the global column vector structure showing the tensor product of three quantum registers: Clock Register as a #font[52]{2^{m}#times 1} column vector with #font[52]{|0#GT} state,\n"
            "Index Register as a #font[52]{2^{1}#times1} column vector containing coefficients #font[52]{#beta_{1}} and #font[52]{#beta_{2}}, Ancilla Register as a #font[52]{2^{1}#times1} column vector with #font[52]{|0#GT} state, and the resulting global \n"
            "state vector of dimension #font[52]{2^{n_{total}}#times1} where #font[52]{n_{total}=m+1+1}. The tab shows how Kronecker product creates exponential dimensionality.";
    }

    if (step == 3) {
        return 
            "The tab shows the standard Hadamard gate matrix for a single qubit, followed by the global operator #font[52]{H^{#otimesm}=H#otimesH#otimes...} applied simultaneously on m qubits. The expanded\n"
            "matrix (#font[52]{2^{m}#times2^{m}}) is displayed with explicit numerical values, where positive entries are shown in blue and negative entries in red, illustrating the Walsh-Hadamard structure\n"
            "that creates uniform superposition across all computational basis states.";
    }

    if (step == 4) {
        return 
            "The tab shows the unitary operator #font[52]{#hat{U}} as a #font[52]{2#times2} diagonal matrix in the eigenbasis, with entries #font[52]{e^{i#lambda_{1}#tau}} (green) and #font[52]{e^{i#lambda_{2}#tau}} (orange). It displays the clock register state vectors #font[52]{|#phi_{1}#GT} and #font[52]{|#phi_{2}#GT}\n"
            "as 2^{m}-dimensional column vectors containing complex phase factors for each time step t from 0 to 2^{m-1}. Each vector element represents the phase accumulated at a specific time, with \n"
            "explicit numerical values showing real and imaginary parts, demonstrating how the eigenvalue information is physically encoded in the complex amplitudes of the quantum state.";
    }

    if (step == 5 && microStep >= 12 && microStep < 14) {
        return 
            "The MATRIX tab visualizes the linear algebra operations behind the Inverse Quantum Fourier Transform (IQFT). It displays the #font[1.3]{2^{m}#times2^{m}} unitary matrix #font[52]{#hat{U}_{IQFT}} with its\n"
            "explicit complex entries, and demonstrates the matrix-vector multiplication #scale[1.3]{#hat{U}_{IQFT}|#phi_{j}#GT} that collapses the phase-encoded state into a single computational basis state\n"
            "corresponding to the eigenvalue. To understand this multiplication, the tab first defines the computational basis states of the Clock Register as standard column \n" 
            "vectors of dimension #scale[1.3]{2^{m}#times1}, where a single '1' indicates the state index and '0's elsewhere.\n"
            "#bullet #color[635]{For #font[62]{m=1} (2 states):} |0#GT = [1, 0]^{T}, |1#GT = [0, 1]^{T}.\n"
            "#bullet #color[635]{For #font[62]{m=2} (4 states):} |00#GT = [1, 0, 0, 0]^{T}, |01#GT = [0, 1, 0, 0]^{T}, |10#GT = [0, 0, 1, 0]^{T}, |11#GT = [0, 0, 0, 1]^{T}.\n"
            "#bullet #color[635]{For #font[62]{m=3} (8 states):} |000#GT = [1, 0, 0, 0, 0, 0, 0, 0]^{T}, |001#GT = [0, 1, 0, 0, 0, 0, 0, 0]^{T}, |010#GT = [0, 0, 1, 0, 0, 0, 0, 0]^{T}, |011#GT = [0, 0, 0, 1, 0, 0, 0, 0]^{T},\n"
            "\\quad \\quad \\quad \\quad \\quad \\quad \\quad \\quad \\quad \\quad |100\\rangle = [0, 0, 0, 0, 1, 0, 0, 0]^{T}, |101\\rangle = [0, 0, 0, 0, 0, 1, 0, 0]^{T}, |110\\rangle = [0, 0, 0, 0, 0, 0, 1, 0]^{T}, |111\\rangle = [0, 0, 0, 0, 0, 0, 0, 1]^{T}.\n"
            "This explicit vector representation makes the quantum state manipulation tangible before applying the IQFT matrix.";
    }
    
    if (step == 6 && microStep >= 5 && microStep < 8) {
        return 
            "The MATRIX tab shows the matrix representation of the controlled rotation operation on the ancilla qubit. It displays: #font[62]{(1)} The initial state of the ancilla as a column vector in the\n"
            "computational basis; #font[62]{(2)} The standard rotation matrix #font[52]{R_{y}(#theta_{j})}  which is a unitary 2#times2 matrix performing rotation by angle #font[52]{#theta_{j}} around the Y-axis of the Bloch sphere; #font[62]{(3)} The matrix\n"
            "multiplication #font[52]{R_{y}(#theta_{j})|0#GT_{A}} showing the explicit calculation. This demonstrates how the rotation transforms the initial #font[52]{|0#GT} state into a superposition with amplitudes determined\n"
            "by the eigenvalue #font[52]{#lambda_{j}}.";
    }
    
    if (step == 7) {
        return 
            "The MATRIX tab displays the three inverse matrices that compose #font[52]{#hat{U}_{IQPE}}. First, the Inverse Hadamard Matrix. Second, the Inverse Unitary Evolution Matrix. Third, the Quantum Fourier \n"
            "Transform Matrix #font[52]{#hat{U}_{QFT}} (the inverse of IQFT). The combined operator #font[52]{#hat{U}_{IQPE} = H^{#otimes m} #upoint #hat{U}^{-1} #upoint QFT} is shown as the product of these three matrices, with the property \n"
            "#font[52]{#hat{U}_{IQPE} #upoint #hat{U}_{QPE} = I}, confirming that applying IQPE after QPE returns the Clock Register to #font[52]{|0#GT^{#otimes m}}.";
    }

    if (step == 8) {
        return 
            "The MATRIX tab displays the column vector representations of both the classical and quantum solutions for direct comparison. The classical solution vector #font[52]{#vec{x}_{classical} = A^{-1}#vec{b}} is shown with its \n"
            "explicit numerical components obtained by solving the linear system directly. The quantum solution vector #font[52]{#vec{x}_{quantum}} is shown with components derived from the post-selected quantum state\n"
            "#font[52]{|x#GT}, where each component is the amplitude of the corresponding basis state. The tab highlights the component-wise verification showing that #font[52]{(#vec{x}_{quantum})_{i} = (#vec{x}_{classical})_{i} #upoint N}, where\n"
            "#font[52]{N = C/(#sqrt{P(|1#GT)} ||b||)} is the normalization constant. This explicit numerical comparison proves that the quantum and classical solutions are identical up to the normalization factor, validating\n"
            "the correctness of the HHL algorithm implementation.";
    }

    return "Matrix representation not available for this microstep.";

}

// HELPER: Circuit text descriptions
TString QHHLA_SoftEdu::GetCircuitText(Int_t step, Int_t microStep) {

    if (step == 1) {
        return
            "The tab shows the Index Register (Memory Register) preparation: the initial state #font[52]{|0#GT} enters a State Preparation block containing the superposition, and\n"
            "outputs the prepared quantum state |b#GT. The Index Register is a quantum register designed to encode the system's data by loading the classical vector #font[52]{#vec{b}}\n"
            "using Amplitude Encoding. Throughout the HHL algorithm, this register will evolve, and its final state will hold the solution #font[52]{|x#GT} of the linear system.";
    }
    
    if (step == 2) {
        return 
            "The tab draws the initial quantum circuit skeleton showing three quantum registers: Index Register (top line) initialized in #font[52]{|b#GT_{I}}, Clock Register (middle lines, m qubits) \n"
            "all initialized in #font[52]{|0#GT_{C}}, and Ancilla Register (bottom line) initialized in #font[52]{|0#GT_{A}}. Each register line is clearly labeled on the left following Qiskit-style convention. This circuit skeleton\n"
            "represents the starting point before any quantum gates are applied in subsequent steps.";
    }

    if (step == 3) {
        return 
            "The tab updates the circuit skeleton by adding Hadamard gate boxes (labeled H) on each line of the Clock Register, while the Index Register line and Ancilla line remain\n"
            "as straight lines without additional gates. This visual update clearly shows that only the Clock Register undergoes transformation in this step, preparing it for the controlled\n"
            "unitary evolution that will follow in Step 4.";
    }

    if (step == 4) {
        return 
            "The circuit updates from Step 3 by adding controlled-U operations. The Index Register line now passes through unitary evolution blocks, each controlled by a different clock qubit\n"
            "(indicated by dots on vertical control lines). This circuit structure implements the controlled unitary evolution, where each clock qubit controls a different power of U (U^{1}, U^{2}, ..., U^{2^{m-1}}),\n"
            "creating the entanglement necessary for phase extraction in the next step.";
    }
    
    if (step == 5 && microStep >= 14 && microStep < 18) {
        return 
            "The circuit updates by adding a large IQFT box at the end of all Clock Register lines, spanning vertically across all m qubits. This IQFT block completes the Quantum Phase \n"
            "Estimation (QPE) subroutine, which is composed of three sequential operations: (1) Step 3 - Hadamard gates on each clock qubit creating superposition, (2) Step 4 - Controlled\n"
            "unitary evolution blocks #font[52]{U^{2^{0}}, U^{2^{1}}, ..., U^{2^{m-1}}} controlled by each clock qubit, and (3) Step 5 - The IQFT block that decodes the phase information. A dashed bracket labeled\n"
            "QPE visually groups these three stages together, showing that they form a single logical subroutine.";
    
    }
    
    if (step == 6 && microStep >= 8 && microStep < 13) {
        return 
            "The CIRCUIT tab shows the complete quantum circuit up to Step 6. After the QPE block, controlled rotation gates #font[52]{R_{y}(#theta)} appear on the ancilla line (red box), with control lines coming\n"
            "from each clock qubit line. These control lines indicate that the rotation angle #theta depends on the eigenvalue encoded in the clock register state. The Index Register line #font[52]{|b#GT_{I}} passes\n"
            "through unchanged, while the Ancilla line #font[52]{|0#GT_{A}} undergoes the controlled rotation, creating entanglement between the eigenvalue information in the clock and the inverse eigenvalue\n"
            "amplitude in the ancilla.";
    }

    if (step == 7) {
        return 
            "The CIRCUIT tab shows the complete quantum circuit with the IQPE block added after the QPE subroutine. The new IQPE block (orange rectangle) is applied to the Clock Register lines,\n"
            "representing the inverse operations: QFT, controlled #font[52]{U^{-1}} blocks, and Hadamard gates in reverse order. This circuit structure demonstrates that IQPE is the exact mirror image of QPE,\n"
            " undoing the phase encoding while preserving the eigenvalue inversion in the Ancilla.";
    }
    
    if (step == 8) {
        return 
            "The CIRCUIT tab shows the complete HHL quantum circuit with the final measurement operation. The full circuit includes: the QPE block (dashed brown rectangle) containing Hadamard\n"
            "gates, controlled unitary evolution blocks, and the IQFT block; the IQPE block (orange rectangle) that uncomputes the clock register; the controlled rotation R_{y}(#theta) on the ancilla line (red box)\n"
            "with control lines from the clock register; and finally the measurement box (yellow with meter symbol) on the ancilla line. The circuit outputs show: the Index Register line ends in |x#GT (the\n"
            "quantum solution), the Clock Register lines return to |0#GT (successfully uncomputed), and the Ancilla line collapses to |1#GT (successful post-selection). This final measurement\n"
            "induces the wave function collapse that extracts the solution from the quantum superposition.";
    }

    return "Circuit description not available for this microstep.";

}

// HELPER: Graph text descriptions
TString QHHLA_SoftEdu::GetGraphText(Int_t step, Int_t microStep) {

    if (step == 1) {
        return
            "The tab provides an interactive #font[52]{2D} Cartesian plane visualization showing geometric intuition. It plots: vector #font[52]{#hat{u}_{1}} (green arrow) as the first eigenvector,\n"
            "vector #font[52]{#hat{u}_{2}} (brown arrow) as the second eigenvector, vector #font[52]{#vec{b}} (blue arrow) as the input, and vector #font[52]{#vec{x}_{classical}} (red arrow) as the classical solution. A the\n"
            "stretched lines represents the eigenbasis coordinate system, with dashed lines showing geometric projections following the parallelogram rule: #font[52]{#vec{b}=#beta_{1}#hat{u}_{1}+#beta_{2}#hat{u}_{2}}.\n"
            "A formula box at bottom-left displays #font[52]{#vec{x}=(#beta_{1}/#lambda_{1})#hat{u}_{1}+(#beta_{2}/#lambda_{2})#hat{u}_{2}}, demonstrating how the classical solution is expressed in the eigenbasis through eigenvalue \n"
            "inversion. This geometric perspective is crucial for understanding how the classical vector is encoded into the quantum eigenvector basis.";
    }

    if (step == 2) {
        return 
            "The tab displays a probability distribution histogram showing #font[52]{P=|#beta_{j}|^{2}} for each quantum state component. It visualizes two bars representing the probability amplitudes\n"
            "of states #font[52]{|0...0#GT|u_{1}#GT|0#GT} and #font[52]{|0...0#GT|u_{2}#GT|0#GT} in the initial superposition. A yellow information box displays #font[52]{|#beta_{1}|^{2}} and #font[52]{|#beta_{2}|^{2}} values with their sum equal to 1.00. Below the\n"
            "histogram, the equation #font[52]{|#Psi_{0}#GT=|0#GT_{C}^{#otimesm}#otimes[#beta_{1}|u_{1}#GT+#beta_{2}|u_{2}#GT]_{I}#otimes|0#GT_{A}} shows the complete initial state. This visualization demonstrates how the normalized vector #font[52]{|b#GT} is encoded\n"
            "as a quantum superposition with probabilities determined by the spectral decomposition coefficients.";
    }

    if (step == 3) {
        return 
            "The tab displays a probability distribution histogram showing equiprobable superposition in the Clock Register. All #font[52]{2^{m}} bars have equal height representing uniform\n"
            "probability #font[52]{P=1/2^{m}} for each state #font[52]{|t#GT_{C}} (shown in binary notation on the x-axis for m qubits). This visualization demonstrates that the Hadamard transform creates\n"
            "perfect uniformity across all time states, which is essential for the quantum parallelism that gives HHL its computational advantage.";
    }

    if (step == 4) {
        return 
        "The GRAPH tab provides an interactive phasor clock visualization on the complex plane (unit circle) to make the invisible phase evolution visible and intuitive. It displays: #font[62]{(1)} Unit\n" 
        "circle with Real (Re) and Imaginary (Im) axes showing the trajectory of phase rotation; #font[62]{(2)} Two phasors (rotating arrows): #font[62]{#lambda_{1}} (green arrow) and #font[62]{#lambda_{2}} (orange arrow), each rotating \n" 
        "at angular velocity proportional to its eigenvalue; #font[62]{(3)} Interactive slider for Clock Time t, allowing the user to see how both phasors rotate simultaneously as t increases from 0 to 2^{m-1};\n" 
        "#font[62]{(4)} Phasor equations box showing the explicit calculation with numerical values for the current time step. The visualization demonstrates that larger eigenvalues rotate faster (more phase\n"
        "accumulation per time step), while smaller eigenvalues rotate slower. This differential rotation is the physical manifestation of how QPE distinguishes between different eigenvalues - they \n" 
        "create different interference patterns that will be decoded by the IQFT in Step 5. The note 'Both eigenvalues rotate at the same speed' refers to the fact that they share the same time\n"
        "parameter t, but their angular velocities #font[52]{#omega_{j} = #lambda_{j}#tau} are different, creating the phase differences that encode the eigenvalue information.";
    }

    if (step == 5 && microStep >= 18){
        return 
            "The GRAPH tab provides an interactive visualization of constructive and destructive interference in the complex plane, showing how the IQFT extracts eigenvalue information through\n"
            "phase summation. Two separate unit circles are displayed side-by-side: one for the #font[52]{#lambda_{1}} branch (green) and one for the #font[52]{#lambda_{2}} branch (orange) For each candidate state #font[52]{|y#GT} .\n"
            "being evaluated (controlled by a slider from y=0 to y=2^{m}-1), the IQFT sums the phase factors #scale[1.3]{e^{2#piit(#theta_{j} - y/2^{m})}} geometrically by placing each phasor head-to-tail. \n"
            "CONSTRUCTIVE INTERFERENCE: all phase factors equal 1, so all phasors point in the same direction (along the positive real axis), forming a long straight line with maximum \n"
            "amplitude #font[52]{2^{m}}, giving probability 1 after normalization. DESTRUCTIVE INTERFERENCE: the phase factors rotate at different angles, causing the phasors to trace out a closed polygon\n" 
            "(square for m=2, octagon for m=3, etc.) that returns to the origin, giving probability 0. The animation shows this step-by-step: as y increments, the user sees the phasors either align \n"
            "perfectly (resonance) or cancel completely (non-resonance), demonstrating visually why only the eigenvalue state survives after IQFT. This geometric interpretation makes the abstract  \n"
            "mathematics of quantum interference tangible and intuitive.";
    }

    if (step == 6 && microStep >= 13) {
        return 
            "The GRAPH tab provides a 3D Bloch sphere visualization showing the controlled rotation of the ancilla qubit for each eigenvalue branch. Two separate Bloch spheres are displayed \n"
            "side-by-side: the #font[52]{#lambda_{1}} branch (left, green) and the #font[52]{#lambda_{2}} branch (right, orange). Each sphere shows: #font[62]{(1)} The Bloch sphere wireframe with axes X, Y, Z; #font[62]{(2)} The north pole labeled\n"
            "|0#GT (initial ancilla state); #font[62]{(3)} The south pole labeled |1#GT (target state for eigenvalue inversion); #font[62]{(4)} A red arrow representing the state vector #font[52]{R_{y}(#theta_j)|0#GT_{A}}, rotated from the north\n"
            "pole by angle #font[52]{#theta_{j}} toward the south pole. For smaller eigenvalues, the rotation angle #font[52]{#theta_{2}} is large, so the arrow points nearly to |1#GT, giving high probability of measuring |1#GT.\n"
            "For larger eigenvalues, the rotation angle #font[52]{#theta_{2}} is small, so the arrow stays closer to |0#GT, giving lower probability of measuring |1#GT. This visual demonstrates the inverse relationship:\n"
            "small #lambda #rightarrow large rotation #rightarrow high |1#GT probability, which is the core mechanism of eigenvalue inversion in HHL.";
    }

    if (step == 7) {
        return 
            "The GRAPH tab displays two probability distribution histograms showing the Clock Register before and after IQPE. BEFORE IQPE (Micro-step 14): The histogram shows the QPE peaks at\n"
            "the binary states corresponding to the eigenvalues #font[52]{#lambda_{1}} and #font[52]{#lambda_{2}}, with probabilities #font[52]{P(#lambda_{1})} and #font[52]{P(#lambda_{2})}. The bars are colored red (for #font[52]{#lambda_{2}}) and blue (for #font[52]{#lambda_{1}}), with a yellow info box showing\n"
            "the QPE peak probabilities. AFTER IQPE (Micro-step 15): The histogram shows a single green bar at #font[52]{|00...0#GT} with probability 1.000, while all other states (including the previous QPE\n"
            "peaks) have probability 0.00. The yellow info box confirms: #font[52]{P(|00...0#GT)=1.0000, P(#lambda_{1})=0.00, P(#lambda_{2})=0.00, Clock uncomputed}. This dramatic transition visually demonstrates that IQPE hasc\n"
            "successfully disentangled the Clock Register, returning it to its initial state while preserving the solution information in the Index and Ancilla registers.";
    }

    if (step == 8) {
        return 
            "The GRAPH tab provides two complementary visualizations. First, a probability distribution histogram showing the ancilla measurement outcomes: two bars representing P(|0#GT_{A}) and P(|1#GT_{A}),\n"
            "where the |1#GT bar corresponds to the success probability of the algorithm. A yellow information box displays the exact probabilities with their sum equal to 1.00, and below the histogram the \n"
            "equation shows the state before measurement. Second, a 2D Cartesian plane visualization comparing the classical solution #font[52]{#vec{x}_{classical}} (red arrow) with the quantum solution #font[52]{#vec{x}_{quantum}}.\n"
            "(blue arrow). Both vectors are shown originating from the origin, pointing in the same direction (parallel), with the classical vector being longer due to the normalization factor. A formula \n"
            "box displays the numerical values of both vectors and the relationship #font[52]{#vec{x}_{classical} = N #upoint #vec{x}_{quantum}}, visually confirming that the quantum algorithm successfully produces the classical solution \n"
            "encoded in a normalized quantum state.";
    }

    return "Graph description not available for this microstep.";
}

//* ============================ -HELPER METHODS- =============================
TComplex QHHLA_SoftEdu::ComboBoxToValue(TGComboBox* cb) {

    Int_t id = cb->GetSelected();
    if (id < 0) return TComplex(-999, 0);  // Sentinel value
    
    // IDs 0..4: original mapping to real values ​​-2, -1, 0, 1, 2
    if (id <= 4) {
        return TComplex((Double_t)(id - 2), 0.0);
    }
    // ID 5: imaginary unit i
    else if (id == 5) {
        return TComplex(0.0, 1.0);
    }
    // ID 6: imaginary unit 2i
    else if (id == 6) {
        return TComplex(0.0, 2.0);
    }
    // ID 7: imaginary unit -i
    else if (id == 7) {
        return TComplex(0.0, -1.0);
    }
    // ID 8: imaginary unit -2i
    else if (id == 8) {
        return TComplex(0.0, -2.0);
    }
    return TComplex(0, 0);  // Safe
}

TString QHHLA_SoftEdu::FormatComplex(const TComplex& z) {

    Double_t re = z.Re();
    Double_t im = z.Im();
    const Double_t eps = 1e-6; 
    
    // Función auxiliar local para formatear inteligentemente (sin decimales si es entero)
    auto FormatVal = [](Double_t val) -> TString {
        if (TMath::Abs(val - TMath::Nint(val)) < 1e-5) {
            return TString::Format("%d", (Int_t)TMath::Nint(val));
        }
        return TString::Format("%.2f", val);
    };

    Bool_t hasRe = TMath::Abs(re) > eps;
    Bool_t hasIm = TMath::Abs(im) > eps;
    
    if (!hasRe && !hasIm) return "0";
    
    // Case 1: Strictly Real (Main diagonal of a Hermitian matrix)
    if (hasRe && !hasIm) {
        return FormatVal(re);
    }
    
    // Case 2: Purely Imaginary (Off-diagonal)
    if (!hasRe && hasIm) {
        if (TMath::Abs(im - 1.0) < eps) return "i";
        if (TMath::Abs(im + 1.0) < eps) return "-i";
        
        // Si es un entero puro imaginario (ej. 2i, -2i, 3i...)
        if (TMath::Abs(im - TMath::Nint(im)) < 1e-5) {
            return TString::Format("%d", (Int_t)TMath::Nint(im)) + "i";
        }
        return TString::Format("%.2fi", im);
    }
    
    // Case 3: Mixed Complex (Ej: 1.50 + 2i o 2 - i)
    TString sign = (im > 0) ? "+" : "-";
    Double_t absIm = TMath::Abs(im);
    
    TString strRe = FormatVal(re);
    
    if (TMath::Abs(absIm - 1.0) < eps) {
        return TString::Format("%s %s i", strRe.Data(), sign.Data());
    }
    
    TString strIm = FormatVal(absIm);
    return TString::Format("%s %s %si", strRe.Data(), sign.Data(), strIm.Data());
}

void QHHLA_SoftEdu::DecomposeSign(const TString& formatted, TString& outSign, TString& outValue){
    
    // If the string starts with '-', the term is negative.
    if (formatted.Length() > 0 && formatted[0] == '-') {
        outSign = "-";

        // Substring from index 1 to the end (removes the '-')
        outValue = formatted(1, formatted.Length() - 1);
    } else {
        outSign = "+";
        outValue = formatted;
    }
}

//* ============================ -START BUTTON LOGIC- =========================
void QHHLA_SoftEdu::DoStart(){

    // Capture the selected values ​​in the ComboBoxes
    TComplex A11 = ComboBoxToValue(A11ComboBox);
    TComplex A12 = ComboBoxToValue(A12ComboBox);
    TComplex A21 = ComboBoxToValue(A21ComboBox);
    TComplex A22 = ComboBoxToValue(A22ComboBox);
    TComplex b1  = ComboBoxToValue(b1ComboBox);
    TComplex b2  = ComboBoxToValue(b2ComboBox);

    // Validate that ALL fields have been selected FIRST (Uncommented and moved up)
    TComplex sentinel(-999, 0);
        if ((A11.Re() == sentinel.Re() && A11.Im() == sentinel.Im()) || 
        (A12.Re() == sentinel.Re() && A12.Im() == sentinel.Im()) || 
        (A21.Re() == sentinel.Re() && A21.Im() == sentinel.Im()) ||
        (A22.Re() == sentinel.Re() && A22.Im() == sentinel.Im()) || 
        (b1.Re() == sentinel.Re() && b1.Im() == sentinel.Im()) || 
        (b2.Re() == sentinel.Re() && b2.Im() == sentinel.Im())) {
        new TGMsgBox(gClient->GetRoot(), this,
            "Incomplete Data",
            "Please select a value for ALL fields in Matrix A and Vector b before starting.",
            kMBIconExclamation, kMBOk);
        return;
    }

    // Detect whether the matrix is ​​complex (has an imaginary part in A)
    fIsComplexMatrix = (TMath::Abs(A11.Im()) > 1e-10 || 
                        TMath::Abs(A12.Im()) > 1e-10 || 
                        TMath::Abs(A21.Im()) > 1e-10 || 
                        TMath::Abs(A22.Im()) > 1e-10);
    
    // Hermiticity Validation: A = A†
    // 1) The diagonal must be strictly real.
    if (TMath::Abs(A11.Im()) > 1e-10 || TMath::Abs(A22.Im()) > 1e-10) {
        new TGMsgBox(gClient->GetRoot(), this,
            "Non-Hermitian Matrix",
            "The diagonal entries of a Hermitian matrix must be real numbers.\n"
            "Imaginary units (i, -i) are not allowed on the diagonal (A11, A22).",
            kMBIconExclamation, kMBOk);
        return;
    }
    
    // 2) A12 must be the conjugate of A21.
    TComplex conjA21 = TComplex::Conjugate(A21);
    if (TMath::Abs(A12.Re() - conjA21.Re()) > 1e-10 || 
        TMath::Abs(A12.Im() - conjA21.Im()) > 1e-10) {
        TString msg = TString::Format(
            "The matrix A is not Hermitian.\n"
            "Condition required: A12 = conjugate(A21)\n"
            "Current: A12 = %s,  A21 = %s\n\n"
            "HHL requires Hermitian matrices.",
            FormatComplex(A12).Data(), FormatComplex(A21).Data()
        );
        new TGMsgBox(gClient->GetRoot(), this, "Non-Hermitian Matrix", msg,
            kMBIconExclamation, kMBOk);
        return;
    }
    
    // Verify that the determinant is different from zero (invertible matrix)
    TComplex det = (A11 * A22) - (A12 * A21);
    if (TMath::Abs(det.Re()) < 1e-10 && TMath::Abs(det.Im()) < 1e-10) {
        new TGMsgBox(gClient->GetRoot(), this,
            "Singular Matrix",
            "The determinant of A is zero.\n"
            "The matrix is not invertible.\n"
            "HHL requires A to be invertible.",
            kMBIconExclamation, kMBOk);
        return;
    }
    
    // Validate that vector b is not the zero vector
    if (TMath::Abs(b1.Re()) < 1e-10 && TMath::Abs(b2.Re()) < 1e-10) {
        new TGMsgBox(gClient->GetRoot(), this,
            "Trivial System",
            "The vector b is the zero vector.\n"
            "The trivial solution x = (0, 0) does not require HHL.",
            kMBIconExclamation, kMBOk);
        return;
    }
    
    // ALL OK → Build the algebraic structures of ROOT
    // Release existing structures if they exist (in case START is pressed multiple times)

    // Create a 2x2 matrix
    fMatrixA[0][0] = A11;  fMatrixA[0][1] = A12;
    fMatrixA[1][0] = A21;  fMatrixA[1][1] = A22;
    
    // Create a 2x1 column vector
    fVectorB[0] = b1;
    fVectorB[1] = b2;
    
    // 7. Print to console for verification
        std::cout << "\n=====================================================" << std::endl;
    std::cout << "[START] System Ax = b initialized:" << std::endl;
    std::cout << "Matrix A:" << std::endl; 
    
    for (Int_t i = 0; i < 2; i++) { 
        for (Int_t j = 0; j < 2; j++) {
            std::cout << "(" << fMatrixA[i][j].Re() << "," << fMatrixA[i][j].Im() << ") "; 
        }
        std::cout << std::endl; 
    }

    std::cout << "Vector b:" << std::endl; 
    for (Int_t i = 0; i < 2; i++) {
        std::cout << "(" << fVectorB[i].Re() << "," << fVectorB[i].Im() << ")" << std::endl;
    }

    std::cout << "Determinant: " << det << std::endl;
    std::cout << "=====================================================\n" << std::endl;

    
    // 8. Change interface state
    m_isRunning = kTRUE;
    m_macroStep = 1;
    m_microStep = 1;
    
    // 9. Disable ComboBox and START; enable navigation and RESET
    A11ComboBox->SetEnabled(kFALSE);
    A12ComboBox->SetEnabled(kFALSE);
    A21ComboBox->SetEnabled(kFALSE);
    A22ComboBox->SetEnabled(kFALSE);
    b1ComboBox->SetEnabled(kFALSE);
    b2ComboBox->SetEnabled(kFALSE);
    ButtonSTART->SetState(kButtonDisabled, kTRUE);
    
    ButtonRESET->SetState(kButtonUp, kTRUE);
    EnableNavigationButtons();
    
    std::cout << "[START] Navigation enabled. Current step: " << m_macroStep << std::endl;
    CalculateCoreMath();
    UpdateVisuals();

}

//* ========================== -RESET BUTTON LOGIC- ===========================
void QHHLA_SoftEdu::DoReset(){

    std::cout << "[RESET] Interface restored to initial state." << std::endl;

    // 1. Freeing up memory from algebraic structures
    fIsComplexMatrix = kFALSE; // Reset the complex matrix flag

    // 2. Re-enable all ComboBoxes
    A11ComboBox->SetEnabled(kTRUE);
    A12ComboBox->SetEnabled(kTRUE);
    A21ComboBox->SetEnabled(kTRUE);
    A22ComboBox->SetEnabled(kTRUE);
    b1ComboBox->SetEnabled(kTRUE);
    b2ComboBox->SetEnabled(kTRUE);
    
    // 3. Clear selections (return to initial state "-1" = no selection)
    A11ComboBox->Select(-1);
    A12ComboBox->Select(-1);
    A21ComboBox->Select(-1);
    A22ComboBox->Select(-1);
    b1ComboBox->Select(-1);
    b2ComboBox->Select(-1);

    A11ComboBox->Layout();
    A12ComboBox->Layout();
    A21ComboBox->Layout();
    A22ComboBox->Layout();
    b1ComboBox->Layout();
    b2ComboBox->Layout();
    
    // 4. Reactivate the START button and reset the navigation state
    m_isRunning = kFALSE;
    m_macroStep = 0; 
    m_microStep = 0;
    
    // 5. Restore button state
    ButtonSTART->SetState(kButtonUp, kTRUE);
    ButtonRESET->SetState(kButtonDisabled, kTRUE);
        
    // 6. We delegate all visual work to the Central Director
    UpdateVisuals();

}

//! ======================= -CENTRAL RENDERING DIRECTOR- ======================
void QHHLA_SoftEdu::UpdateVisuals(){
    
    UpdateNavigationButtons();

    // Welcome status
    if (m_macroStep == 0) {
        if (TabAlls) TabAlls->SetTab(0); // HOME Tab
        DoWelcome();
    }

    // Dynamic Tab Control
    if (TabAlls) {
        if (m_macroStep == 1) {
            if (m_microStep == 1) TabAlls->SetTab(1);       // MATH
            else if (m_microStep == 5) TabAlls->SetTab(2);  // MATRIX
            else if (m_microStep == 8) TabAlls->SetTab(3);  // CIRCUIT
            else if (m_microStep == 10) TabAlls->SetTab(4); // GRAPH
        }
        if (m_macroStep == 2) {
            if (m_microStep == 0) TabAlls->SetTab(1);       // MATH
            else if (m_microStep == 5) TabAlls->SetTab(2);  // MATRIX
            else if (m_microStep == 8) TabAlls->SetTab(3);  // CIRCUIT
            else if (m_microStep == 9) TabAlls->SetTab(4);  // GRAPH
        }
        if (m_macroStep == 3) {
            if (m_microStep == 0) TabAlls->SetTab(1);       // MATH
            else if (m_microStep == 4) TabAlls->SetTab(2);  // MATRIX
            else if (m_microStep == 7) TabAlls->SetTab(3);  // CIRCUIT
            else if (m_microStep == 9) TabAlls->SetTab(4);  // GRAPH
        }
        if (m_macroStep == 4) {
            if (m_microStep == 0) TabAlls->SetTab(1);       // MATH
            else if (m_microStep == 7) TabAlls->SetTab(2);  // MATRIX
            else if (m_microStep == 9) TabAlls->SetTab(3);  // CIRCUIT
            else if (m_microStep == 12) TabAlls->SetTab(4); // GRAPH
        }
        if (m_macroStep == 5) {
            if (m_microStep == 0) TabAlls->SetTab(1);        // MATH
            else if (m_microStep == 12) TabAlls->SetTab(2);  // MATRIX
            else if (m_microStep == 14) TabAlls->SetTab(3);  // CIRCUIT
            else if (m_microStep == 18) TabAlls->SetTab(4);  // GRAPH
        }
        if (m_macroStep == 6) {
            if (m_microStep == 0) TabAlls->SetTab(1);        // MATH
            else if (m_microStep == 5) TabAlls->SetTab(2);   // MATRIX
            else if (m_microStep == 8) TabAlls->SetTab(3);   // CIRCUIT
            else if (m_microStep == 13) TabAlls->SetTab(4);  // GRAPH
        }
        if (m_macroStep == 7) {
            if (m_microStep == 0) TabAlls->SetTab(1);        // MATH
            else if (m_microStep == 4) TabAlls->SetTab(2);   // MATRIX
            else if (m_microStep == 8) TabAlls->SetTab(3);   // CIRCUIT
            else if (m_microStep == 14) TabAlls->SetTab(4);  // GRAPH
        }
        if (m_macroStep == 8) {
            if (m_microStep == 0) TabAlls->SetTab(1);        // MATH
            else if (m_microStep == 5) TabAlls->SetTab(2);   // MATRIX
            else if (m_microStep == 8) TabAlls->SetTab(3);   // CIRCUIT
            else if (m_microStep == 15) TabAlls->SetTab(4);  // GRAPH
        }
    }

    DrawMathTab();
    DrawMatrixTab();
    DrawCircuitTab();
    DrawGraphTab();

    std::cout << "[Navigation] Macro Step: " << m_macroStep << " | Micro Step: " << m_microStep << std::endl;

}

void QHHLA_SoftEdu::DrawMathTab(){

    if (!ECanvasMATH || !ECanvasMATH->GetCanvas() || m_macroStep == 0) return;
    TCanvas *c = ECanvasMATH->GetCanvas();
    c->cd();
    c->Clear();

    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right

    switch (m_macroStep) {

        case 1: DrawMath_Step1(m_microStep); break;
        case 2: DrawMath_Step2(m_microStep); break;
        case 3: DrawMath_Step3(m_microStep); break;
        case 4: DrawMath_Step4(m_microStep); break;
        case 5: DrawMath_Step5(m_microStep); break;
        case 6: DrawMath_Step6(m_microStep); break;
        case 7: DrawMath_Step7(m_microStep); break;
        case 8: DrawMath_Step8(m_microStep); break;

    }

    c->Modified(); 
    c->Update();
}

void QHHLA_SoftEdu::DrawMatrixTab(){

    if (!ECanvasMATRIX || !ECanvasMATRIX->GetCanvas() || m_macroStep == 0) return;
    TCanvas *c = ECanvasMATRIX->GetCanvas();
    c->cd();
    c->Clear();

    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right

    switch (m_macroStep) {

        case 1: DrawMatrix_Step1(m_microStep); break;
        case 2: DrawMatrix_Step2(m_microStep); break;
        case 3: DrawMatrix_Step3(m_microStep); break;
        case 4: DrawMatrix_Step4(m_microStep); break;
        case 5: DrawMatrix_Step5(m_microStep); break;
        case 6: DrawMatrix_Step6(m_microStep); break;
        case 7: DrawMatrix_Step7(m_microStep); break;
        case 8: DrawMatrix_Step8(m_microStep); break;

    }

    c->Modified(); 
    c->Update();

}

void QHHLA_SoftEdu::DrawCircuitTab(){

    if (!ECanvasCIRCUIT || !ECanvasCIRCUIT->GetCanvas() || m_macroStep == 0) return;
    TCanvas *c = ECanvasCIRCUIT->GetCanvas();
    c->cd(); 
    c->Clear();

    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right

    switch (m_macroStep) {

        case 1: DrawCircuit_Step1(m_microStep); break;
        case 2: DrawCircuit_Step2(m_microStep); break;
        case 3: DrawCircuit_Step3(m_microStep); break;
        case 4: DrawCircuit_Step4(m_microStep); break;
        case 5: DrawCircuit_Step5(m_microStep); break;
        case 6: DrawCircuit_Step6(m_microStep); break;
        case 7: DrawCircuit_Step7(m_microStep); break;
        case 8: DrawCircuit_Step8(m_microStep); break;
    }

    c->Modified();
    c->Update();

}

void QHHLA_SoftEdu::DrawGraphTab(){

    if (!ECanvasGRAPH || !ECanvasGRAPH->GetCanvas() || m_macroStep == 0) return;
    TCanvas *c = ECanvasGRAPH->GetCanvas();
    c->cd();
    c->Clear();

    switch (m_macroStep) {

        case 1: DrawGraph_Step1(m_microStep); break;
        case 2: DrawGraph_Step2(m_microStep); break;
        case 3: DrawGraph_Step3(m_microStep); break;
        case 4: DrawGraph_Step4(m_microStep); break;
        case 5: DrawGraph_Step5(m_microStep); break;
        case 6: DrawGraph_Step6(m_microStep); break;
        case 7: DrawGraph_Step7(m_microStep); break;
        case 8: DrawGraph_Step8(m_microStep); break;

    }

    c->Modified();
    c->Update();

}

//! ===========================================================================
//* ================== -GLOBAL VISUAL ELEMENTS AND COREMATH- ==================
//* -------------------------------------------------------------------
// GetStepName: Returns the name of each HHL step
//* -------------------------------------------------------------------
TString QHHLA_SoftEdu::GetStepName(Int_t step){

    switch(step) {

        case 1:  return "Quantum Problem Preparation";
        case 2:  return "Quantum System Initialization";
        case 3:  return "Time Superposition";
        case 4:  return "Controlled Unitary Evolution";
        case 5:  return "Inverse Quantum Fourier Transform";
        case 6:  return "Controlled Rotation & Eigenvalue Inversion";
        case 7:  return "Uncomputing (IQPE)";
        case 8:  return "Measurement & Post-selection";
        default: return "Unknown Step";

    }

}

//* ---------------------------------------------------------------------------
// DrawStepTitle: Draws a styled title box at the top of the canvas
//   - Blue light background with shadow
//   - Shows "Step N: Name" centered
//   - Uses NDC coordinates (portable across canvas sizes)
//* ---------------------------------------------------------------------------
void QHHLA_SoftEdu::DrawStepTitle(TCanvas* canvas){

    if (!canvas || m_macroStep < 1 || m_macroStep > 8) return;
    
    canvas->cd();
    
    // --- Title Box (TPaveText) ---
    // Coordinates: (x1, y1, x2, y2) in NDC [0,1]
    // Positioned at the top of the canvas
    TPaveText* titleBox = new TPaveText(0.02, 0.90, 0.98, 0.98, "NDC");
    titleBox->SetFillColor(kBlue-9);        // Light blue background
    titleBox->SetFillStyle(1001);           // Solid fill
    titleBox->SetLineColor(kBlue-3);        // Darker blue border
    titleBox->SetLineWidth(2);
    titleBox->SetShadowColor(kGray+1);      // Shadow effect
    titleBox->SetBorderSize(2);
    titleBox->SetMargin(0.02);
    titleBox->SetTextAlign(12);             // Centered horizontally and vertically
    titleBox->SetTextFont(42);              // Bold font
    
    // Build the title string
    TString titleText = TString::Format(
        "#scale[0.8]{#font[62]{Step %d:}} #scale[0.7]{%s}",
        m_macroStep,
        GetStepName(m_macroStep).Data()
    );
    titleBox->AddText(titleText.Data());
    titleBox->Draw();

}

//* ---------------------------------------------------------------------------
// DrawProgressBar: Draws a progress indicator at the bottom-right
//   - Shows overall progress within the current macro-step
//   - Visual bar + text label "Micro-step X / Y"
//   - Resets when moving to the next macro-step
//* ---------------------------------------------------------------------------
void QHHLA_SoftEdu::DrawProgressBar(TCanvas* canvas){

    if (!canvas || m_macroStep < 1 || m_macroStep > 8) return;
    
    canvas->cd();
    
    Int_t maxMicro = m_maxMicroSteps[m_macroStep];
    if (maxMicro <= 0) return;
    
    // --- Progress Calculation ---
    // microStep goes from 0 to maxMicro
    // Progress ratio: current / max
    Double_t progress = (Double_t)m_microStep / (Double_t)maxMicro;
    if (progress > 1.0) progress = 1.0;
    
    // --- Background Box (empty bar) ---
    // Located at bottom-right corner
    TBox* bgBox = new TBox(0.65, 0.02, 0.98, 0.06);
    bgBox->SetFillColor(kGray+1);          // Light gray background
    bgBox->SetFillStyle(1001);
    bgBox->SetLineColor(kGray+0);          // Darker gray border
    bgBox->SetLineWidth(1);
    bgBox->Draw();
    
    // --- Filled Bar (progress indicator) ---
    // Width proportional to progress
    Double_t barWidth = 0.33 * progress;   // 0.33 is the max width of the bar
    if (barWidth > 0.001) {                // Only draw if there's visible progress
        TBox* fillBox = new TBox(0.65, 0.02, 0.65 + barWidth, 0.06);
        fillBox->SetFillColor(kGreen+1);   // Green fill for progress
        fillBox->SetFillStyle(1001);
        fillBox->SetLineColor(kGreen+2);
        fillBox->SetLineWidth(1);
        fillBox->Draw();
    }
    
    // --- Progress Text Label ---
    // Shows "Micro-step X / Y" centered over the bar
    TLatex* progressLabel = new TLatex(0.815, 0.04, 
        TString::Format("#font[62]{Micro-step %d / %d}", 
                        m_microStep, maxMicro));
    progressLabel->SetTextAlign(22);       // Centered
    progressLabel->SetTextSize(0.018);
    progressLabel->SetTextFont(42);
    progressLabel->SetTextColor(kWhite);   // White text for contrast
    progressLabel->Draw();
    
}

//* ---------------------------------------------------------------------------
//! CalculateCoreMath:
//! 1. Spectral decomposition of matrix A & b expansion.
//! 2. QPE parameters: time scale τ, clock qubits m, θⱼ.
//! 3. Compute final solutions & print parameters.
//* ---------------------------------------------------------------------------
void QHHLA_SoftEdu::CalculateCoreMath(){

    // Obtain values from the complex matrix and vector
    TComplex a = fMatrixA[0][0], b = fMatrixA[0][1];
    TComplex c = fMatrixA[1][0], d = fMatrixA[1][1];
    TComplex b0 = fVectorB[0], b1 = fVectorB[1];
    Double_t b2 = b0.Rho2() + b1.Rho2();  // |b0|² + |b1|²

    //For a 2x2 matrix, the characteristic polynomial is λ²-tr(A)λ+det(A)=0
    TComplex trace = a + d;
    TComplex det = a*d - b*c;

    // For a Hermitian matrix, the trace and determinant are real.
    Double_t traceRe = trace.Re();
    Double_t detRe = det.Re();

    // Where λⱼ=tr(A)±√tr²(A)-4*det(A)/2=tr(A)±√discriminant/2
    Double_t discriminant = traceRe*traceRe - 4.0*detRe;
    if (discriminant < 0) discriminant = 0;  // For real hermitian matrix, always ≥ 0
    
    //? Eigenvalues
    fLambda1 = (traceRe - TMath::Sqrt(discriminant)) / 2.0;
    fLambda2 = (traceRe + TMath::Sqrt(discriminant)) / 2.0;
    
    // Eigenvectors (intentionally NON-normalized for pedagogical display)

    // For λ₁: (A - λ₁I)v = 0
    if (b.Rho2() > 1e-10) {

        fEigenvectors[0][0] = TComplex(1.0, 0.0);
        
        TComplex lambda1Cpx(fLambda1, 0.0); 
        fEigenvectors[1][0] = (lambda1Cpx - a) / b;

    } else {

        if (a.Re() <= d.Re()) {

            fEigenvectors[0][0] = TComplex(1.0, 0.0);
            fEigenvectors[1][0] = TComplex(0.0, 0.0);

        } else {
            
            fEigenvectors[0][0] = TComplex(0.0, 0.0);
            fEigenvectors[1][0] = TComplex(1.0, 0.0);

        }
        
    }

    // Squared of the UNNORMALIZED eigenvectors
    fNormUSq = fEigenvectors[0][0].Rho2() + fEigenvectors[1][0].Rho2();

    // For λ₂: ortogonal hermítico a u₁
    // If u₁ = (x, y), then u₂ = (-conj(y), conj(x))
    fEigenvectors[0][1] = - (TComplex::Conjugate(fEigenvectors[1][0]));
    fEigenvectors[1][1] =   (TComplex::Conjugate(fEigenvectors[0][0]));

    fNormU = TMath::Sqrt(fNormUSq);          // Norm eigenvector uj ||uj||
    fNormB = TMath::Sqrt((Double_t)b2);      // Norm vector b ||b||

    // Hermitian inner product: ⟨uⱼ|b⟩ = conj(u_jx)*b_x + conj(u_jy)*b_y
    fbetaNum1 = (TComplex::Conjugate(fEigenvectors[0][0]))*b0 + (TComplex::Conjugate(fEigenvectors[1][0]))*b1;
    fbetaNum2 = (TComplex::Conjugate(fEigenvectors[0][1]))*b0 + (TComplex::Conjugate(fEigenvectors[1][1]))*b1;
    fIntDenomSq = fNormUSq * b2; // Always real and positive
    
    // Coefficients βⱼ = ⟨uⱼ|b⟩ for the BACKEND SIMULATOR
    fBeta1 = fbetaNum1 / TMath::Sqrt(fIntDenomSq);
    fBeta2 = fbetaNum2 / TMath::Sqrt(fIntDenomSq);
    
    // Eigenvectors uⱼ = (u_jx , u_jy ) for the BACKEND SIMULATOR
    TComplex u1_x = fEigenvectors[0][0]/fNormU; 
    TComplex u1_y = fEigenvectors[1][0]/fNormU;
    TComplex u2_x = fEigenvectors[0][1]/fNormU; 
    TComplex u2_y = fEigenvectors[1][1]/fNormU;


    // ====================================================================
    //? SCALING CALCULATION AND QPE
    // ====================================================================

    // We find the magnitude (absolute value) of the largest eigenvalue.
    Double_t maxAbsLambda = TMath::Max(TMath::Abs(fLambda1), TMath::Abs(fLambda2));

    // We calculate how many bits are needed ONLY for the magnitude (2^k > maxAbsLambda).
    Int_t magnitudeBits = 0;
    while (TMath::Power(2, magnitudeBits) <= maxAbsLambda) {
        magnitudeBits++;
    }

    // We assign the magnitude bits to the clock register.
    fClockQubitsM = magnitudeBits;

    // SIGN EVALUATION (Two's Complement): 
    // If there are negative eigenvalues, quantum computing requires an extra bit for the sign.
    if (fLambda1 < 0 || fLambda2 < 0) {
        fClockQubitsM++; 
    }

    // Limit the number of clock qubits to a maximum of 3 for visualization purposes.
    if (fClockQubitsM > 3) {
        fClockQubitsM = 3;
    }

    // We calculate the Scale Factor (1 / 2^m) and Tau (2π / 2^m)
    fScaleFactor = 1.0 / TMath::Power(2, fClockQubitsM);
    fTimeScale = TMath::TwoPi() * fScaleFactor;        
    fDemTau = TMath::Power(2, fClockQubitsM - 1); //for visuals 


    // Scale the eigenvalues ​​to fit within the unit circle [-0.5, 0.5).
    fScaledLambda1 = fLambda1 * fScaleFactor;
    fScaledLambda2 = fLambda2 * fScaleFactor;

    // Convert to a binary fraction
    Int_t dummyBits1 = 0, dummyBits2 = 0;
    fBinLambda1 = DecimalToBinaryFraction(fScaledLambda1, fClockQubitsM, dummyBits1);
    fBinLambda2 = DecimalToBinaryFraction(fScaledLambda2, fClockQubitsM, dummyBits2);
    
    // Calculate the total number of states of the clock register (2^m).
    ftotalStates = TMath::Power(2, fClockQubitsM);

    //? Evaluating the operator U^t = e^{iλ_jτ} for each eigenvalue.
    fPhaseStrings.clear(); 

     // Eigenvalues like a vector
        TVectorD eigenvalues(2);
        eigenvalues(0) = fLambda1;
        eigenvalues(1) = fLambda2;

    // Populating our text matrix.
    for (Int_t j = 0; j < 2; j++) { 
        Double_t lambda = eigenvalues(j); 
        std::vector<TString> phasesForThisLambda;

        for (Int_t t = 0; t < ftotalStates; t++) {
            // Circuit physics: e^{i * lambda_j * tau * t}
            Double_t theta = lambda * fTimeScale * (Double_t)t;
            
            phasesForThisLambda.push_back(AngleToAlgebraicString(theta));
        }
        // Storing the branch of eigenvalue 'j'
        fPhaseStrings.push_back(phasesForThisLambda);
    }

    //? DETERMINATION OF ESTIMATED EIGENVALUES (QPE)
    Int_t lim_t = ftotalStates - 1;

    // For λ₁
    fLambdaQPE1 = 0.0;
    Double_t minPhase1 = 999.0; 

    fmappedLambda1 = fLambda1;

    //We apply the geometric "wrap-around" (two's complement) if it is negative.
    if (fmappedLambda1 < 0) {
        fmappedLambda1 = fmappedLambda1 + ftotalStates; 
    }
    
    for (Int_t y = 0; y <= lim_t; y++) {

        Double_t phase = fmappedLambda1 - y;
        
        // If the phase is exactly 0 (perfect resonance, in IQFT)
        if (phase == 0.0) {
            fLambdaQPE1 = y;
            break;
        }
        // Protection for cases where the eigenvalue is not an integer: finds the nearest 'y'.
        if (TMath::Abs(phase) < minPhase1) {
            minPhase1 = TMath::Abs(phase);
            fLambdaQPE1 = y;
        }
    }

    // For λ₂
    fLambdaQPE2 = 0.0;
    Double_t minPhase2 = 999.0;

    fmappedLambda2 = fLambda2;

    //We apply the geometric "wrap-around" (two's complement) if it is negative.
    if (fmappedLambda2 < 0) {
        fmappedLambda2 = fmappedLambda2 + ftotalStates; 
    }
    
    for (Int_t y = 0; y <= lim_t; y++) {

        Double_t phase = fmappedLambda2 - y;
        
        if (phase == 0.0) {
            fLambdaQPE2 = y;
            break;
        }

        if (TMath::Abs(phase) < minPhase2) {
            minPhase2 = TMath::Abs(phase);
            fLambdaQPE2 = y;
        }
    }

    // ====================================================================
    //? CONTROLLED ROTATION
    // ====================================================================
    
    // C ≤ min(|λ₁|, |λ₂|) to ensure that C/λj ≤ 1
    Double_t minLambda = TMath::Min(TMath::Abs(fLambda1), TMath::Abs(fLambda2));
    fC = minLambda; 
    
    // Calculate angles θj = 2·arcsin(C/λj)
    fThetaAngles.ResizeTo(2);
    fThetaAngles(0) = 2.0 * TMath::ASin(fC / TMath::Abs(fLambda1));
    fThetaAngles(1) = 2.0 * TMath::ASin(fC / TMath::Abs(fLambda2));
    
    // ====================================================================
    //? System solution (Classical vs. quantum)
    // ====================================================================

    TComplex beta1_classical = fbetaNum1 / fNormU;  // = û₁ · b
    TComplex beta2_classical = fbetaNum2 / fNormU;  // = û₂ · b

    //Classical solution b non normalized
    fVectorCX[0] = (beta1_classical / fLambda1) * u1_x + (beta2_classical / fLambda2) * u2_x;
    fVectorCX[1] = (beta1_classical / fLambda1) * u1_y + (beta2_classical / fLambda2) * u2_y;

    //Classical solution normalized
    fVectorCX[2] = (fBeta1 / fLambda1) * u1_x + (fBeta2 / fLambda2) * u2_x;
    fVectorCX[3] = (fBeta1 / fLambda1) * u1_y + (fBeta2 / fLambda2) * u2_y;

    //Quantum solution
        TComplex amp1 = (fBeta1 * fC) / fLambda1;
        TComplex amp2 = (fBeta2 * fC) / fLambda2;

        Double_t Coff1 = amp1.Rho2();  // |amp1|²
        Double_t Coff2 = amp2.Rho2();  // |amp2|²

        fProb1 = Coff1 + Coff2; // Success Probability Ancilla |1⟩

        fNGlobal = 1 / (fNormB * TMath::Sqrt(fProb1));

    fVectorQX[0] = fVectorCX[0] * fNGlobal;
    fVectorQX[1] = fVectorCX[1] * fNGlobal;

    // ====================================================================
    //? TERMINAL OUTPUT - HHL DATA
    // ====================================================================
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "[HHL Data] ------ Core Mathematical Parameters ------" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    // Eigenvalues
    std::cout << "\n[Eigenvalues]:" << std::endl;
    std::cout << "  λ₁ = " << fLambda1 << std::endl;
    std::cout << "  λ₂ = " << fLambda2 << std::endl;
    
    // Eigenvectors
    std::cout << "\n[Eigenvectors] (non-normalized):" << std::endl;
    std::cout << "  |u₁⟩ = [" << fEigenvectors[0][0] << ", " << fEigenvectors[1][0] << "]" << std::endl;
    std::cout << "  |u₂⟩ = [" << fEigenvectors[0][1] << ", " << fEigenvectors[1][1] << "]" << std::endl;
    std::cout << "  Norm²(|uⱼ|) = " << fNormU << std::endl;
    
    // Beta coefficients
    std::cout << "\n[Beta Coefficients] (βⱼ = ⟨uⱼ|b⟩):" << std::endl;
    std::cout << "  β₁ = " << fBeta1 << std::endl;
    std::cout << "  β₂ = " << fBeta2 << std::endl;
    std::cout << "  Denominator √(||u||²||b||²) = √" << fIntDenomSq << std::endl;
    
    // Time scaling
    std::cout << "\n[Time Scaling]:" << std::endl;
    std::cout << "  Max eigenvalue |λ|_max = " << TMath::Max(TMath::Abs(fLambda1), TMath::Abs(fLambda2)) << std::endl;
    std::cout << "  Scale factor S = 1/2^" << fClockQubitsM << " = " << fScaleFactor << std::endl;
    std::cout << "  Time scale τ = 2π × S = " << fTimeScale << std::endl;
    std::cout << "  Scaled eigenvalues:" << std::endl;
    std::cout << "    λ₁' = λ₁ × S = " << fScaledLambda1 << std::endl;
    std::cout << "    λ₂' = λ₂ × S = " << fScaledLambda2 << std::endl;
    
    // Clock register qubits
    std::cout << "\n[Clock Register]:" << std::endl;
    std::cout << "  Number of qubits (m) = " << fClockQubitsM << std::endl;
    std::cout << "  Clock states: 2^" << fClockQubitsM << " = " << TMath::Power(2, fClockQubitsM) << std::endl;
    
    // Binary representation
    std::cout << "\n[Binary Representation of Eigenvalues]:" << std::endl;
    std::cout << "  λ₁' (binary) = " << fBinLambda1.Data() << std::endl;
    std::cout << "  λ₂' (binary) = " << fBinLambda2.Data() << std::endl;

    std::cout << "\n[Controlled rotation parameters]:" << std::endl;
    std::cout << "Constant C = " << fC << " (min|λ| = " << minLambda << ")" << std::endl;
    std::cout << "Rotation angles: θ₁ = " << fThetaAngles[0] << ", θ₂ = " << fThetaAngles[1] << std::endl;
    
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "\n[Classical vector solution]:" << std::endl;
    std::cout << "Xc = [ " << fVectorCX[0] << " , " << fVectorCX[1] << " ]" << std::endl;
    std::cout << "\n[Quantum solution]:" << std::endl;
    std::cout << "Xq = [ " << fVectorQX[0] << " , " << fVectorQX[1] << " ]" << std::endl;
    std::cout << "\n=====================================================" << std::endl;

}

//* ====================== MATHEMATICS: DECIMAL TO BINARY =====================
TString QHHLA_SoftEdu::DecimalToBinaryFraction(Double_t decimalValue, Int_t maxBits, Int_t &bitsNeeded) {
    
    TString binStr = "";  // Initialize the text string

    // In QPE, the clock register ALWAYS uses all its m qubits (maxBits).
    // By locking it, we ensure that the drawn hardware retains its actual size.
    bitsNeeded = maxBits;

    Double_t epsilon = 1e-9; // Tolerance for C++ precision errors

    // Quantum Wrap-around (Mapping to Two's Complement)
    // We extract the strictly positive fractional part.
    // If the phase is negative, this is equivalent to flipping the unit circle from the other side.
    Double_t frac = decimalValue - TMath::Floor(decimalValue);

        
    /*  If it is ≥1: It concatenates (adds) the text "1" to our binary answer. 
        Then, it subtracts 1.0 from the fraction to keep only the remaining 
        decimals for the next iteration.

        If it is <1: Simply concatenate a "0" to the answer and the fraction 
        remains intact for the next round. 
    */
    for (Int_t i = 0; i < maxBits; ++i) {
    frac *= 2.0; 
    
        if (frac >= 1.0 - epsilon) {

            binStr += "1";
            frac -= 1.0;

        } 
        
        else {
            binStr += "0";

        }

    }

    return binStr;

}

//* ================== MATHEMATICS: ANGLE TO ALGEBRAIC CHAIN ==================
TString QHHLA_SoftEdu::AngleToAlgebraicString(Double_t angle_rad){

    // 1. Normalize the angle so that it is between 0 and 2π.
    while (angle_rad < 0) angle_rad += TMath::TwoPi();
    while (angle_rad >= TMath::TwoPi()) angle_rad -= TMath::TwoPi();
    
    Double_t c = TMath::Cos(angle_rad);
    Double_t s = TMath::Sin(angle_rad);
    Double_t epsilon = 1e-4; // Tolerance for C++ precision errors
    
    // Calculamos 1/raíz(2) = 0.707106...
    Double_t invSqrt2 = 1.0 / TMath::Sqrt(2.0);
    
    // 2. Evaluate the pure pedagogical cases (roots of unity on axes)
    if (TMath::Abs(c - 1.0) < epsilon && TMath::Abs(s) < epsilon) return ""; // Retorna vacío (o 1, según tu manejador externo)
    if (TMath::Abs(c + 1.0) < epsilon && TMath::Abs(s) < epsilon) return "-";
    if (TMath::Abs(c) < epsilon && TMath::Abs(s - 1.0) < epsilon) return "i";
    if (TMath::Abs(c) < epsilon && TMath::Abs(s + 1.0) < epsilon) return "-i";
    
    // 3. Evaluate pi/4 cases (Diagonals) 
    // Cuadrante I (pi/4) -> + +
    if (TMath::Abs(c - invSqrt2) < epsilon && TMath::Abs(s - invSqrt2) < epsilon) {
        return "#left(1/#sqrt{2} + i/#sqrt{2}#right)";
    }
    // Cuadrante II (3pi/4) -> - +
    if (TMath::Abs(c + invSqrt2) < epsilon && TMath::Abs(s - invSqrt2) < epsilon) {
        return "#left(-1/#sqrt{2} + i/#sqrt{2}#right)";
    }
    // Cuadrante III (5pi/4) -> - -
    if (TMath::Abs(c + invSqrt2) < epsilon && TMath::Abs(s + invSqrt2) < epsilon) {
        return "#left(-1/#sqrt{2} - i/#sqrt{2}#right)";
    }
    // Cuadrante IV (7pi/4) -> + -
    if (TMath::Abs(c - invSqrt2) < epsilon && TMath::Abs(s + invSqrt2) < epsilon) {
        return "#left(1/#sqrt{2} - i/#sqrt{2}#right)";
    }
    
    // 4. Fallback in case a eigenvalue produces an intermediate angle
    return TString::Format("e^{i%.2f}", angle_rad);

}

//! ===========================================================================

//* MODULAR METHODS: STEP 1 (Quantum Problem Preparation) ---------------------
void QHHLA_SoftEdu::DrawMath_Step1(Int_t microStep){

    Int_t b0 = fVectorB[0].Re(), b1 = fVectorB[1].Re(), b2 = b0*b0 + b1*b1;

    //? Rendering step 1.1: Vector b Normalization
    if (microStep >= 1) {

        TString S11titleDesc = "#font[62]{#color[600]{1.1. Vector b Normalization:}} Since N=2, the basis is |0#GT, |1#GT.";
        TLatex *lTitleS11 = new TLatex(0.02, 0.85, S11titleDesc.Data());
        lTitleS11->SetNDC();          
        lTitleS11->SetTextFont(42);   
        lTitleS11->SetTextSize(0.040);
        lTitleS11->SetTextColor(kGray+3);
        lTitleS11->Draw();

        const char* signB1 = (b1 < 0) ? "-" : "+"; // Evaluate the sign of b2
        Int_t absB1 = TMath::Abs(b1);

        TString eq11 = TString::Format(
            "|b\\rangle = \\frac{\\sum_{i=0}^{N-1} b_i |i\\rangle}{\\sqrt{\\sum_{i=0}^{N-1} |b_i|^{2}}} "
            " \\longrightarrow " 
            "||b|| = \\sqrt{(%i)^{2} + (%i)^{2}} =\\sqrt{%i} "
            " \\longrightarrow "
            "|b\\rangle = \\frac{%i}{\\sqrt{%i}}|0\\rangle %s \\frac{%i}{\\sqrt{%i}}|1\\rangle", 
            b0, b1, b2, b0, b2, signB1, absB1, b2
        );
        TLatex *lEqS11 = new TLatex(0.04, 0.75, eq11.Data()); 
        lEqS11->SetNDC();
        lEqS11->SetTextFont(152);     
        lEqS11->SetTextSize(0.05);
        lEqS11->SetTextColor(kBlack); 
        lEqS11->Draw();
    }
    
    //? Rendering step 1.2: Eigenvalues matrix A
    if (microStep >= 2) {

        TString S12titleDesc = "#font[62]{#color[600]{1.2. Eigenvalues matrix A:}} Solving the characteristic equation for the 2x2 matrix.";
        TLatex *lTitleS12 = new TLatex(0.02, 0.65, S12titleDesc.Data());
        lTitleS12->SetNDC();          
        lTitleS12->SetTextFont(42);   
        lTitleS12->SetTextSize(0.040);
        lTitleS12->SetTextColor(kGray+3);
        lTitleS12->Draw();

        TString eq12 = TString::Format(
            "det(A-\\lambda_j \\mathbf{I}) = 0"
            "\\longrightarrow " 
            "\\lambda^2-tr(A)\\lambda+det(A)=0"
            " \\longrightarrow "
            "\\lambda_j=\\frac{tr(A)\\pm\\sqrt{tr(A)^{2}-4\\cdot det(A)}}{2}:"
            "\\lambda_1=%.2f, \\quad \\lambda_2=%.2f",
            fLambda1, fLambda2
        );
        TLatex *lEqS12 = new TLatex(0.02, 0.55, eq12.Data()); 
        lEqS12->SetNDC();
        lEqS12->SetTextFont(152);     
        lEqS12->SetTextSize(0.05);
        lEqS12->SetTextColor(kBlack); 
        lEqS12->Draw();
    }
    
    //? Rendering step 1.3: Eigenvectors matrix A
    if (microStep >= 3){

        TString S13titleDesc = "#font[62]{#color[600]{1.3. Eigenvectors matrix A:}} Solving for each eigenvalue.";
        TLatex *lTitleS13 = new TLatex(0.02, 0.45, S13titleDesc.Data());
        lTitleS13->SetNDC();          
        lTitleS13->SetTextFont(42);   
        lTitleS13->SetTextSize(0.040);
        lTitleS13->SetTextColor(kGray+3);
        lTitleS13->Draw();

        TString u1x = FormatComplex(fEigenvectors[0][0]);
        TString u1y = FormatComplex(fEigenvectors[1][0]);
        TString u2x = FormatComplex(fEigenvectors[0][1]);
        TString u2y = FormatComplex(fEigenvectors[1][1]);
        
        TString eq13 = TString::Format(
            "det(A-\\lambda_j\\mathbf{I}) |u_{j}\\rangle = 0 \\quad \\longrightarrow \\quad"
            "|u_{1}\\rangle=\\frac{1}{\\sqrt{%.0f}}(%s, %s) \\quad"
            "|u_{2}\\rangle=\\frac{1}{\\sqrt{%.0f}}(%s, %s)",
            fNormUSq, u1x.Data(), u1y.Data(),
            fNormUSq, u2x.Data(), u2y.Data()
        );
        TLatex *lEqS13 = new TLatex(0.04, 0.35, eq13.Data()); 
        lEqS13->SetNDC();
        lEqS13->SetTextFont(152);     
        lEqS13->SetTextSize(0.05);
        lEqS13->SetTextColor(kBlack); 
        lEqS13->Draw(); 

    }
    
    //? Rendering step 1.4: Expansion of |b⟩ in the basis of A
    if (microStep >= 4) {

        TString S14titleDesc = "#font[62]{#color[600]{1.4. Expansion of |b#GT in the basis of A:}} Where #beta_{j}=#LTu_{j}|b#GT .";
        TLatex *lTitleS14 = new TLatex(0.02, 0.25, S14titleDesc.Data());
        lTitleS14->SetNDC();          
        lTitleS14->SetTextFont(42);   
        lTitleS14->SetTextSize(0.040);
        lTitleS14->SetTextColor(kGray+3);
        lTitleS14->Draw();

        TString b1Str = FormatComplex(fbetaNum1);
        TString b2Str = FormatComplex(fbetaNum2);

        TString sign1, val1, sign2, val2;
        DecomposeSign(b1Str, sign1, val1);
        DecomposeSign(b2Str, sign2, val2);

        TString eq14 = TString::Format(
            "\\beta_j = \\frac{\\langle u_j | b \\rangle}{\\sqrt{||u_j||^2 ||b||^2}} \\quad \\longrightarrow \\quad"
            "\\beta_1 = \\frac{%s}{\\sqrt{%.0f}}, \\quad \\beta_2 = \\frac{%s}{\\sqrt{%.0f}} \\quad \\longrightarrow \\quad"
            "|b\\rangle = \\frac{%s}{\\sqrt{%.0f}} |u_1\\rangle %s \\frac{%s}{\\sqrt{%.0f}} |u_2\\rangle",
            b1Str.Data(), fIntDenomSq,   // beta1 con signo natural
            b2Str.Data(), fIntDenomSq,   // beta2 con signo natural
            val1.Data(), fIntDenomSq,    // primer termino sin signo duplicado
            sign2.Data(), val2.Data(), fIntDenomSq  // conector dinamico + valor limpio
        );
        
        TLatex *lEqS14 = new TLatex(0.04, 0.15, eq14.Data()); 
        lEqS14->SetNDC();
        lEqS14->SetTextFont(152);     
        lEqS14->SetTextSize(0.05);
        lEqS14->SetTextColor(kBlack); 
        lEqS14->Draw(); 
    }

}

void QHHLA_SoftEdu::DrawMatrix_Step1(Int_t microStep){

    TString aStr = FormatComplex(fMatrixA[0][0]);
    TString bStr = FormatComplex(fMatrixA[0][1]);
    TString cStr = FormatComplex(fMatrixA[1][0]);
    TString dStr = FormatComplex(fMatrixA[1][1]);
    TString b0Str = FormatComplex(fVectorB[0]);
    TString b1Str = FormatComplex(fVectorB[1]);

    // Extract data from the CoreMath 
    Double_t l1 = fLambda1; 
    TComplex u11 = fEigenvectors[0][0]/fNormU;
    TComplex u12 = fEigenvectors[1][0]/fNormU;
    TComplex u21 = fEigenvectors[0][1]/fNormU;
    TComplex u22 = fEigenvectors[1][1]/fNormU;

    // Projectors |u><u| using Hermitian product: P_{ij} = u_i * conj(u_j)
    TComplex P1_11 = u11 * TComplex::Conjugate(u11);
    TComplex P1_12 = u11 * TComplex::Conjugate(u12);
    TComplex P1_21 = u12 * TComplex::Conjugate(u11);
    TComplex P1_22 = u12 * TComplex::Conjugate(u12);

    TComplex P2_11 = u21 * TComplex::Conjugate(u21);
    TComplex P2_12 = u21 * TComplex::Conjugate(u22);
    TComplex P2_21 = u22 * TComplex::Conjugate(u21);
    TComplex P2_22 = u22 * TComplex::Conjugate(u22);

    //λ|u><u| Productos
    TComplex A1_11 = fLambda1 * P1_11; TComplex A1_12 = fLambda1 * P1_12;
    TComplex A1_21 = fLambda1 * P1_21; TComplex A1_22 = fLambda1 * P1_22;
    TComplex A2_11 = fLambda2 * P2_11; TComplex A2_12 = fLambda2 * P2_12;
    TComplex A2_21 = fLambda2 * P2_21; TComplex A2_22 = fLambda2 * P2_22; 

    //? Rendering step 1.5: Classical Matrix System
    if (microStep >= 5) {

        TString S15titleDesc = "#font[62]{#color[600]{1.5. Classical Matrix System:}}";
        TLatex *lTitleS15 = new TLatex(0.02, 0.80, S15titleDesc.Data());
        lTitleS15->SetNDC(); 
        lTitleS15->SetTextFont(42); 
        lTitleS15->SetTextSize(0.040);
        lTitleS15->SetTextColor(kGray+3); 
        lTitleS15->Draw();

        TString eq15 = TString::Format(
            "#color[1]{#left[ #splitline{%s    %s}{%s    %s} #right]} "
            "#color[632]{#left[ #splitline{x_{1}}{x_{2}} #right]} "
            "#color[1]{=} "
            "#color[1]{#left[ #splitline{%s}{%s} #right]}",
            aStr.Data(), bStr.Data(), cStr.Data(), dStr.Data(), 
            b0Str.Data(), b1Str.Data()
        ); 
        TLatex *lEqS15 = new TLatex(); 
        lEqS15->SetNDC(kTRUE);       
        lEqS15->SetTextFont(42);     
        lEqS15->SetTextSize(0.06);
        lEqS15->DrawLatex(0.30, 0.80, eq15.Data());

    }

    //? Rendering step 1.6: Spectral Expansion
    if (microStep >= 6) {
        
        TString S16titleDesc = "#font[62]{#color[600]{1.6. Spectral Expansion:}}  A = #sum #lambdai |ui#GT#LTui|";
        TLatex *lTitleS16 = new TLatex(0.02, 0.60, S16titleDesc.Data()); 
        lTitleS16->SetNDC(); 
        lTitleS16->SetTextFont(42); 
        lTitleS16->SetTextSize(0.040);
        lTitleS16->SetTextColor(kGray+3); 
        lTitleS16->Draw();

        const char* signLambda2 = (fLambda2 < 0) ? "-" : "+";  
        Double_t absLambda = TMath::Abs(fLambda2);

        // 1. Convertimos TODAS las variables complejas a TString dinámicos
        TString p1_11Str = FormatComplex(P1_11); TString p1_12Str = FormatComplex(P1_12);
        TString p1_21Str = FormatComplex(P1_21); TString p1_22Str = FormatComplex(P1_22);
        
        TString p2_11Str = FormatComplex(P2_11); TString p2_12Str = FormatComplex(P2_12);
        TString p2_21Str = FormatComplex(P2_21); TString p2_22Str = FormatComplex(P2_22);

        TString a1_11Str = FormatComplex(A1_11); TString a1_12Str = FormatComplex(A1_12);
        TString a1_21Str = FormatComplex(A1_21); TString a1_22Str = FormatComplex(A1_22);
        
        TString a2_11Str = FormatComplex(A2_11); TString a2_12Str = FormatComplex(A2_12);
        TString a2_21Str = FormatComplex(A2_21); TString a2_22Str = FormatComplex(A2_22);

        // 2. Usamos %s en lugar de %.2f para evitar el Segmentation Fault
        TString eq16a = TString::Format(
            "#color[1]{A} = "
            "#color[632]{%.2f}#color[1]{#left[ #splitline{%s    %s}{%s    %s} #right]} " 
            "#color[1]{%s} "
            "#color[632]{%.2f}#color[1]{#left[ #splitline{%s    %s}{%s    %s} #right]} "
            "#color[1]{=} "
            "#color[419]{#left[ #splitline{%s    %s}{%s    %s} #right]} "
            "#color[1]{+} "
            "#color[419]{#left[ #splitline{%s    %s}{%s    %s} #right]} ",
            l1, p1_11Str.Data(), p1_12Str.Data(), p1_21Str.Data(), p1_22Str.Data(),
            signLambda2, absLambda, p2_11Str.Data(), p2_12Str.Data(), p2_21Str.Data(), p2_22Str.Data(),
            a1_11Str.Data(), a1_12Str.Data(), a1_21Str.Data(), a1_22Str.Data(), 
            a2_11Str.Data(), a2_12Str.Data(), a2_21Str.Data(), a2_22Str.Data()
        );
        
        TLatex *lEqS16a = new TLatex(); 
        lEqS16a->SetNDC(kTRUE);       
        lEqS16a->SetTextFont(42);     
        lEqS16a->SetTextSize(0.048);
        lEqS16a->DrawLatex(0.02, 0.50, eq16a.Data());
        
    }

    //? Rendering step 1.7: Vector |b⟩ as superposition
    if (microStep >= 7) {

        TString S17titleDesc = "#font[62]{#color[600]{1.7. Vector |b#GT as superposition:}}";
        TLatex *lTitleS17 = new TLatex(0.02, 0.35, S17titleDesc.Data()); 
        lTitleS17->SetNDC(); 
        lTitleS17->SetTextFont(42); 
        lTitleS17->SetTextSize(0.040);
        lTitleS17->SetTextColor(kGray+3); 
        lTitleS17->Draw();

        TString b1Str = FormatComplex(fbetaNum1);
        TString b2Str = FormatComplex(fbetaNum2);

        TString u11Str = FormatComplex(u11); TString u12Str = FormatComplex(u12);
        TString u21Str = FormatComplex(u21); TString u22Str = FormatComplex(u22);

        TString sign1, val1, sign2, val2;
        DecomposeSign(b1Str, sign1, val1);
        DecomposeSign(b2Str, sign2, val2);

        TString eq17 = TString::Format(
            "|b#GT= #frac{%s}{#sqrt{%.0f}} #color[632]{|u_{1}#GT} " 
            "%s "
            "#frac{%s}{#sqrt{%.0f}} #color[632]{|u_{2}#GT} "
            "= "
            "#frac{%s}{#sqrt{%.0f}} #color[419]{#left[ #splitline{%s}{%s} #right]} "
            "%s "
            "#frac{%s}{#sqrt{%.0f}} #color[419]{#left[ #splitline{%s}{%s} #right]}",
            b1Str.Data(), fIntDenomSq,               
            sign2.Data(), val2.Data(), fIntDenomSq,
            b1Str.Data(), fIntDenomSq, u11Str.Data(), u12Str.Data(),
            sign2.Data(), val2.Data(), fIntDenomSq, u21Str.Data(), u22Str.Data()
        );
        TLatex *lEqS17 = new TLatex(0.04, 0.15, eq17.Data()); 
        lEqS17->SetNDC();
        lEqS17->SetTextFont(42);     
        lEqS17->SetTextSize(0.06);
        lEqS17->SetTextColor(kBlack); 
        lEqS17->DrawLatex(0.02, 0.25, eq17.Data()); 
        
    }

}

void QHHLA_SoftEdu::DrawCircuit_Step1(Int_t microStep){

    //? Rendering step 1.8: Index Register Preparation
    if (microStep >= 8) {

        TString S18titleDesc = "#font[62]{#color[600]{1.8. Index Register Preparation:}}";
        TLatex *lTitleS18 = new TLatex(0.02, 0.80, S18titleDesc.Data()); 
        lTitleS18->SetNDC(); 
        lTitleS18->SetTextFont(42); 
        lTitleS18->SetTextSize(0.040);
        lTitleS18->SetTextColor(kGray+3); 
        lTitleS18->Draw();

        // Qubit Line (Circuit Wire) X1, Y1, X2, Y2
        TLine *qWire = new TLine(0.10, 0.60, 0.90, 0.60);
        qWire->SetLineWidth(2);
        qWire->SetLineColor(kBlack);
        qWire->Draw();

        // Initial state label |0>
        TLatex *lInitState = new TLatex(0.06, 0.59, "#color[632]{|0#GT_{I}}");
        lInitState->SetNDC();
        lInitState->SetTextFont(62);
        lInitState->SetTextSize(0.05);
        lInitState->Draw();

        // State Preparation
        TBox *gateBox = new TBox(0.30, 0.50, 0.70, 0.70);
        gateBox->SetFillColor(kAzure-9); 
        gateBox->SetLineColor(kBlack);
        gateBox->SetLineWidth(2);
        gateBox->Draw();

        TString b1Str = FormatComplex(fbetaNum1);
        TString b2Str = FormatComplex(fbetaNum2);

        TString sign1, val1, sign2, val2;
        DecomposeSign(b1Str, sign1, val1);
        DecomposeSign(b2Str, sign2, val2);

        // In the box
        TString eq18 = TString::Format(
            "\\frac{%s}{\\sqrt{%.0f}} |u_{1}\\rangle %s \\frac{%s}{\\sqrt{%.0f}} |u_{2}\\rangle",
            b1Str.Data(), fIntDenomSq, sign2.Data(), val2.Data(), fIntDenomSq 
        );

            
        TLatex *lEqS18 = new TLatex(0.04, 0.18, eq18.Data()); 
        lEqS18->SetNDC();
        lEqS18->SetTextFont(152);     
        lEqS18->SetTextSize(0.060);
        lEqS18->SetTextColor(kWhite); 
        lEqS18->DrawLatex(0.40, 0.60, eq18.Data()); 

        // Resulting State Label |b>
        TLatex *lOutState = new TLatex(0.91, 0.59, "#color[419]{|b#GT_{I}}");
        lOutState->SetNDC();
        lOutState->SetTextFont(62);
        lOutState->SetTextSize(0.05);
        lOutState->Draw();

    }

    if (microStep >= 9) {
        // INFORMATION BOX BELOW (Didactic Info)
        TPaveText *infoBox = new TPaveText(0.10, 0.15, 0.90, 0.45, "NDC");
        infoBox->SetFillColor(kCyan-5);
        infoBox->SetLineColor(kBlack);
        infoBox->SetBorderSize(1);
        infoBox->SetTextAlign(12);
        infoBox->SetTextSize(0.040);
        infoBox->SetMargin(0.05);

        // Agregamos el texto en inglés como solicitaste
        infoBox->AddText("#font[62]{Index Register (Memory Register)}");
        infoBox->AddText("#font[62]{#color[600]{What is it?}} A quantum register to encode the system's data.");
        infoBox->AddText("#font[62]{#color[600]{Purpose:}} It loads the classical vector #vec{b} using Amplitude Encoding to create the state |b#GT.");
        infoBox->AddText("Throughout the HHL algorithm, this register will evolve, and its final state will hold the ");
        infoBox->AddText("solution |x#GT of the linear system A |x#GT = |b#GT.");

        infoBox->SetTextFont(42);
        infoBox->Draw();

    }

}

void QHHLA_SoftEdu::DrawGraph_Step1(Int_t microStep){

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    c->cd();
    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right

    Double_t b_x = fVectorB[0].Re();
    Double_t b_y = fVectorB[1].Re();

    Double_t u1_x = fEigenvectors[0][0].Re()/fNormU; 
    Double_t u1_y = fEigenvectors[1][0].Re()/fNormU;
    Double_t u2_x = fEigenvectors[0][1].Re()/fNormU; 
    Double_t u2_y = fEigenvectors[1][1].Re()/fNormU;
    
    Double_t b1 = fBeta1.Re(); 
    Double_t b2 = fBeta2.Re();
    Double_t L1 = fLambda1;  
    Double_t L2 = fLambda2;

    // Coordinates of the projections
    Double_t p1_x = b1 * u1_x; Double_t p1_y = b1 * u1_y;
    Double_t p2_x = b2 * u2_x; Double_t p2_y = b2 * u2_y;

    // Theoretical classical solution vector and scaled projections
    Double_t cx_x = fVectorCX[0].Re(), cx_y = fVectorCX[1].Re();

    Double_t sx1 = (b1 / L1) * u1_x; Double_t sy1 = (b1 / L1) * u1_y;
    Double_t sx2 = (b2 / L2) * u2_x; Double_t sy2 = (b2 / L2) * u2_y;

    // ===== LOCKING MECHANISM FOR COMPLEX MATRICES =====
    if (fIsComplexMatrix) {
        TPaveText *msg = new TPaveText(0.1, 0.25, 0.9, 0.75, "NDC");
        msg->SetFillColor(kYellow-9);
        msg->SetBorderSize(2);
        msg->SetShadowColor(kGray+2);
        msg->SetTextAlign(22);
        msg->SetTextFont(42);
        msg->SetTextSize(0.045);
        msg->SetMargin(0.05);
        msg->AddText(" ");
        msg->AddText("#font[62]{#color[600]{#scale[1.3]{Complex Matrix Mode}}}");
        msg->AddText(" ");
        msg->AddText("\\text{The eigenvectors have imaginary components and live in } \\mathbb{C}^{2}.");
        msg->AddText("\\text{They cannot be represented in a real 2D Cartesian plane } \\mathbb{R}^{2}.");
        msg->AddText("Please refer to the MATH and MATRIX tabs for the algebraic representation.");
        msg->AddText(" ");
        msg->Draw();
        c->Modified(); 
        c->Update(); 
        c->cd();
        return;
    }

    // Rendering the equations by substep
    if (microStep >= 11) {

        TPaveText *ptEq11 = new TPaveText(0.01, 0.01, 0.20, 0.12, "NDC");
        ptEq11->SetFillColor(kWhite);
        ptEq11->SetBorderSize(1);
        ptEq11->SetShadowColor(0);
        ptEq11->SetTextAlign(22);
        ptEq11->SetTextSize(0.04);
        ptEq11->SetTextFont(42);
        ptEq11->SetMargin(0.03);
        ptEq11->AddText("#color[4]{#vec{b}} = #color[414]{#beta_{1}#vec{u}_{1} } + #color[807]{#beta_{2}#vec{u}_{2}}");
        ptEq11->Draw();

        if (microStep >= 12) {
            TPaveText *ptEq12 = new TPaveText(0.01, 0.01, 0.20, 0.12, "NDC");
            ptEq12->SetFillColor(kWhite);
            ptEq12->SetBorderSize(1);
            ptEq12->SetShadowColor(0);
            ptEq12->SetTextAlign(22);
            ptEq12->SetTextSize(0.038);
            ptEq12->SetTextFont(42);
            ptEq12->SetMargin(0.03);
            ptEq12->AddText("#color[2]{#vec{x}} = #color[414]{#frac{#beta_{1}}{#lambda_{1}} #vec{u}_{1}} + #color[807]{#frac{#beta_{2}}{#lambda_{2}} #vec{u}_{2}}");
            ptEq12->Draw();
        }

    }
    
    // CREATION OF THE CONTAINER
    TPad *plotPad = (TPad*)c->GetPrimitive("plotPad");
    if (!plotPad) {
        plotPad = new TPad("plotPad", "Región del Gráfico", 0.01, 0.12, 0.99, 0.88);
        plotPad->Draw();
    }
    plotPad->cd();
    plotPad->Clear(); 
    plotPad->SetGrid();

    // Comparing the maximum size of all variables to adjust
    Double_t max_val = std::max({
        std::abs(b_x), std::abs(b_y), 
        std::abs(u1_x), std::abs(u1_y), std::abs(u2_x), std::abs(u2_y), 
        std::abs(p1_x), std::abs(p1_y), std::abs(p2_x), std::abs(p2_y),
        std::abs(cx_x), std::abs(cx_y),
        std::abs(sx1), std::abs(sy1), std::abs(sx2), std::abs(sy2), 1.0
    }); 
    
    TH1F *frame = plotPad->DrawFrame(-max_val, -max_val, max_val, max_val);
    frame->SetStats(0);

    // Central Cartesian axes (X and Y)
    TLine *axisX = new TLine(-max_val, 0, max_val, 0); 
    axisX->SetLineColor(13); 
    axisX->Draw();

    TLine *axisY = new TLine(0, -max_val, 0, max_val); 
    axisY->SetLineColor(13); 
    axisY->Draw();

    //? Rendering step 1.10: Classical 2D geometry
    if (microStep >= 10) {

        TArrow *arr_u1 = new TArrow(0, 0, u1_x, u1_y, 0.01, "|>");
        arr_u1->SetLineColor(kGray+2); 
        arr_u1->SetFillColor(kGray+2); 
        arr_u1->SetLineWidth(2); 
        arr_u1->Draw();

        TArrow *arr_u2 = new TArrow(0, 0, u2_x, u2_y, 0.01, "|>");
        arr_u2->SetLineColor(kGray+2); 
        arr_u2->SetFillColor(kGray+2); 
        arr_u2->SetLineWidth(2); 
        arr_u2->Draw();

        TLatex *texU1 = new TLatex(u1_x * 1.05, u1_y * 1.05, "#vec{u}_{1}"); texU1->SetTextSize(0.04); texU1->Draw();
        TLatex *texU2 = new TLatex(u2_x * 1.05, u2_y * 1.05, "#vec{u}_{2}"); texU2->SetTextSize(0.04); texU2->Draw();

        TArrow *arr_b = new TArrow(0, 0, b_x, b_y, 0.012, "|>");
        arr_b->SetLineColor(kBlue); 
        arr_b->SetFillColor(kBlue); 
        arr_b->SetLineWidth(3);
        arr_b->Draw();

        TLatex *texB = new TLatex(b_x * 1.05, b_y * 1.05, "#vec{b}"); 
        texB->SetTextColor(kBlue); 
        texB->SetTextSize(0.045); 
        texB->Draw();

    }

    //? Rendering step 1.11: Change of Coordinates: projections β1u1 and β2u2
    if (microStep >= 11) {

        TLine *eigenAxis1 = new TLine(-max_val*u1_x, -max_val*u1_y, max_val*u1_x, max_val*u1_y);
        eigenAxis1->SetLineColor(kGreen+2); 
        eigenAxis1->SetLineStyle(1); 
        eigenAxis1->Draw();

        TLine *eigenAxis2 = new TLine(-max_val*u2_x, -max_val*u2_y, max_val*u2_x, max_val*u2_y);
        eigenAxis2->SetLineColor(kOrange+7); 
        eigenAxis2->SetLineStyle(1); 
        eigenAxis2->Draw();

        TLine *para1 = new TLine(p1_x, p1_y, b_x, b_y);
        para1->SetLineColor(kBlue+1); 
        para1->SetLineStyle(2); 
        para1->Draw();

        TLine *para2 = new TLine(p2_x, p2_y, b_x, b_y);
        para2->SetLineColor(kBlue+1); 
        para2->SetLineStyle(2); 
        para2->Draw();

        TArrow *arr_p1 = new TArrow(0, 0, p1_x, p1_y, 0.01, "|>");
        arr_p1->SetLineColor(kGreen+2); 
        arr_p1->SetFillColor(kGreen+2); 
        arr_p1->SetLineWidth(3); 
        arr_p1->Draw();

        TArrow *arr_p2 = new TArrow(0, 0, p2_x, p2_y, 0.01, "|>");
        arr_p2->SetLineColor(kOrange+7); 
        arr_p2->SetFillColor(kOrange+7); 
        arr_p2->SetLineWidth(3); 
        arr_p2->Draw();

    }

    //? Rendering step 1.12: The Solution Hypothesis
    if (microStep >= 12) {

        TLine *paraX1 = new TLine(sx1, sy1, cx_x, cx_y);
        paraX1->SetLineColor(kRed-7); 
        paraX1->SetLineStyle(2); 
        paraX1->Draw();

        TLine *paraX2 = new TLine(sx2, sy2, cx_x, cx_y);
        paraX2->SetLineColor(kRed-7); 
        paraX2->SetLineStyle(2); 
        paraX2->Draw();

        TArrow *arr_sx1 = new TArrow(0, 0, sx1, sy1, 0.01, "|>");
        arr_sx1->SetLineColor(kGreen+3); 
        arr_sx1->SetFillColor(kGreen+3); 
        arr_sx1->SetLineWidth(4); arr_sx1->Draw();

        TArrow *arr_sx2 = new TArrow(0, 0, sx2, sy2, 0.01, "|>");
        arr_sx2->SetLineColor(kOrange+10); 
        arr_sx2->SetFillColor(kOrange+10); 
        arr_sx2->SetLineWidth(4); 
        arr_sx2->Draw();

        TArrow *arr_x = new TArrow(0, 0, cx_x, cx_y, 0.012, "|>");
        arr_x->SetLineColor(kRed); 
        arr_x->SetFillColor(kRed); 
        arr_x->SetLineWidth(4); 
        arr_x->Draw();
        
        TLatex *texX = new TLatex(cx_x * 1.06, cx_y * 1.06, "#vec{x}_{classical}"); 
        texX->SetTextColor(kRed); 
        texX->SetTextSize(0.05); 
        texX->Draw();

    }

    c->Modified();
    c->Update();
    c->cd();
    
}

//* MODULAR METHODS: STEP 2 (Quantum System Initialization) -------------------
void QHHLA_SoftEdu::DrawMath_Step2(Int_t microStep){

    //? Rendering step 2.1: Clock Register Calculation
    if (microStep >= 1) {

        TString S21titleDesc = "#font[62]{#color[600]{2.1. Clock Register Resolution:}} The number of qubits m defines the phase resolution.";
        TLatex *lTitleS21 = new TLatex(0.02, 0.82, S21titleDesc.Data());
        lTitleS21->SetNDC();
        lTitleS21->SetTextFont(42);
        lTitleS21->SetTextSize(0.040);
        lTitleS21->SetTextColor(kGray+3);
        lTitleS21->Draw();
        
        // Show the eigenvalues and the resolution requirement
        TString eq21 = TString::Format(
            "#font[42]{#color[635]{Eigenvalues in binary:   }}"
            "#scale[1.3]{#lambda_{1} = %.2f = #color[419]{%s}},    "  
            "#scale[1.3]{#lambda_{2} = %.2f = #color[419]{%s}}",
            fLambda1, fBinLambda1.Data(), fLambda2, fBinLambda2.Data()
        );
        TLatex *lEqS21 = new TLatex(0.04, 0.75, eq21.Data());
        lEqS21->SetNDC();
        lEqS21->SetTextFont(132);
        lEqS21->SetTextSize(0.040);
        lEqS21->SetTextColor(kBlack);
        lEqS21->Draw();

        TPaveText *pBox21 = new TPaveText(0.63, 0.74, 0.90, 0.80, "NDC");
        pBox21->SetFillColor(kYellow-9);
        pBox21->SetBorderSize(1);
        pBox21->SetTextAlign(22);
        pBox21->SetTextSize(0.045);
        pBox21->SetTextFont(132);
        pBox21->SetTextColor(kBlack); 
        TString tauCalc = TString::Format(
            "m = %i qubits  #color[2]{#rightarrow}  2^{m} = %i values", 
            fClockQubitsM, ftotalStates
        );
        pBox21->AddText(tauCalc.Data());
        pBox21->Draw();

        TString explanation = TString::Format(
            "#font[42]{#color[635]{Phase resolution:   }}"   
        );
        TLatex *lExpS21 = new TLatex(0.04, 0.68, explanation.Data());
        lExpS21->SetNDC();
        lExpS21->SetTextFont(132);
        lExpS21->SetTextSize(0.040);
        lExpS21->SetTextColor(kBlack);
        lExpS21->Draw();

        TString fractionLine = "";

        for (Int_t i = 0; i < ftotalStates; i++) {
            // Dynamic generation of the binary
            TString binState = "";
            for (Int_t bit = fClockQubitsM - 1; bit >= 0; --bit) {
                binState += ((i >> bit) & 1) ? "1" : "0";
            }
            
            TString item = TString::Format("#frac{%d}{%d} = %s", i, ftotalStates, binState.Data());
            
            if (fClockQubitsM <= 3) {
                // Case m=1, m=2 and m=3: All elements are printed consecutively
                if (i > 0) fractionLine += ",   "; 
                fractionLine += item;
            } else {
                // Case m>3: Only one row, showing only 4 elements and then "..."
                if (i < 3) {
                    if (i > 0) fractionLine += ",   "; 
                    fractionLine += item;
                } else if (i == 3) {
                    fractionLine += ",   " + item + ",  #color[12]{...}";
                    break; // We break the loop to avoid iterating through the remaining states.
                }
            }
        }

        TLatex *lStatesS21 = new TLatex(0.20, 0.68, fractionLine.Data());
        lStatesS21->SetNDC();
        lStatesS21->SetTextFont(132);
        lStatesS21->SetTextSize(0.040);
        lStatesS21->SetTextColor(kBlack);
        lStatesS21->Draw();

    }
    
    //? Rendering step 2.2: Register Definitions
    if (microStep >= 2) {

        TString S22titleDesc = "#font[62]{#color[600]{2.2. Quantum Registers Definition:}} Three registers are initialized.";
        TLatex *lTitleS22 = new TLatex(0.02, 0.60, S22titleDesc.Data());
        lTitleS22->SetNDC();
        lTitleS22->SetTextFont(42);
        lTitleS22->SetTextSize(0.040);
        lTitleS22->SetTextColor(kGray+3);
        lTitleS22->Draw();
        
        // Clock Register
        TString clockReg = TString::Format(
            "\\bullet \\text{  Clock Register: } |0\\rangle^{\\otimes %d}_C \\quad \\longrightarrow  \\text{stores eigenvalues in binary}",
            fClockQubitsM
        );
        TLatex *lClock = new TLatex(0.04, 0.54, clockReg.Data());
        lClock->SetNDC();
        lClock->SetTextFont(152);
        lClock->SetTextSize(0.040);
        lClock->SetTextColor(kBlack);
        lClock->Draw();
        
        // Index Register
        TString indexReg = "\\bullet \\text{  Index Register: } |b\\rangle_I \\quad \\longrightarrow  \\text{stores normalized problem vector, calculated in step 1}";
        TLatex *lIndex = new TLatex(0.04, 0.48, indexReg.Data());
        lIndex->SetNDC();
        lIndex->SetTextFont(152);
        lIndex->SetTextSize(0.040);
        lIndex->SetTextColor(kBlack);
        lIndex->Draw();
        
        // Ancilla Register
        TString ancillaReg = "\\bullet \\text{  Ancilla Register: } |0\\rangle_A \\quad \\longrightarrow  \\text{auxiliary qubit for eigenvalue inversion}";
        TLatex *lAncilla = new TLatex(0.04, 0.42, ancillaReg.Data());
        lAncilla->SetNDC();
        lAncilla->SetTextFont(152);
        lAncilla->SetTextSize(0.040);
        lAncilla->SetTextColor(kBlack);
        lAncilla->Draw();

    }
    
    //? Rendering step 2.3: Global Initial State
    if (microStep >= 3) {

        TString S23titleDesc = "#font[62]{#color[600]{ 2.3. Global Initial State:}} Tensor product of all registers.";
        TLatex *lTitleS23 = new TLatex(0.02, 0.34, S23titleDesc.Data());
        lTitleS23->SetNDC();
        lTitleS23->SetTextFont(42);
        lTitleS23->SetTextSize(0.040);
        lTitleS23->SetTextColor(kGray+3);
        lTitleS23->Draw();
        
        TString globalState = TString::Format(
            "|#Psi_{0}#GT = |0#GT^{#otimes%d}_{C} #otimes #color[635]{|b#GT_{I}} #otimes |0#GT_{A}",
            fClockQubitsM
        );
        TLatex *lGlobal = new TLatex(0.04, 0.27, globalState.Data());
        lGlobal->SetNDC();
        lGlobal->SetTextFont(132);
        lGlobal->SetTextSize(0.050);
        lGlobal->SetTextColor(kBlack);
        lGlobal->Draw();

    }
    
    //? Rendering step 2.4: Substitution with eigenvector expansion
    if (microStep >= 4) {

        TString S24titleDesc = "#font[62]{#color[600]{2.4. Eigenvector Expansion:}} Substituting |b#GT by its spectral decomposition.";
        TLatex *lTitleS24 = new TLatex(0.02, 0.18, S24titleDesc.Data());
        lTitleS24->SetNDC();
        lTitleS24->SetTextFont(42);
        lTitleS24->SetTextSize(0.040);
        lTitleS24->SetTextColor(kGray+3);
        lTitleS24->Draw();
        
        TString b1Str = FormatComplex(fbetaNum1);
        TString b2Str = FormatComplex(fbetaNum2);

        TString sign1, val1, sign2, val2;
        DecomposeSign(b1Str, sign1, val1);
        DecomposeSign(b2Str, sign2, val2);
        
        TString expansion = TString::Format(
            "|#Psi_{0}#GT = |0#GT^{#otimes%d}_{C} #otimes "
            "#color[419]{#left[ #frac{%s}{#sqrt{%.0f}} |u_{1}#GT %s #frac{%s}{#sqrt{%.0f}} |u_{2}#GT #right]_{I}}"
            "#otimes |0#GT_{A}",
            fClockQubitsM,
            b1Str.Data(), fIntDenomSq,
            sign2.Data(), val2.Data(), fIntDenomSq
        );
        TLatex *lExpansion = new TLatex(0.04, 0.10, expansion.Data());
        lExpansion->SetNDC();
        lExpansion->SetTextFont(132);
        lExpansion->SetTextSize(0.050);
        lExpansion->SetTextColor(kBlack);
        lExpansion->Draw();

    }

}

void QHHLA_SoftEdu::DrawMatrix_Step2(Int_t microStep){

    // Calculate dimensionalities
    Int_t nTotal = fClockQubitsM + 2;  // m clock + 1 index + 1 ancilla
    Int_t vectorSize = TMath::Power(2, nTotal);
    
    // Lambda Auxiliary function for drawing custom matrix brackets
    auto DrawBracket = [](Double_t x, Double_t yMin, Double_t yMax, Bool_t isLeft) {
        TLine *lMain = new TLine(x, yMin, x, yMax);
        lMain->SetLineWidth(2);
        lMain->Draw();
        Double_t w = 0.01;
        Double_t xH = isLeft ? x + w : x - w;
        TLine *lTop = new TLine(x, yMax, xH, yMax);
        lTop->SetLineWidth(2); lTop->Draw();
        TLine *lBot = new TLine(x, yMin, xH, yMin);
        lBot->SetLineWidth(2); lBot->Draw();
    };

    // Lambda Auxiliary function to center text 
    auto DrawTextCenter = [](Double_t x, Double_t y, const char* text, Int_t color=kBlack, Double_t size=0.03, Int_t font=42) {
        TLatex *l = new TLatex(x, y, text);
        l->SetNDC();
        l->SetTextAlign(22);
        l->SetTextFont(font);
        l->SetTextSize(size);
        l->SetTextColor(color);
        l->Draw();
        return l;
    };

    //? Rendering step 5: Global Column Vector Structure:
    if (microStep >= 5) {

        TString title = "#font[62]{#color[600]{2.5. Global Column Vector Structure:}}";
        TLatex *lTitle = new TLatex(0.02, 0.82, title.Data());
        lTitle->SetNDC(); 
        lTitle->SetTextSize(0.04); 
        lTitle->Draw();

        TString eq1 = TString::Format(
            "Total System Dimensionality: m_{clock} + n_{index} + n_{ancilla} = %d + 1 + 1 = %d", 
            fClockQubitsM, nTotal);
        TLatex *lEqS26a = new TLatex(0.04, 0.12, eq1.Data());
        lEqS26a->SetNDC();
        lEqS26a->SetTextFont(42);
        lEqS26a->SetTextSize(0.04);
        lEqS26a->SetTextColor(kBlack);
        lEqS26a->Draw();
        TString eq2 = TString::Format(
            "Dimension: 2^{n_{total}} = 2^{%d} = %d states", 
            nTotal, vectorSize);
        TLatex *lEqS26b = new TLatex(0.04, 0.05, eq2.Data());
        lEqS26b->SetNDC();
        lEqS26b->SetTextFont(42);
        lEqS26b->SetTextSize(0.04);
        lEqS26b->SetTextColor(kRed+3);
        lEqS26b->Draw();
        
    }

    //? Micro-paso 6: Detailed Visualization of the Kronecker Product
    if (microStep >= 6) {

        // --- Vector Clock ---
        DrawBracket(0.12, 0.30, 0.65, kTRUE);
        DrawBracket(0.18, 0.30, 0.65, kFALSE);
        DrawTextCenter(0.15, 0.60, "1", kGreen+3, 0.045);
        DrawTextCenter(0.15, 0.53, "0", kGray+3, 0.045);
        DrawTextCenter(0.15, 0.45, ".", kGray+3, 0.045);
        DrawTextCenter(0.15, 0.43, ".", kGray+3, 0.045);
        DrawTextCenter(0.15, 0.41, ".", kGray+3, 0.045);
        DrawTextCenter(0.15, 0.35, "0", kGray+3, 0.045);
        DrawTextCenter(0.15, 0.25, TString::Format("2^{%d} #times 1", fClockQubitsM), kGreen+3, 0.035);
        DrawTextCenter(0.15, 0.70, "|0#GT_{C}^{#otimes m}", kGreen+3, 0.050);

        // Tensor Operator
        DrawTextCenter(0.23, 0.47, "#otimes", kBlack, 0.05);

        // --- Index Vector ---
        DrawBracket(0.28, 0.35, 0.60, kTRUE);
        DrawBracket(0.38, 0.35, 0.60, kFALSE);
        DrawTextCenter(0.33, 0.52, "#beta_{1}", kBlue+3, 0.045);
        DrawTextCenter(0.33, 0.42, "#beta_{2}", kBlue+3, 0.045);
        DrawTextCenter(0.33, 0.30, "2^{1} #times 1", kBlue+3, 0.035);
        DrawTextCenter(0.33, 0.70, "|b#GT_{I}", kBlue+3, 0.05);

        // Operador Tensor
        DrawTextCenter(0.43, 0.47, "#otimes", kBlack, 0.05);

        // --- Vector Ancilla ---
        DrawBracket(0.48, 0.35, 0.60, kTRUE);
        DrawBracket(0.54, 0.35, 0.60, kFALSE);
        DrawTextCenter(0.51, 0.52, "1", kCyan+2, 0.045);
        DrawTextCenter(0.51, 0.42, "0", kGray+3, 0.045);
        DrawTextCenter(0.51, 0.30, "2^{1} #times 1", kCyan+2, 0.035);
        DrawTextCenter(0.51, 0.70, "|0#GT_{A}", kCyan+2, 0.05);

    }

    //? Micro-paso 7: The Giant Column Vector
    if (microStep >= 7) {

        DrawTextCenter(0.60, 0.47, "=", kBlack, 0.05);

        // Draw the large global vector 
        DrawBracket(0.66, 0.15, 0.80, kTRUE);
        DrawBracket(0.78, 0.15, 0.80, kFALSE);
        
        DrawTextCenter(0.72, 0.85, "|#Psi_{0}#GT", kRed+2, 0.05, 62);
        
        // Internal elements: Note how β₁ and β₂ are separated by a 0 due to the anchor |0>
        DrawTextCenter(0.72, 0.76, "#beta_{1}", kBlue, 0.045);
        DrawTextCenter(0.72, 0.68, "0", kGray+3, 0.045);
        DrawTextCenter(0.72, 0.60, "#beta_{2}", kBlue, 0.045);
        DrawTextCenter(0.72, 0.52, "0", kGray+3, 0.045);
        DrawTextCenter(0.72, 0.45, "0", kGray+3, 0.045);
        DrawTextCenter(0.72, 0.38, ".", kGray+3, 0.045);
        DrawTextCenter(0.72, 0.36, ".", kGray+3, 0.045);
        DrawTextCenter(0.72, 0.34, ".", kGray+3, 0.045);
        DrawTextCenter(0.72, 0.27, "0", kGray+3, 0.045);
        DrawTextCenter(0.72, 0.20, "0", kGray+3, 0.045);

        DrawTextCenter(0.72, 0.10, TString::Format("Dimension: %d #times 1", vectorSize), kRed+2, 0.035, 62);
        
        // Arrows pointing to the β constants
        TArrow *arrow1 = new TArrow(0.81, 0.76, 0.75, 0.76, 0.01, "|>");
        arrow1->SetLineColor(kBlue); arrow1->SetFillColor(kBlue); arrow1->SetLineWidth(2);
        arrow1->Draw();
        
        TArrow *arrow2 = new TArrow(0.81, 0.60, 0.75, 0.60, 0.01, "|>");
        arrow2->SetLineColor(kBlue); arrow2->SetFillColor(kBlue); arrow2->SetLineWidth(2);
        arrow2->Draw();
        
        TString b1Str = FormatComplex(fbetaNum1);
        TString b2Str = FormatComplex(fbetaNum2);


        // Labels β₁ and β₂ next to the arrows
        TLatex *beta1Label = new TLatex(0.83, 0.76, TString::Format("#frac{%s}{#sqrt{%.0f}}",b1Str.Data(),fIntDenomSq));
        beta1Label->SetNDC();
        beta1Label->SetTextAlign(12);
        beta1Label->SetTextFont(42);
        beta1Label->SetTextSize(0.045);
        beta1Label->SetTextColor(kBlue);
        beta1Label->Draw();
        
        TLatex *beta2Label = new TLatex(0.83, 0.60, TString::Format("#frac{%s}{#sqrt{%.0f}}",b2Str.Data(),fIntDenomSq));
        beta2Label->SetNDC();
        beta2Label->SetTextAlign(12);
        beta2Label->SetTextFont(42);
        beta2Label->SetTextSize(0.045);
        beta2Label->SetTextColor(kBlue);
        beta2Label->Draw();
        
    }

}

void QHHLA_SoftEdu::DrawCircuit_Step2(Int_t microStep){

    // Position parameters
    Double_t xStart = 0.05;        // Start of the lines
    Double_t xEnd = 0.95;          // End of the lines
    Double_t yIndex = 0.75;        // Position Y of the Index record (top)
    Double_t yAncilla = 0.20;      // Y position of the Ancilla qubit (lower)
    Double_t yClockStart = 0.65;   // Clock bus start
    Double_t yClockSpacing = 0.10; // Space between clock qubits
    
    //? Rendering step 2.8: Circuit Skeleton
    if (microStep >= 8) {

        // TOP LINE: Memory/Index Register
        TLine *lineIndex = new TLine(xStart, yIndex, xEnd, yIndex);
        lineIndex->SetLineWidth(2);
        lineIndex->SetLineColor(kBlue+3);
        lineIndex->Draw();
        
        // Initial state |0⟩ for index record
        TLatex *stateIndex = new TLatex(xStart - 0.035, yIndex-0.015, "|0#GT_{I}");
        stateIndex->SetNDC();
        stateIndex->SetTextFont(62);
        stateIndex->SetTextSize(0.05);
        stateIndex->SetTextColor(kBlue+3);
        stateIndex->Draw();
        
        // CENTRAL LINES: Clock Register m-qubit bus
        for (Int_t i = 0; i < fClockQubitsM; i++) {
            Double_t yClock = yClockStart - (i * yClockSpacing);
            
            TLine *lineClock = new TLine(xStart, yClock, xEnd, yClock);
            lineClock->SetLineWidth(2);
            lineClock->SetLineColor(kGreen+3);
            lineClock->Draw();
            
            // Initial state |0⟩ for each qubit of the clock
            TLatex *stateClock = new TLatex(xStart - 0.035, yClock - 0.015, "|0#GT_{C}");
            stateClock->SetNDC();
            stateClock->SetTextFont(62);
            stateClock->SetTextSize(0.05);
            stateClock->SetTextColor(kGreen+3);
            stateClock->Draw();
            
        }
        
        // BOTTOM LINE: Qubit Ancilla
        TLine *lineAncilla = new TLine(xStart, yAncilla, xEnd, yAncilla);
        lineAncilla->SetLineWidth(2);
        lineAncilla->SetLineColor(kCyan+3);
        lineAncilla->Draw();
        
        // Initial state |0> for the ancilla
        TLatex *stateAncilla = new TLatex(xStart - 0.03, yAncilla - 0.015, "|0#GT_{A}");
        stateAncilla->SetNDC();
        stateAncilla->SetTextFont(62);
        stateAncilla->SetTextSize(0.05);
        stateAncilla->SetTextColor(kCyan+3);
        stateAncilla->Draw();
        
    }

}

void QHHLA_SoftEdu::DrawGraph_Step2(Int_t microStep){

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    c->cd();
    c->Clear();
    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right
    
    Double_t prob1 = fBeta1.Rho2(); 
    Double_t prob2 = fBeta2.Rho2();
    
    // Validate mathematical security (If they are NaN by some error, force them to 0)
    if (TMath::IsNaN(prob1)) prob1 = 0.0;
    if (TMath::IsNaN(prob2)) prob2 = 0.0;
    
    TString state1Label = "|0...0#GT |u_{1}#GT |0#GT";
    TString state2Label = "|0...0#GT |u_{2}#GT |0#GT";

    //? Rendering of the State Equation |Ψ_0⟩
    if (microStep >= 10) {
        TPaveText *eqBox = new TPaveText(0.01, 0.01, 0.50, 0.12, "NDC");
        eqBox->SetFillColor(kWhite);
        eqBox->SetBorderSize(1);
        eqBox->SetLineColor(kGray+1);
        eqBox->SetTextAlign(22);
        eqBox->SetTextSize(0.040);
        eqBox->SetTextFont(132);
        eqBox->SetTextColor(kRed+3);
        
        TString eqText = "|#Psi_{0}#GT = |0#GT^{#otimesm}_{C} #otimes #left[ #beta_{1}|u_{1}#GT + #beta_{2}|u_{2}#GT #right]_{I} #otimes |0#GT_{A}";
        eqBox->AddText(eqText.Data());
        eqBox->Draw();
    }

    // CREATION OF THE CONTAINER
    TPad *plotPad = new TPad("plotPad", "Región del Gráfico", 0.01, 0.12, 0.99, 0.88);
    plotPad->Draw();
    plotPad->cd();
    
    // Give internal margins to the Pad
    plotPad->SetBottomMargin(0.18); 
    plotPad->SetTopMargin(0.12);
    plotPad->SetGrid(1, 1); 
    
    //? Rendering step 2.9: Probability Histogram
    if (microStep >= 9) {
        
        // Al instanciar el TH1F, es mejor pasarle una estructura de ejes mínima (;)
        TH1F *hist = new TH1F("probHist", ";Quantum state;Probability P = |#beta_{i}|^{2}", 2, 0, 2);
        hist->SetDirectory(0); 
        hist->SetStats(0);     
        
        hist->SetMinimum(0.0);   
        hist->SetMaximum(1.15);
        
        // Configure the X-axis labels
        hist->GetXaxis()->SetBinLabel(1, state1Label.Data());
        hist->GetXaxis()->SetBinLabel(2, state2Label.Data());
        hist->GetXaxis()->SetLabelSize(0.06);
        hist->GetXaxis()->SetTitleSize(0.045); 
        hist->GetXaxis()->SetLabelFont(42);
        hist->GetXaxis()->SetTickLength(0);   
        
        // Configure the Y-axis
        hist->GetYaxis()->SetTitleSize(0.04);
        hist->GetYaxis()->SetTitleOffset(1.1);
        hist->GetYaxis()->SetLabelSize(0.04);
        hist->GetYaxis()->SetTitleSize(0.045);
        
        // Establish the probability values
        hist->SetBinContent(1, prob1);
        hist->SetBinContent(2, prob2);
        
        // Bar style
        hist->SetFillColor(kAzure-5);
        hist->SetFillStyle(1001);
        hist->SetLineColor(kAzure+2);
        hist->SetLineWidth(2);
        hist->SetBarOffset(0.2); 
        hist->SetBarWidth(0.6);  
        
        // Draw the histogram
        hist->Draw("BAR");
        
        // Add numeric value labels above each bar
        TLatex *label1 = new TLatex(0.5, prob1 + 0.04, TString::Format("%.2f", prob1).Data());
        label1->SetTextAlign(22); 
        label1->SetTextSize(0.035); 
        label1->SetTextColor(kBlue+2);
        label1->Draw();
        
        TLatex *label2 = new TLatex(1.5, prob2 + 0.04, TString::Format("%.2f", prob2).Data());
        label2->SetTextAlign(22); 
        label2->SetTextSize(0.035); 
        label2->SetTextColor(kBlue+2);
        label2->Draw();
        
        // Title
        TLatex *titleText = new TLatex(0.5, 0.93, "#color[600]{#font[62]{Probability Distribution of the Initial State |#Psi_{0}#GT}}");
        titleText->SetNDC();
        titleText->SetTextAlign(22);
        titleText->SetTextSize(0.050);
        titleText->SetTextColor(kBlack);
        titleText->Draw();
    }
    
    //? Rendering step 2.10: Equations and Note
    if (microStep >= 10) {

        TPaveText *probBox = new TPaveText(0.85, 0.75, 0.95, 0.95, "NDC");
        probBox->SetFillColor(kYellow-9);
        probBox->SetBorderSize(1);
        probBox->SetLineColor(kOrange-2);
        probBox->SetTextAlign(12);
        probBox->SetTextSize(0.035);
        probBox->SetTextFont(42);
        probBox->SetMargin(0.08);
        
        probBox->AddText(TString::Format("|#beta_{1}|^{2} = %.2f", prob1).Data());
        probBox->AddText(TString::Format("|#beta_{2}|^{2} = %.2f", prob2).Data());
        probBox->AddLine(0.1, 0.35, 0.9, 0.35); 
        probBox->AddText(TString::Format("Sum = %.2f", prob1 + prob2).Data());
        probBox->Draw();
    
    }

    c->Modified();
    c->Update();
    c->cd();
    
}

//* MODULAR METHODS: STEP 3 (Time Superposition) ------------------------------
void QHHLA_SoftEdu::DrawMath_Step3(Int_t microStep){

    Int_t m = fClockQubitsM; 
    Int_t lim_t = TMath::Power(2, m) - 1; // Calculate 2^m - 1 automatically
    
    //Initializes the clock register to zeros, depending on the number m qubits
    std::string ceros_std(m, '0'); 
    TString ceros(ceros_std.c_str());

    // Dynamic construction of the expanded summation
    TString expandedSum = "#left[ ";
        if (m <= 3) {
            // For m=1, 2, or 3, the limit is small (1, 3, or 7). We print everything.
            for (Int_t t = 0; t <= lim_t; t++) {
                expandedSum += TString::Format("|%d#GT", t);
                if (t < lim_t) expandedSum += " + "; // Add the '+' unless it is the last one
            }
        } else {
            // For m > 3, we use an ellipsis to prevent the Canvas from overflowing.
            expandedSum = TString::Format("|0#GT + |1#GT + ... + |%d#GT", lim_t);
        }
    expandedSum += " #right]_{C}";

    // Dynamic construction of the summation in binary
    TString expandedBinarySum = "#left[ ";
    if (m <= 3) {
        // For each small number, we iterate and print it in binary.
        for (Int_t t = 0; t <= lim_t; t++) {
            TString binStr = "";
            // We read the bits from left to right to form the string.
            for (Int_t bit = m - 1; bit >= 0; bit--) {
                binStr += ((t >> bit) & 1) ? "1" : "0";
            }
            
            expandedBinarySum += TString::Format("|%s#GT", binStr.Data());
            if (t < lim_t) expandedBinarySum += " + "; 
        }
    } else {
        // For m > 3, we avoid overflowing the screen by showing the beginning and the end.
        TString firstBin(std::string(m, '0').c_str());             // Ej: 0000
        TString secBin(std::string(m - 1, '0').c_str()); secBin += "1"; // Ej: 0001
        TString lastBin(std::string(m, '1').c_str());              // Ej: 1111 (The limit 2^m - 1 always consists entirely of 1s)
        
        expandedBinarySum = TString::Format("|%s#GT + |%s#GT + ... + |%s#GT", 
                                            firstBin.Data(), secBin.Data(), lastBin.Data());
    }
    expandedBinarySum += " #right]_{C}";


    //? Rendering step 3.1: Hadamard Action on Clock Register
    if (microStep >= 1) {
        TString S31titleDesc = "#font[62]{#color[600]{3.1. Hadamard Action:}} Applying H^{#otimesm} to the Clock Register.";
        TLatex *lTitleS31 = new TLatex(0.02, 0.80, S31titleDesc.Data());
        lTitleS31->SetNDC();
        lTitleS31->SetTextFont(42);
        lTitleS31->SetTextSize(0.040);
        lTitleS31->SetTextColor(kGray+3);
        lTitleS31->Draw();
        
        // Hadamard transformation
        TString eq31 = TString::Format(
            "H^{#otimesm}|0...0#GT^{m}_{C} = #frac{1}{#sqrt{2^{m}}}#sum_{t=0}^{2^{m}-1}|t#GT_{C}"
            "    #color[2]{#rightarrow}  "
            "#scale[0.8]{#font[42]{#color[635]{For m = %.i qubits}}}"
            "  #color[2]{#rightarrow}    "
            "H^{#otimes#color[419]{%.i}}|#color[419]{%s}#GT_{C} = #frac{1}{#sqrt{#color[419]{%.d}}}#sum_{t=0}^{#color[419]{%.i}}|t#GT_{C}",
            m,m,ceros.Data(),ftotalStates,lim_t
        );
            
        TLatex *lEqS31 = new TLatex(0.04, 0.70, eq31.Data()); 
        lEqS31->SetNDC();
        lEqS31->SetTextFont(132);     
        lEqS31->SetTextSize(0.055);
        lEqS31->SetTextColor(kBlack); 
        lEqS31->Draw();
        
    }
    
    //? Rendering step 3.2: Time interpretation:
    if (microStep >= 2) {
        TString S32titleDesc = "#font[62]{#color[600]{3.2. Time interpretation:}} We have an equiprobable superposition of integer (times) t.";
        TLatex *lTitleS32 = new TLatex(0.02, 0.60, S32titleDesc.Data());
        lTitleS32->SetNDC();
        lTitleS32->SetTextFont(42);
        lTitleS32->SetTextSize(0.040);
        lTitleS32->SetTextColor(kGray+3);
        lTitleS32->Draw();
        
        TString eq32a = TString::Format(
            "H^{#otimes%.i}|%s#GT_{C} = #frac{1}{#sqrt{%.d}} = #color[419]{%s}",
            m, ceros.Data(),ftotalStates, expandedSum.Data()
        );  
        TLatex *lEqS32a = new TLatex(0.04, 0.50, eq32a.Data()); 
        lEqS32a->SetNDC();
        lEqS32a->SetTextFont(132);     
        lEqS32a->SetTextSize(0.053);
        lEqS32a->SetTextColor(kBlack); 
        lEqS32a->Draw();

        TString eq32b = TString::Format(
            "#scale[0.8]{#font[42]{#color[635]{In binary}}}"
            " #color[2]{#rightarrow} "
            "#frac{1}{#sqrt{%d}} #color[419]{%s}",
            ftotalStates, expandedBinarySum.Data()
        );  
        TLatex *lEqS32b = new TLatex(0.04, 0.40, eq32b.Data()); 
        lEqS32b->SetNDC();
        lEqS32b->SetTextFont(132);     
        lEqS32b->SetTextSize(0.053);
        lEqS32b->SetTextColor(kBlack); 
        lEqS32b->Draw();
    }

    //? Rendering step 3.3: Resulting Global State |Ψ_1⟩
    if (microStep >= 3) {
        TString S33titleDesc = "#font[62]{#color[600]{3.3. Resulting Global State |#Psi_{1}#GT:}}";
        TLatex *lTitleS33 = new TLatex(0.02, 0.30, S33titleDesc.Data());
        lTitleS33->SetNDC();
        lTitleS33->SetTextFont(42);
        lTitleS33->SetTextSize(0.040);
        lTitleS33->SetTextColor(kGray+3);
        lTitleS33->Draw();

        TString b1Str = FormatComplex(fbetaNum1);
        TString b2Str = FormatComplex(fbetaNum2);

        TString sign1, val1, sign2, val2;
        DecomposeSign(b1Str, sign1, val1);
        DecomposeSign(b2Str, sign2, val2);

        TString eq33 = TString::Format(
            "|#Psi_{1}#GT = #color[419]{#frac{1}{#sqrt{%d}}} #color[419]{%s} #otimes "
            "#left[ #frac{%s}{#sqrt{%.0f}}|u_{1}#GT %s #frac{%s}{#sqrt{%.0f}}|u_{2}#GT #right]_{I} "
            "#otimes  |0#GT_{A}",
            ftotalStates, expandedSum.Data(),
            b1Str.Data(), fIntDenomSq,
            sign2.Data(), val2.Data(), fIntDenomSq
        );
            
        TLatex *lEqS33 = new TLatex(0.04, 0.20, eq33.Data()); 
        lEqS33->SetNDC();
        lEqS33->SetTextFont(132);     
        lEqS33->SetTextSize(0.055);
        lEqS33->SetTextColor(kBlack); 
        lEqS33->Draw();
    
    }

}

void QHHLA_SoftEdu::DrawMatrix_Step3(Int_t microStep){
    
    //? Rendering step 3.4: Standard Hadamard Gate (2x2 Base)
    if (microStep >= 4) {
        TString S34titleDesc = "#font[62]{#color[600]{3.4. Standard Hadamard Gate (1 Qubit):}}";
        TLatex *lTitleS34 = new TLatex(0.02, 0.80, S34titleDesc.Data());
        lTitleS34->SetNDC();
        lTitleS34->SetTextFont(42);
        lTitleS34->SetTextSize(0.040);
        lTitleS34->SetTextColor(kGray+3);
        lTitleS34->Draw();
        
        // Matrix representation using #splitline for vertical alignment
        TString eq34 = "H = #frac{1}{#sqrt{2}} #left[ #splitline{1}{1}     #splitline{ 1}{-1} #right]";
        TLatex *lEqS34 = new TLatex(0.40, 0.80, eq34.Data());
        lEqS34->SetNDC();
        lEqS34->SetTextFont(132);
        lEqS34->SetTextSize(0.050);
        lEqS34->SetTextColor(kBlack);
        lEqS34->Draw();
    }

    //? Rendering step 3.5: Global Operator Construction (Kronecker Product)
    if (microStep >= 5) {
        TString S35titleDesc = "#font[62]{#color[600]{3.5. Global Operator for Clock Register:}}";
        TLatex *lTitleS35 = new TLatex(0.02, 0.70, S35titleDesc.Data());
        lTitleS35->SetNDC();
        lTitleS35->SetTextFont(42);
        lTitleS35->SetTextSize(0.040);
        lTitleS35->SetTextColor(kGray+3);
        lTitleS35->Draw();
        
        // Dynamic loop to draw the exact tensor product based on "m"
        TString kronecker = "H^{#otimes m} = ";
        for(Int_t i = 0; i < fClockQubitsM; i++) {
            if(i > 0) kronecker += " #otimes ";
            kronecker += "H";
        }
        
        TLatex *lEqS35 = new TLatex(0.10, 0.60, kronecker.Data());
        lEqS35->SetNDC();
        lEqS35->SetTextFont(132);
        lEqS35->SetTextSize(0.055);
        lEqS35->SetTextColor(kBlack);
        lEqS35->Draw();
        
        TString explanation = TString::Format(
            "#color[2]{#rightarrow} #color[419]{Applied simultaneously on m = %d qubits}",
            fClockQubitsM
        );
        TLatex *lExpS35 = new TLatex(0.35, 0.60, explanation.Data());
        lExpS35->SetNDC();
        lExpS35->SetTextFont(42);
        lExpS35->SetTextSize(0.045);
        lExpS35->SetTextColor(kGray+2);
        lExpS35->Draw();
    }

    //? Rendering step 3.6: Advanced Touch (Expanded Walsh-Hadamard Matrix)
    if (microStep >= 6) {
        Int_t dim = TMath::Power(2, fClockQubitsM);
        
        TString S36titleDesc = TString::Format(
            "#font[62]{#color[600]{3.6. Expanded Transformation (%d#times%d):}}",
            dim, dim);
        TLatex *lTitleS36 = new TLatex(0.02, 0.50, S36titleDesc.Data());
        lTitleS36->SetNDC();
        lTitleS36->SetTextFont(42);
        lTitleS36->SetTextSize(0.040);
        lTitleS36->SetTextColor(kGray+3);
        lTitleS36->Draw();
        
        // Safeguard: If m > 4 (32x32 matrix or larger), don't draw to avoid visual overlap
        if (fClockQubitsM > 4) {
            TLatex *lWarn = new TLatex(0.20, 0.30, "#color[2]{[Matrix too large to display on screen]}");
            lWarn->SetNDC();
            lWarn->SetTextFont(42);
            lWarn->SetTextSize(0.04);
            lWarn->SetTextColor(kRed+2);
            lWarn->Draw();
        } else {
            // Dynamic variables to scale size based on matrix dimension
            Double_t centerY = 0.27; 
            Double_t startX = 0.30;
            Double_t stepX = 0.02;
            Double_t stepY = 0.02;
            Int_t textSize = 0;
            
            if (dim == 4) { stepX = 0.08; stepY = 0.08; textSize = 50; }
            if (dim == 8) { stepX = 0.05; stepY = 0.05; textSize = 42; }
            if (dim == 16){ stepX = 0.035; stepY = 0.015; textSize = 20; startX = 0.25; centerY = 0.15; }
            
            Double_t b_top = centerY + (dim * stepY) / 2.0;
            Double_t b_bot = centerY - (dim * stepY) / 2.0;
            
            // Draw external normalization fraction
            TString norm = TString::Format("H^{#otimes%d} = #frac{1}{#sqrt{%d}}", fClockQubitsM, dim);
            TLatex *lNorm = new TLatex(0.20, centerY, norm.Data());
            lNorm->SetNDC();
            lNorm->SetTextAlign(22);
            lNorm->SetTextFont(132);
            lNorm->SetTextSize(0.055);
            lNorm->SetTextColor(kBlack);
            lNorm->Draw();
            
            // ALGORITHM: Matrix generation via bit manipulation
            for (Int_t r = 0; r < dim; ++r) {
                for (Int_t col = 0; col < dim; ++col) {
                    // Count set bits in bitwise AND between row and column
                    Int_t bitwiseAnd = r & col;
                    Int_t count = 0;
                    while (bitwiseAnd > 0) {
                        count += (bitwiseAnd & 1);
                        bitwiseAnd >>= 1;
                    }
                    
                    Double_t x = startX + col * stepX;
                    Double_t y = b_top - (r + 0.5) * stepY;
                    
                    if (count % 2 == 0) {
                        // Positive Phase (Blue Color)
                        TLatex *lPos = new TLatex(x, y, "#color[4]{1}");
                        lPos->SetNDC();
                        lPos->SetTextAlign(22);
                        lPos->SetTextFont(42);
                        lPos->SetTextSize(textSize * 0.001);
                        lPos->Draw();
                    } else {
                        // Negative Phase (Red Color)
                        TLatex *lNeg = new TLatex(x, y, "#color[2]{-1}");
                        lNeg->SetNDC();
                        lNeg->SetTextAlign(22);
                        lNeg->SetTextFont(42);
                        lNeg->SetTextSize(textSize * 0.001);
                        lNeg->Draw();
                    }
                }
            }
            
            // Draw giant brackets with TLine to encapsulate the matrix
            TLine *lineLeft = new TLine();
            lineLeft->SetLineWidth(2);
            Double_t b_left = startX - stepX/2.0;
            Double_t b_right = startX + (dim - 1)*stepX + stepX/2.0;
            
            // Left Bracket '['
            lineLeft->DrawLine(b_left, b_top, b_left, b_bot);
            lineLeft->DrawLine(b_left, b_top, b_left+0.01, b_top);
            lineLeft->DrawLine(b_left, b_bot, b_left+0.01, b_bot);
            
            // Right Bracket ']'
            lineLeft->DrawLine(b_right, b_top, b_right, b_bot);
            lineLeft->DrawLine(b_right, b_top, b_right-0.01, b_top);
            lineLeft->DrawLine(b_right, b_bot, b_right-0.01, b_bot);

        }

    }
    
}

void QHHLA_SoftEdu::DrawCircuit_Step3(Int_t microStep){

    // Position parameters
    Double_t xStart = 0.05;        // Start of the lines
    Double_t xEnd = 0.95;          // End of the lines
    Double_t yIndex = 0.75;        // Position Y of the Index record (top)
    Double_t yAncilla = 0.20;      // Y position of the Ancilla qubit (lower)
    Double_t yClockStart = 0.65;   // Clock bus start
    Double_t yClockSpacing = 0.10; // Space between clock qubits

    // Gate dimensions (Hadamard)
    Double_t hGateX1 = 0.07;
    Double_t hGateX2 = 0.11;
    Double_t hGateHalfHeight = 0.04;
    
    //? Rendering step 3.7: Circuit Diagram step 3
    if (microStep >= 7) {

        // TOP LINE: Memory/Index Register
        TLine *lineIndex = new TLine(xStart, yIndex, xEnd, yIndex);
        lineIndex->SetLineWidth(2);
        lineIndex->SetLineColor(kBlue+3);
        lineIndex->Draw();
        
        // Initial state |0⟩ for index record
        TLatex *stateIndex = new TLatex(xStart - 0.035, yIndex-0.015, "|b#GT_{I}");
        stateIndex->SetNDC();
        stateIndex->SetTextFont(62);
        stateIndex->SetTextSize(0.05);
        stateIndex->SetTextColor(kBlue+3);
        stateIndex->Draw();
        
        // CENTRAL LINES: Clock Register m-qubit bus
        for (Int_t i = 0; i < fClockQubitsM; i++) {

            Double_t yClock = yClockStart - (i * yClockSpacing);
            
            TLine *lineClock = new TLine(xStart, yClock, xEnd, yClock);
            lineClock->SetLineWidth(2);
            lineClock->SetLineColor(kGreen+3);
            lineClock->Draw();
            
            // Initial state |0⟩ for each qubit of the clock
            TLatex *stateClock = new TLatex(xStart - 0.035, yClock - 0.015, "|0#GT_{C}");
            stateClock->SetNDC();
            stateClock->SetTextFont(62);
            stateClock->SetTextSize(0.05);
            stateClock->SetTextColor(kGreen+3);
            stateClock->Draw();

            if (microStep >= 8) {

                // Background box for the gate
                TBox *hBox = new TBox(hGateX1, yClock - hGateHalfHeight, hGateX2, yClock + hGateHalfHeight);
                hBox->SetFillColor(kCyan-10);
                hBox->SetLineColor(kCyan+4);
                hBox->SetLineWidth(1.5);
                hBox->Draw("l");
                
                // Letter 'H' inside the box
                TLatex *hText = new TLatex((hGateX1 + hGateX2)/2.0, yClock, "H");
                hText->SetTextAlign(22);
                hText->SetTextFont(62);
                hText->SetTextSize(0.06);
                hText->SetTextColor(kCyan+4);
                hText->Draw();
            }
            
        }
        
        // BOTTOM LINE: Qubit Ancilla
        TLine *lineAncilla = new TLine(xStart, yAncilla, xEnd, yAncilla);
        lineAncilla->SetLineWidth(2);
        lineAncilla->SetLineColor(kCyan+3);
        lineAncilla->Draw();
        
        // Initial state |0⟩ for the ancilla
        TLatex *stateAncilla = new TLatex(xStart - 0.035, yAncilla - 0.015, "|0#GT_{A}");
        stateAncilla->SetNDC();
        stateAncilla->SetTextFont(62);
        stateAncilla->SetTextSize(0.05);
        stateAncilla->SetTextColor(kCyan+3);
        stateAncilla->Draw();
        
    }

}

void QHHLA_SoftEdu::DrawGraph_Step3(Int_t microStep){

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    c->cd();
    c->Clear();
    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right

    // --- CALCULATION OF THE OVERLAP ---
    Int_t m = fClockQubitsM;
    Int_t lim_t = TMath::Power(2, m) - 1;
    Int_t numStates = TMath::Power(2, m);
    Double_t uniformProb = 1.0 / numStates; // Equiprobability = 1 / 2^m
    
    //? Rendering step 3.10: State Equation |Ψ_1⟩
    if (microStep >= 10) {

        TPaveText *eqBox = new TPaveText(0.01, 0.01, 0.55, 0.12, "NDC");
        eqBox->SetFillColor(kWhite);
        eqBox->SetBorderSize(1);
        eqBox->SetLineColor(kGray+1);
        eqBox->SetTextAlign(22);
        eqBox->SetTextSize(0.040);
        eqBox->SetTextFont(132);
        eqBox->SetTextColor(kRed+3);
        
        TString eq33 = TString::Format(
            "|#Psi_{1}#GT = #frac{1}{#sqrt{%.d}}#sum_{t=0}^{%.i}|t#GT_{C} "
            "#otimes #left[ #beta_{1}|u_{1}#GT + #beta_{2}|u_{2}#GT #right]_{I} "
            "#otimes  |0#GT_{A}",
            ftotalStates, lim_t
        );
        
        eqBox->AddText(eq33.Data());
        eqBox->Draw();

    }

    // CREATION OF THE CONTAINER (PAD)
    TPad *plotPad = new TPad("plotPadStep3", "Región del Gráfico 3", 0.01, 0.12, 0.99, 0.88);
    plotPad->Draw();
    plotPad->cd();
    
    // Inner margins
    plotPad->SetBottomMargin(0.18); 
    plotPad->SetTopMargin(0.12);
    plotPad->SetGrid(1, 1); 
    
    //? Rendering step 3.9: Equiprobable Histogram Rendering
    if (microStep >= 9) {
        
        // The histogram is created dynamically with 'numStates' bars.
        TH1F *hist = new TH1F("probHistStep3", ";Clock Register State |t#GT_{C};Probability P", numStates, 0, numStates);
        hist->SetDirectory(0); 
        hist->SetStats(0);     
        
        hist->SetMinimum(0.0);   
        hist->SetMaximum(uniformProb * 1.6); // Escala el eje Y para que no quede pegado al techo
        
        // Dynamically configure bars and binary labels.
        for (Int_t i = 0; i < numStates; i++) {
            
            TString binLabel = "|";
            for (Int_t bit = m - 1; bit >= 0; bit--) {
                binLabel += ((i >> bit) & 1) ? "1" : "0";
            }
            binLabel += "#GT";
            
            // Assign a label and probability to the current bar.
            hist->GetXaxis()->SetBinLabel(i + 1, binLabel.Data());
            hist->SetBinContent(i + 1, uniformProb);

        }

        // Visual configuration of the axes
        hist->GetXaxis()->SetLabelSize(0.05);
        hist->GetXaxis()->SetTitleSize(0.045); 
        hist->GetXaxis()->SetLabelFont(42);
        hist->GetXaxis()->SetTickLength(0);   
        
        hist->GetYaxis()->SetTitleSize(0.04);
        hist->GetYaxis()->SetTitleOffset(1.1);
        hist->GetYaxis()->SetLabelSize(0.04);
        
        // Bar Style
        hist->SetFillColor(kGreen-7);
        hist->SetFillStyle(1001);
        hist->SetLineColor(kGreen+2);
        hist->SetLineWidth(2);
        hist->SetBarOffset(0.15); 
        hist->SetBarWidth(0.7);  
        
        hist->Draw("BAR");
        
        // Add the numerical values ​​above each bar.
        for (Int_t i = 0; i < numStates; i++) {
            TLatex *label = new TLatex(i + 0.5, uniformProb + (uniformProb * 0.08), TString::Format("%.3f", uniformProb).Data());
            label->SetTextAlign(22); 
            label->SetTextSize(0.035); 
            label->SetTextColor(kGreen+3);
            label->Draw();
        }
        
        // Título del Gráfico
        TLatex *titleText = new TLatex(0.5, 0.93, "#color[416]{#font[62]{Equiprobable Superposition in Clock Register}}"); // 416 es kGreen
        titleText->SetNDC();
        titleText->SetTextAlign(22);
        titleText->SetTextSize(0.050);
        titleText->Draw();
    }

    //? Statistical Summary Table
    if (microStep >= 10) {

        TPaveText *probBox = new TPaveText(0.75, 0.75, 0.95, 0.93, "NDC"); // Movido ligeramente para no tapar barras
        probBox->SetFillColor(kYellow-9);
        probBox->SetBorderSize(1);
        probBox->SetLineColor(kOrange-2);
        probBox->SetTextAlign(12);
        probBox->SetTextSize(0.035);
        probBox->SetTextFont(42);
        probBox->SetMargin(0.08);
        
        probBox->AddText(TString::Format("Total States = 2^{%d} = %d", m, numStates).Data());
        probBox->AddText(TString::Format("Uniform P = 1/%d = %.3f", numStates, uniformProb).Data());
        probBox->AddLine(0.1, 0.35, 0.9, 0.35); 
        probBox->AddText("Total Sum = 1.000");
        probBox->Draw();
    }
    
    c->Modified();
    c->Update();
    c->cd();
    
}

//* MODULAR METHODS: STEP 4 (Controlled Unitary Evolution) --------------------
void QHHLA_SoftEdu::DrawMath_Step4(Int_t microStep){
    
    TString b1Str = FormatComplex(fbetaNum1);
    TString b2Str = FormatComplex(fbetaNum2);
    TString sign1, val1, sign2, val2;
    DecomposeSign(b1Str, sign1, val1);
    DecomposeSign(b2Str, sign2, val2);

    Int_t m = fClockQubitsM; 
    Int_t lim_t = TMath::Power(2, m) - 1; // Calculate 2^m - 1 automatically

    // Dynamic construction of the expanded summation for λ₁
        TString expandedSum1 = "#left[ #scale[1.5]{e}^{0}|0#GT + ";
            if (m <= 3) {
                // For m=1, 2, or 3, the limit is small (1, 3, or 7). We print everything.
                for (Int_t t = 1; t <= lim_t; t++) {
                    expandedSum1 += TString::Format(
                        "#scale[1.5]{e}^{i(%.2f)(#pi/%.0f)%d}|%d#GT", 
                        fLambda1, fDemTau, t, t
                    );
                    if (t < lim_t) expandedSum1 += " + "; // Add the '+' unless it is the last one
                }
            } else {
                // For m > 3, we use an ellipsis to prevent the Canvas from overflowing.
                expandedSum1 = TString::Format(
                    "e^{i(%.2f)(#pi/%.0f)%d}}|%d#GT + ... + e^{i(%.2f)(#pi/%.0f)%d}}|%d#GT", 
                    fLambda1, fDemTau, 0, 0, fLambda1, fDemTau, lim_t, lim_t);
            }
        expandedSum1 += " #right]_{C}";

    // Dynamic construction of the expanded summation for λ₂
        TString expandedSum2 = "#left[ #scale[1.5]{e}^{0}|0#GT + ";
            if (m <= 3) {
                // For m=1, 2, or 3, the limit is small (1, 3, or 7). We print everything.
                for (Int_t t = 1; t <= lim_t; t++) {
                    expandedSum2 += TString::Format(
                        "#scale[1.5]{e}^{i(%.2f)(#pi/%.0f)%d}|%d#GT", 
                        fLambda2, fDemTau, t, t
                    );
                    if (t < lim_t) expandedSum2 += " + "; // Add the '+' unless it is the last one
                }
            } else {
                // For m > 3, we use an ellipsis to prevent the Canvas from overflowing.
                expandedSum2 = TString::Format(
                    "e^{i(%.2f)(#pi/%.0f)%d}}|%d#GT + ... + e^{i(%.2f)(#pi/%.0f)%d}}|%d#GT", 
                    fLambda2, fDemTau, 0, 0, fLambda2, fDemTau, lim_t, lim_t);
            }
        expandedSum2 += " #right]_{C}";

    //? Rendering 4.1: Time Scale Factor τ
    if (microStep >= 1 && microStep < 5) {

        TString S41title = TString::Format(
            "#font[62]{#color[600]{4.1. Time Scale Factor #scale[1.5]{#tau}:}} " 
            "To avoid phase wrap-around (aliasing), the maximum phase must satisfy."
        );
        TLatex *lTitleS41 = new TLatex(0.02, 0.82, S41title.Data());
        lTitleS41->SetNDC();
        lTitleS41->SetTextFont(42);
        lTitleS41->SetTextSize(0.040);
        lTitleS41->SetTextColor(kGray+3);
        lTitleS41->Draw();

        TString eq41 = TString::Format(
            "#scale[1.3]{#lambda_{max}#tau < 2#pi}"
            "   #color[2]{#rightarrow}   "
            "#font[42]{#color[635]{Calculated #tau for user matrix:}}"
            "   #color[2]{#rightarrow}   "
        );
        TLatex *lEq41 = new TLatex(0.04, 0.72, eq41.Data()); 
        lEq41->SetNDC();
        lEq41->SetTextFont(132);     
        lEq41->SetTextSize(0.040);
        lEq41->SetTextColor(kBlack); 
        lEq41->Draw();

        TPaveText *pBox41 = new TPaveText(0.50, 0.80, 0.70, 0.70, "NDC");
        pBox41->SetFillColor(kYellow-9);
        pBox41->SetBorderSize(1);
        pBox41->SetTextAlign(12);
        pBox41->SetTextSize(0.045);
        pBox41->SetTextFont(132);
        pBox41->SetTextColor(kBlack); 
        TString tauCalc = TString::Format(
            "#tau = #frac{2#pi}{2^{m}}"
            "   #color[2]{#rightarrow}   "
            "#scale[1.3]{#tau = #frac{#pi}{%.0f}}",
            fDemTau
        );
        pBox41->AddText(tauCalc.Data());
        pBox41->Draw();
    }    

    //? Rendering step 4.2: Hamiltonian Evolution
    if (microStep >= 2 && microStep < 5) {

        TString S42title = TString::Format(
            "#font[62]{#color[600]{4.2. Hamiltonian Evolution:}} "
            "A system under Hamiltonian #font[62]{A} evolves through the unitary operator #hat{U} = e^{iA#tau}."
        );
        TLatex *lTitleS42 = new TLatex(0.02, 0.62, S42title.Data());
        lTitleS42->SetNDC();          
        lTitleS42->SetTextFont(42);   
        lTitleS42->SetTextSize(0.040);
        lTitleS42->SetTextColor(kGray+3);
        lTitleS42->Draw();

        TString eq42 = TString::Format(
            "#scale[1.5]{e^{iA#tau} |u_{j}#GT = e^{i#lambda_{j}#tau} |u_{j}#GT}"
            "     #color[2]{#rightarrow}   "
            "#font[42]{#color[635]{Fundamental property of diagonalizable matrix functions}}"
        );
        TLatex *lEq42 = new TLatex(0.04, 0.52, eq42.Data()); 
        lEq42->SetNDC();
        lEq42->SetTextFont(132);     
        lEq42->SetTextSize(0.040);
        lEq42->SetTextColor(kBlack); 
        lEq42->Draw();

    }

    //? Rendering 4.3: Clock-Index Connection
    if (microStep >= 3 && microStep < 5) {

        TString S43title = "#font[62]{#color[600]{4.3. Clock-Index Connection:}} The clock register controls the evolution of the index register.";
        TLatex *lTitleS43 = new TLatex(0.02, 0.42, S43title.Data());
        lTitleS43->SetNDC();
        lTitleS43->SetTextFont(42);
        lTitleS43->SetTextSize(0.040);
        lTitleS43->SetTextColor(kGray+3);
        lTitleS43->Draw();

        TString eq43 = TString::Format(
            "#font[42]{#color[635]{If clock register is in state |t#GT_{C} the operator applies}}"
            "   #color[2]{#rightarrow}     "
            "#scale[1.3]{#hat{U}^{t} |b#GT = e^{i#lambda_{j}#taut} |b#GT}"
        );
        TLatex *lEq43 = new TLatex(0.04, 0.32, eq43.Data()); 
        lEq43->SetNDC();
        lEq43->SetTextFont(132);     
        lEq43->SetTextSize(0.040);
        lEq43->SetTextColor(kBlack); 
        lEq43->Draw();  
    
    }

    //? Rendering 4.4: Evolved global state |Ψ₂⟩
    if (microStep >= 4 && microStep < 5) {

        TString S44title = "#font[62]{#color[600]{4.4. Evolved Global State |#Psi_{2}#GT:}}";
        TLatex *lTitleS44 = new TLatex(0.02, 0.22, S44title.Data());
        lTitleS44->SetNDC();
        lTitleS44->SetTextFont(42);
        lTitleS44->SetTextSize(0.040);
        lTitleS44->SetTextColor(kGray+3);
        lTitleS44->Draw();
        
        // Estado general |Ψ₂⟩
        TString eq45 = TString::Format(
            "|#Psi_{2}#GT = #frac{%s}{#sqrt{%.0f}} "
            "#frac{1}{#sqrt{%d}} #sum_{t=0}^{%d} #color[635]{#scale[1.5]{e}^{i(%.2f)(#pi/%.0f)t}}|t#GT_{C} "
            "#otimes  |u_{1}#GT_{I} #otimes |0#GT_{A}"
            "  %s  #frac{%s}{#sqrt{%.0f}} "
            "#frac{1}{#sqrt{%d}} #sum_{t=0}^{%d} #color[635]{#scale[1.5]{e}^{i(%.2f)(#pi/%.0f)t}}|t#GT_{C}"
            "#otimes  |u_{2}#GT_{I} #otimes |0#GT_{A}",
            b1Str.Data(), fIntDenomSq, ftotalStates, lim_t, fLambda1, fDemTau,          
            sign2.Data(), val2.Data(), fIntDenomSq, ftotalStates, lim_t, fLambda2, fDemTau
        );
        TLatex *lEq45 = new TLatex(0.04, 0.12, eq45.Data()); 
        lEq45->SetNDC();
        lEq45->SetTextFont(132);     
        lEq45->SetTextSize(0.050);
        lEq45->SetTextColor(kBlack); 
        lEq45->Draw(); 

    }

    //? Rendering 4.5: Development of the global state sum|Ψ₂⟩
    if (microStep >= 5) {

        TString S45title = "#font[62]{#color[600]{4.5. Development of the global state sum |#Psi_{2}#GT:}}";
        TLatex *lTitleS45 = new TLatex(0.02, 0.80, S45title.Data());
        lTitleS45->SetNDC();
        lTitleS45->SetTextFont(42);
        lTitleS45->SetTextSize(0.040);
        lTitleS45->SetTextColor(kGray+3);
        lTitleS45->Draw();

        TString eq45_line1 = TString::Format(
            "|#Psi_{2}#GT = #frac{%s}{#sqrt{%.0f}} #frac{1}{#sqrt{%d}} "
            "#color[834]{%s} #otimes |u_{1}#GT_{I} #otimes |0#GT_{A}",
            b1Str.Data(), fIntDenomSq, ftotalStates, expandedSum1.Data()
        );

        TLatex *lEq45_1 = new TLatex(0.04, 0.70, eq45_line1.Data()); 
        lEq45_1->SetNDC();
        lEq45_1->SetTextFont(132);
        if (m > 2) { 
            lEq45_1->SetTextSize(0.035);
        } else {
            lEq45_1->SetTextSize(0.050);
        }     
        lEq45_1->SetTextColor(kBlack); 
        lEq45_1->Draw();

        TString eq45_line2 = TString::Format(
            "%s #frac{%s}{#sqrt{%.0f}} #frac{1}{#sqrt{%d}} "
            "#color[804]{%s} #otimes |u_{2}#GT_{I} #otimes |0#GT_{A}",
            sign2.Data(), val2.Data(), fIntDenomSq, ftotalStates, expandedSum2.Data()
        );

        TLatex *lEq45_2 = new TLatex(0.08, 0.60, eq45_line2.Data());
        lEq45_2->SetNDC();
        lEq45_2->SetTextFont(132);     
        if (m > 2) { 
            lEq45_2->SetTextSize(0.035);
        } else {
            lEq45_2->SetTextSize(0.050);
        }   
        lEq45_2->SetTextColor(kBlack); 
        lEq45_2->Draw();

    }

    //? Rendering 4.6: Global Resulting State |Ψ₂⟩
    if (microStep >= 6) {

        Int_t totalStates = (Int_t)TMath::Power(2, fClockQubitsM);

        TString S46title = "#font[62]{#color[600]{4.6. Global Resulting State |#Psi_{2}#GT:}}";
        TLatex *lTitleS46 = new TLatex(0.02, 0.40, S46title.Data());
        lTitleS46->SetNDC();
        lTitleS46->SetTextFont(42);
        lTitleS46->SetTextSize(0.040);
        lTitleS46->SetTextColor(kGray+3);
        lTitleS46->Draw();
        
        // --- Branch 1 (For lambda_1) ---
        TString ecuacionR1 = TString::Format(
            "#color[1]{|#Psi_{2}#GT = #frac{%s}{#sqrt{%.0f}} #frac{1}{#sqrt{%d}}} #left[ ", 
            b1Str.Data(), fIntDenomSq, ftotalStates
        );
        for (Int_t t = 0; t < totalStates; t++) {
            TString fase = fPhaseStrings[0][t]; 
            
            // If it is not the first term and the phase is not negative, we add a "+" separator.
            if (t > 0 && !fase.BeginsWith("-")) ecuacionR1 += " + ";
            else if (t > 0 && fase.BeginsWith("-")) ecuacionR1 += " "; // The negative sign is already included in the string
            
            ecuacionR1 += TString::Format("%s|%d#GT", fase.Data(), t);
        }
        ecuacionR1 += " #right]_{C} #color[1]{#otimes |u_{1}#GT_{I} #otimes |0#GT_{A}}";
        
        TLatex *lEqR1 = new TLatex(0.02, 0.30, ecuacionR1.Data());
        lEqR1->SetNDC();
        lEqR1->SetTextFont(132);
        if (m > 2) { 
            lEqR1->SetTextSize(0.035);
        } else {
            lEqR1->SetTextSize(0.050);
        }  
        lEqR1->SetTextColor(kTeal-6); 
        lEqR1->Draw();

        // --- Branch 2 (For lambda_2) ---
        TString ecuacionR2 = TString::Format(
            "#color[1]{%s #frac{%s}{#sqrt{%.0f}} #frac{1}{#sqrt{%d}}} #left[ ", 
            sign2.Data(), val2.Data(), fIntDenomSq, ftotalStates
        );
        for (Int_t t = 0; t < totalStates; t++) {
            TString fase = fPhaseStrings[1][t]; 
            
            if (t > 0 && !fase.BeginsWith("-")) ecuacionR2 += " + ";
            else if (t > 0 && fase.BeginsWith("-")) ecuacionR2 += " ";
            
            ecuacionR2 += TString::Format("%s|%d#GT", fase.Data(), t);
        }
        ecuacionR2 += " #right]_{C} #color[1]{#otimes |u_{2}#GT_{I} #otimes |0#GT_{A}}";
        
        TLatex *lEqR2 = new TLatex(0.06, 0.20, ecuacionR2.Data());
        lEqR2->SetNDC();
        lEqR2->SetTextFont(132);
        if (m > 2) { 
            lEqR2->SetTextSize(0.035);
        } else {
            lEqR2->SetTextSize(0.050);
        }
        lEqR2->SetTextColor(kOrange+4);    
        lEqR2->Draw();

    }

}

void QHHLA_SoftEdu::DrawMatrix_Step4(Int_t microStep){

    Int_t totalStates = TMath::Power(2, fClockQubitsM);

    //? Rendering step 4.7: Unitary Operator Matrix U in the Eigenvector Basis
    if (microStep >= 7) {

        TString S47title = TString::Format(
            "#font[62]{#color[600]{4.7. Unitary Operator Matrix (U)}} "
            "In the eigenbasis, the Hamiltonian evolution matrix #hat{U} = e^{iA#tau} is strictly diagonal."
        );
        TLatex *lTitleS47 = new TLatex(0.02, 0.82, S47title.Data());
        lTitleS47->SetNDC();          
        lTitleS47->SetTextFont(42);   
        lTitleS47->SetTextSize(0.040);
        lTitleS47->SetTextColor(kGray+3);
        lTitleS47->Draw();

        // Matrix representation using #splitline for vertical alignment
        TString eq47 = TString::Format(
            "#hat{U} = #left[ #splitline{#color[834]{#scale[1.5]{e}^{i(%.2f)#tau}}}{    0  }   #splitline{    0  }{#color[804]{#scale[1.5]{e}^{i(%.2f)#tau}}} #right]"
            "  #color[2]{#rightarrow} "
            "#scale[0.7]{#font[42]{#color[635]{Each diagonal entry represents the phase evolution of one eigenvalue branch.}}}",
            fLambda1, fLambda2
        );
        TLatex *lEqS47 = new TLatex(0.02, 0.72, eq47.Data());
        lEqS47->SetNDC();
        lEqS47->SetTextFont(132);
        lEqS47->SetTextSize(0.060);
        lEqS47->SetTextColor(kBlack);
        lEqS47->Draw();

    }

    //? Rendering step 4.8: Vectores Columna |c₁⟩ y |c₂⟩ 
    if (microStep >= 8) {

        TString S48title = "#font[62]{#color[600]{4.8. Clock Register State Vectors:}}";
        TLatex *lTitleS48 = new TLatex(0.02, 0.60, S48title.Data());
        lTitleS48->SetNDC();          
        lTitleS48->SetTextFont(42);   
        lTitleS48->SetTextSize(0.040);
        lTitleS48->SetTextColor(kGray+3);
        lTitleS48->Draw();

        /*  Auxiliary function to construct a column vector
            Defines the function that receives the eigenvector index (eigenIndex) and 
            returns a TString object. The [&] indicates that it can access variables from the 
            enclosing scope. */ 
        auto BuildColumnVector = [&](Int_t eigenIndex) -> TString {
            std::vector<TString> rows;
            Bool_t skipping = kFALSE;
            
            for (Int_t t = 0; t < totalStates; t++) {
                if (fClockQubitsM > 3 && t == 3 && !skipping) {
                    rows.push_back(":");
                    skipping = kTRUE; // Logical flag to control whether to skip rows
                    t = totalStates - 2;
                    continue;
                }
                
                TString fase = fPhaseStrings[eigenIndex][t];
                fase = fase.Strip(TString::kBoth);
                
                if (fase == "") fase = "  1 ";
                else if (fase == "-") fase = " -1 ";
                else if (fase == "i") fase = "  i ";
                else if (fase == "-i") fase = " -i ";
                else if (fase == "#left(1/#sqrt{2} + i/#sqrt{2}#right)") fase = "1/#sqrt{2} + i/#sqrt{2}";
                else if (fase == "#left(-1/#sqrt{2} + i/#sqrt{2}#right)") fase = "-1/#sqrt{2} + i/#sqrt{2}";
                else if (fase == "#left(-1/#sqrt{2} - i/#sqrt{2}#right)") fase = "-1/#sqrt{2} - i/#sqrt{2}";
                else if (fase == "#left(1/#sqrt{2} - i/#sqrt{2}#right)") fase = "1/#sqrt{2} - i/#sqrt{2}";

                rows.push_back(fase);
            }
            
            /*  Iterative construction of the #splitline
                Toma la fila actual (rows[i]) y la coloca arriba del content que ya tenía.
                Ejemplo visual: #splitline{Fila2}{#splitline{Fila1}{Fila0}} 
                Construcción invertida: de abajo hacia arriba para que t=0 quede arriba. */
            TString content = "";
            for (Int_t i = (Int_t)rows.size() - 1; i >= 0; i--) {
                if (i == (Int_t)rows.size() - 1) {
                    content = rows[i];
                } else {
                    content = TString::Format("#splitline{%s}{%s}", rows[i].Data(), content.Data());
                }
            }
            
            return TString::Format("#left[%s#right]", content.Data());
        };

        // Construct both vectors.
        TString v1_eval = BuildColumnVector(0);
        TString v2_eval = BuildColumnVector(1);

        Double_t Y_center = 0.35;

        // ------------------- LEFT BRANCH: State |c₁⟩ -------------------
        TLatex *lLabel1 = new TLatex(0.10, Y_center, "#color[834]{|#phi_{1}#GT}");
        lLabel1->SetNDC();
        lLabel1->SetTextFont(132);
        lLabel1->SetTextSize(0.070);
        lLabel1->SetTextAlign(22);
        lLabel1->Draw();

        TString eq48a = TString::Format(
                " =  #frac{1}{#sqrt{%d}}", ftotalStates
            );
        TLatex *lEqual1 = new TLatex(0.16, Y_center, eq48a);
        lEqual1->SetNDC();
        lEqual1->SetTextFont(132);
        lEqual1->SetTextSize(0.060);
        lEqual1->SetTextAlign(22);
        lEqual1->Draw();

        TLatex *lVector1 = new TLatex(0.24, Y_center, v1_eval.Data());
        lVector1->SetNDC();
        lVector1->SetTextAlign(22);
        lVector1->SetTextFont(132);
        lVector1->SetTextColor(kTeal-6);
        if (fClockQubitsM > 2) { 
                lVector1->SetTextSize(0.060);
                lVector1->SetX(0.30);
            } else {
                lVector1->SetTextSize(0.070);
            } 
        lVector1->Draw();

        // ------------------- RIGHT BRANCH: State |c₂⟩ -------------------
        TLatex *lLabel2 = new TLatex(0.50, Y_center, "#color[804]{|#phi_{2}#GT}");
        lLabel2->SetNDC();
        lLabel2->SetTextFont(132);
        lLabel2->SetTextSize(0.070);
        lLabel2->SetTextAlign(22);
        lLabel2->Draw();

        TString eq48b = TString::Format(
                " =  #frac{1}{#sqrt{%d}}", ftotalStates
            );
        TLatex *lEqual2 = new TLatex(0.56, Y_center, eq48b);
        lEqual2->SetNDC();
        lEqual2->SetTextFont(132);
        lEqual2->SetTextSize(0.060);
        lEqual2->SetTextAlign(22);
        lEqual2->Draw();

        TLatex *lVector2 = new TLatex(0.64, Y_center, v2_eval.Data());
        lVector2->SetNDC();
        lVector2->SetTextAlign(22);
        lVector2->SetTextFont(132);
        lVector2->SetTextColor(kOrange+4);
        if (fClockQubitsM > 2) { 
                lVector2->SetTextSize(0.060);
                lVector2->SetX(0.70);
            } else {
                lVector2->SetTextSize(0.070);
            } 
        lVector2->Draw();
    }

}

void QHHLA_SoftEdu::DrawCircuit_Step4(Int_t microStep){

    // Position parameters
    Double_t xStart = 0.05;        // Start of the lines
    Double_t xEnd = 0.95;          // End of the lines
    Double_t yIndex = 0.75;        // Position Y of the Index record (top)
    Double_t yAncilla = 0.20;      // Y position of the Ancilla qubit (lower)
    Double_t yClockStart = 0.65;   // Clock bus start
    Double_t yClockSpacing = 0.10; // Space between clock qubits

    // Gate dimensions (Hadamard)
    Double_t hGateX1 = 0.07;
    Double_t hGateX2 = 0.11;
    Double_t hGateHalfHeight = 0.04;
    
    // Gate dimensions (Controlled-U)
    Double_t uGateWidth = 0.10;
    Double_t uGateHeight = 0.08;
    Double_t uGateXStart = 0.13;   // Starting X position for U gates
    Double_t uGateSpacing = 0.12;  // Spacing between U gates
    
    //? Rendering step 4.9: Circuit Diagram step 4
    if (microStep >= 9) {

        // TOP LINE: Memory/Index Register
        TLine *lineIndex = new TLine(xStart, yIndex, xEnd, yIndex);
        lineIndex->SetLineWidth(2);
        lineIndex->SetLineColor(kBlue+3);
        lineIndex->Draw();
        
        // Initial state |0⟩ for index record
        TLatex *stateIndex = new TLatex(xStart - 0.035, yIndex-0.015, "|b#GT_{I}");
        stateIndex->SetNDC();
        stateIndex->SetTextFont(62);
        stateIndex->SetTextSize(0.05);
        stateIndex->SetTextColor(kBlue+3);
        stateIndex->Draw();
        
        // CENTRAL LINES: Clock Register m-qubit bus
        for (Int_t i = 0; i < fClockQubitsM; i++) {
            Double_t yClock = yClockStart - (i * yClockSpacing);
            
            TLine *lineClock = new TLine(xStart, yClock, xEnd, yClock);
            lineClock->SetLineWidth(2);
            lineClock->SetLineColor(kGreen+3);
            lineClock->Draw();
            
            // Initial state |0⟩ for each qubit of the clock
            TLatex *stateClock = new TLatex(xStart - 0.035, yClock - 0.015, "|0#GT_{C}");
            stateClock->SetNDC();
            stateClock->SetTextFont(62);
            stateClock->SetTextSize(0.05);
            stateClock->SetTextColor(kGreen+3);
            stateClock->Draw();

            if (microStep >= 10) {
                // Background box for the gate
                TBox *hBox = new TBox(hGateX1, yClock - hGateHalfHeight, hGateX2, yClock + hGateHalfHeight);
                hBox->SetFillColor(kCyan-10);
                hBox->SetLineColor(kCyan+4);
                hBox->SetLineWidth(1.5);
                hBox->Draw("l");
                
                // Letter 'H' inside the box
                TLatex *hText = new TLatex((hGateX1 + hGateX2)/2.0, yClock, "H");
                hText->SetTextAlign(22);
                hText->SetTextFont(62);
                hText->SetTextSize(0.06);
                hText->SetTextColor(kCyan+4);
                hText->Draw();
            }
            
        }
        
        // BOTTOM LINE: Qubit Ancilla
        TLine *lineAncilla = new TLine(xStart, yAncilla, xEnd, yAncilla);
        lineAncilla->SetLineWidth(2);
        lineAncilla->SetLineColor(kCyan+3);
        lineAncilla->Draw();
        
        // Initial state |0⟩ for the ancilla
        TLatex *stateAncilla = new TLatex(xStart - 0.035, yAncilla - 0.015, "|0#GT_{A}");
        stateAncilla->SetNDC();
        stateAncilla->SetTextFont(62);
        stateAncilla->SetTextSize(0.05);
        stateAncilla->SetTextColor(kCyan+3);
        stateAncilla->Draw();
        
        //? Rendering step 4.11: Controlled-U operations
        if (microStep >= 11) {

            // Draw controlled-U gates for each clock qubit
            for (Int_t i = 0; i < fClockQubitsM; i++) {
                Double_t yClock = yClockStart - (i * yClockSpacing);
                Double_t uGateX = uGateXStart + (i * uGateSpacing);
                
                // Calculate the power: 2^i
                Int_t power = TMath::Power(2, i);
                
                // Draw control dot on clock qubit line
                TMarker *controlDot = new TMarker(uGateX + uGateWidth/2.0, yClock, 20);
                controlDot->SetMarkerSize(1.5);
                controlDot->SetMarkerColor(kBlue+4);
                controlDot->SetMarkerStyle(20);
                controlDot->Draw();
                
                // Draw vertical line from control to U gate
                TLine *controlLine = new TLine(uGateX + uGateWidth/2.0, yClock, 
                    uGateX + uGateWidth/2.0, yIndex);
                controlLine->SetLineWidth(1);
                controlLine->SetLineColor(kBlue+4);
                controlLine->Draw();
                
                // Draw U gate box on index register line
                TBox *uBox = new TBox(uGateX, yIndex - uGateHeight/2.0, 
                    uGateX + uGateWidth, yIndex + uGateHeight/2.0);
                uBox->SetFillColor(kBlue-10);
                uBox->SetLineColor(kBlue+4);
                uBox->SetLineWidth(1.5);
                uBox->Draw("l");
                
                // Label U gate with power notation
                TString uLabel;
                if (i == 0) {
                    uLabel = "U^{2^{0}}=e^{iA#tau(1)}";
                } else if (i == 1) {
                    uLabel = "U^{2^{1}}=e^{iA#tau(2)}";
                } else {
                    uLabel = TString::Format("U^{2^{%d}}=e^{iA#tau(%d)}", i, power);
                }
                
                TLatex *uText = new TLatex(uGateX + uGateWidth/2.0, yIndex, uLabel);
                uText->SetTextAlign(22);
                uText->SetTextFont(42);
                uText->SetTextSize(0.05);
                uText->SetTextColor(kBlue+4);
                uText->Draw();
    
            }
            
        }

    }

}

void QHHLA_SoftEdu::DrawGraph_Step4(Int_t microStep){

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    if (!c) return;
    c->cd();
    c->Clear();

    //? TITLE AND PROGRESS BAR (Main Canvas) ----------------------------------
    DrawStepTitle(c);
    DrawProgressBar(c);

    //? Calculation of time t based on m and microstep. -----------------------
    Int_t totalStates = (Int_t)TMath::Power(2, fClockQubitsM);
    Double_t t = 0.0; // continuous time for animation

    //? Rendering step 4.12: static base, without phasors
    if (microStep <= 12) {
        t = 0.0; 
    } else {
        // Steps 13-20: 8 animation positions (animIdx = 0..7)
        Int_t animIdx = microStep - 13;

        if (fClockQubitsM == 1) {
            // m=1: steps 0.25 → t = 0, 0.25, 0.5, ..., 1.75
            t = 0.25 * animIdx;
        } else if (fClockQubitsM == 2) {
            // m=2: steps 0.5 → t = 0, 0.5, 1.0, ..., 3.5
            t = 0.5 * animIdx;
        } else if (fClockQubitsM == 3) {
            // m=3: steps de 1.0 → t = 0, 1, 2, ..., 7
            t = 1.0 * animIdx;
        } else {
            // m>3: uniform distribution between 0 and totalStates-1
            t = (Double_t)(totalStates - 1) * animIdx / 7.0;
        }
    }

    //? Rendering step 4.12: Complex Plane (Unit Circle)
    if (microStep >= 12) {

        // LEFT PAD: Complex Plane (Unit Circle)
        TPad *padLeft = new TPad("padLeftStep4", "Complex Plane", 0.00, 0.18, 0.50, 0.88);
        padLeft->SetLeftMargin(0.10);
        padLeft->SetRightMargin(0.15);
        padLeft->SetTopMargin(0.0);
        padLeft->SetBottomMargin(0.05);
        padLeft->Draw();
        padLeft->cd();
        padLeft->SetGrid(0, 0);
        padLeft->SetTicks(1, 1);

        Double_t lim = 1.20;
        Double_t radio = 1.0;
        TH1F *frameL = padLeft->DrawFrame(-lim, -lim, lim, lim);
        frameL->SetStats(0);

        // Unit circle
        TEllipse *unitCircle = new TEllipse(0, 0, radio, radio);
        unitCircle->SetFillStyle(0);
        unitCircle->SetLineColor(kGray+2);
        unitCircle->SetLineStyle(2);
        unitCircle->SetLineWidth(2);
        unitCircle->Draw();

        // Cartesian axes
        TLine *axX = new TLine(-lim, 0, lim, 0);
        axX->SetLineColor(kBlack); 
        axX->SetLineWidth(1); 
        axX->Draw();
        TLine *axY = new TLine(0, -lim, 0, lim);
        axY->SetLineColor(kBlack); 
        axY->SetLineWidth(1); 
        axY->Draw();

        TLatex *lRe = new TLatex(lim*0.88, -0.14, "Re");
        lRe->SetTextSize(0.05); 
        lRe->Draw();
        TLatex *lIm = new TLatex(-0.16, lim*0.88, "Im");
        lIm->SetTextSize(0.05); 
        lIm->Draw();

        // Cardinal marks
        TMarker *mTop = new TMarker(0,  1, 20); mTop->SetMarkerSize(0.5); mTop->Draw();
        TMarker *mBot = new TMarker(0, -1, 20); mBot->SetMarkerSize(0.5); mBot->Draw();
        TMarker *mRig = new TMarker( 1, 0, 20); mRig->SetMarkerSize(0.5); mRig->Draw();
        TMarker *mLef = new TMarker(-1, 0, 20); mLef->SetMarkerSize(0.5); mLef->Draw();

        // Origin
        TMarker *origin = new TMarker(0, 0, 20);
        origin->SetMarkerSize(0.8); 
        origin->SetMarkerColor(kBlack); 
        origin->Draw();

    }

    //? Rendering step 4.13: phasor animation
    if (microStep >= 13) {

        Double_t theta1 = fLambda1 * fTimeScale * t;
        Double_t theta2 = fLambda2 * fTimeScale * t;
        Double_t x1 = TMath::Cos(theta1), y1 = TMath::Sin(theta1);
        Double_t x2 = TMath::Cos(theta2), y2 = TMath::Sin(theta2);

        // Angle arcs
        if (TMath::Abs(theta1) > 0.02) {
            Double_t a1 = theta1 * 180.0 / TMath::Pi();
            TArc *arc1 = new TArc(0, 0, 0.18, 0, a1);
            arc1->SetLineColor(kTeal-6); 
            arc1->SetLineWidth(2); 
            arc1->SetFillStyle(0); 
            arc1->Draw();
        }
        if (TMath::Abs(theta2) > 0.02) {
            Double_t a2 = theta2 * 180.0 / TMath::Pi();
            TArc *arc2 = new TArc(0, 0, 0.32, 0, a2);
            arc2->SetLineColor(kOrange+4); 
            arc2->SetLineWidth(2); 
            arc2->SetFillStyle(0); 
            arc2->Draw();
        }

        // Arrows representing phasors
        TArrow *phasor1 = new TArrow(0, 0, x1, y1, 0.012, "|>");
        phasor1->SetLineColor(kTeal-6); 
        phasor1->SetFillColor(kTeal-6); 
        phasor1->SetLineWidth(4);
        phasor1->Draw();

        TArrow *phasor2 = new TArrow(0, 0, x2, y2, 0.01, "|>");
        phasor2->SetLineColor(kOrange+4); 
        phasor2->SetFillColor(kOrange+4); 
        phasor2->SetLineWidth(3);
        phasor2->Draw();

        // Labels for the phasors
        TLatex *leg1 = new TLatex(x1*1.1, y1*1.1, "#color[834]{#lambda_{1}}");
        leg1->SetTextSize(0.07); 
        leg1->Draw();
        TLatex *leg2 = new TLatex(x2*1.1, y2*1.1, "#color[804]{#lambda_{2}}");
        leg2->SetTextSize(0.07); 
        leg2->Draw();

        // Defined ends of the phasors
        TMarker *tip1 = new TMarker(x1, y1, 20);
        tip1->SetMarkerSize(0.6); 
        tip1->SetMarkerColor(kTeal-6); 
        tip1->Draw();
        TMarker *tip2 = new TMarker(x2, y2, 20);
        tip2->SetMarkerSize(0.6); 
        tip2->SetMarkerColor(kOrange+4); 
        tip2->Draw();

    }

    if (microStep >= 12) {

        // RIGHT PAD: 
        c->cd();
        TPad *padRight = new TPad("padRightStep4", "Fasor Info", 0.50, 0.18, 0.99, 0.88);
        padRight->SetLeftMargin(0.05);
        padRight->SetRightMargin(0.05);
        padRight->SetTopMargin(0.0);
        padRight->SetBottomMargin(0.05);
        padRight->Draw();
        padRight->cd();
        padRight->SetGrid(0, 0);

        // Invisible frame to define the area
        TH1F *frameR = padRight->DrawFrame(0, 0, 1, 1);
        frameR->SetStats(0);
        frameR->GetXaxis()->SetLabelSize(0); 
        frameR->GetYaxis()->SetLabelSize(0);
        frameR->GetXaxis()->SetTickLength(0); 
        frameR->GetYaxis()->SetTickLength(0);
        frameR->SetTitle("");

        // Panel title
        TLatex *titleR = new TLatex(0.5, 0.94, "#font[62]{#color[600]{Fasor Equations}}");
        titleR->SetNDC(); 
        titleR->SetTextAlign(22); 
        titleR->SetTextSize(0.06); 
        titleR->Draw();

        // Decorative dividing line
        TLine *sepTop = new TLine(0.05, 0.89, 0.95, 0.89);
        sepTop->SetLineColor(kGray+1); 
        sepTop->SetLineWidth(1); 
        sepTop->Draw();
        
        //? Equations and Information 
        if (microStep == 12) {
        
            // General system information
            TLatex *lGen = new TLatex(0.10, 0.80, "#font[62]{General Formula:}");
            lGen->SetNDC(); 
            lGen->SetTextAlign(12);
            lGen->SetTextColor(kRed+3); 
            lGen->SetTextSize(0.055); 
            lGen->Draw();

            TLatex *lForm = new TLatex(0.45, 0.80,
                "e^{i#lambda#tau t} = cos(#lambda#tau t) + i sin(#lambda#tau t)");
            lForm->SetNDC(); 
            lForm->SetTextAlign(12);
            lForm->SetTextFont(132); 
            lForm->SetTextSize(0.060); 
            lForm->Draw();

            // Separator line
            TLine *sepMid = new TLine(0.05, 0.71, 0.95, 0.71);
            sepMid->SetLineColor(kGray+1); 
            sepMid->SetLineWidth(1); 
            sepMid->Draw();

            TLatex *lParams = new TLatex(0.50, 0.65, "#font[62]{System Parameters:}");
            lParams->SetNDC(); 
            lParams->SetTextAlign(22); 
            lParams->SetTextColor(kRed+3); 
            lParams->SetTextSize(0.055); 
            lParams->Draw();

            TLatex *lTau = new TLatex(0.50, 0.55, TString::Format("#tau = #frac{#pi}{%.0f} = %.2f", fDemTau, fTimeScale));
            lTau->SetNDC(); 
            lTau->SetTextAlign(22); 
            lTau->SetTextSize(0.06);
            lTau->SetTextFont(132);  
            lTau->Draw();

            TLatex *lL1 = new TLatex(0.50, 0.45,
                TString::Format(
                    "#color[834]{#lambda_{1} = %.2f}  "
                    "#color[632]{#rightarrow}  #omega_{1} = #lambda_{1}#tau = %.6f",
                    fLambda1, fLambda1 * fTimeScale));
            lL1->SetNDC(); 
            lL1->SetTextAlign(22); 
            lL1->SetTextFont(132); 
            lL1->SetTextSize(0.06); 
            lL1->Draw();

            TLatex *lL2 = new TLatex(0.50, 0.34,
                TString::Format(
                    "#color[804]{#lambda_{2} = %.2f} "  
                    "#color[632]{#rightarrow}  #omega_{2} = #lambda_{2}#tau = %.6f",
                    fLambda2, fLambda2 * fTimeScale));
            lL2->SetNDC(); 
            lL2->SetTextAlign(22); 
            lL2->SetTextFont(132); 
            lL2->SetTextSize(0.06); 
            lL2->Draw();

            TLatex *lM = new TLatex(0.50, 0.24,
                TString::Format(
                    "Clock qubits: m = %d  (#color[632]{#rightarrow}  %d states)", 
                    fClockQubitsM, totalStates));
            lM->SetNDC(); 
            lM->SetTextAlign(22); 
            lM->SetTextSize(0.055); 
            lM->Draw();

            // Separator line
            TLine *sepBot= new TLine(0.05, 0.11, 0.95, 0.11);
            sepBot->SetLineColor(kGray+1); 
            sepBot->SetLineWidth(1); 
            sepBot->Draw();

            TLatex *lHint = new TLatex(0.50, 0.09, "#font[62]{#color[2]{Press NEXT to animate phasors}}");
            lHint->SetNDC(); 
            lHint->SetTextAlign(22); 
            lHint->SetTextSize(0.050); 
            lHint->Draw();

        }

        //? Dynamic equations with substituted values
        if (microStep >= 13) {
            
            Double_t theta1 = fLambda1 * fTimeScale * t;
            Double_t theta2 = fLambda2 * fTimeScale * t;

            // Retrieve phase strings from CoreMath (we use an integer t for indexing)
            Int_t tInt = (Int_t)TMath::Nint(t); // Rounding to the nearest integer
            TString phase1Str = (tInt < (Int_t)fPhaseStrings[0].size()) ? fPhaseStrings[0][tInt] : "";
            TString phase2Str = (tInt < (Int_t)fPhaseStrings[1].size()) ? fPhaseStrings[1][tInt] : "";
            if (phase1Str == "") phase1Str = "1"; else if (phase1Str == "-") phase1Str = "-1";
            if (phase2Str == "") phase2Str = "1"; else if (phase2Str == "-") phase2Str = "-1";

            // --- Time indicator ---
            TLatex *lTime = new TLatex(0.50, 0.80,
                TString::Format("#font[62]{Time Step:}  t = %.2f", t));
            lTime->SetNDC(); 
            lTime->SetTextAlign(22);
            lTime->SetTextColor(kRed+3); 
            lTime->SetTextSize(0.055); 
            lTime->Draw();

            // Separator line
            TLine *sepMid = new TLine(0.05, 0.71, 0.95, 0.71);
            sepMid->SetLineColor(kGray+1); 
            sepMid->SetLineWidth(1); 
            sepMid->Draw();

            // --- Fasor λ₁ ---
            TLatex *lF1Title = new TLatex(0.50, 0.60, "#font[62]{#color[834]{Fasor #lambda_{1}:}}");
            lF1Title->SetNDC(); 
            lF1Title->SetTextAlign(22);
            lF1Title->SetTextFont(132); 
            lF1Title->SetTextSize(0.060); 
            lF1Title->Draw();

            const char* signIm1 = (TMath::Sin(theta1) < 0) ? "-" : "+";
            Double_t absSin1 = TMath::Abs(TMath::Sin(theta1));

            TLatex *lF1Eq = new TLatex(0.50, 0.50,
                TString::Format(
                    "e^{i(%.2f)(%.2f)(%.2f)} = e^{i%.2f} = %.2f %s i %.2f",
                    fLambda1, fTimeScale, t, theta1,
                    TMath::Cos(theta1),
                    signIm1, absSin1
                ));
            lF1Eq->SetNDC(); 
            lF1Eq->SetTextAlign(22);
            lF1Eq->SetTextFont(132); 
            lF1Eq->SetTextSize(0.060); 
            lF1Eq->Draw();

            // --- Fasor λ₂ ---
            TLatex *lF2Title = new TLatex(0.50, 0.40, "#font[62]{#color[804]{Fasor #lambda_{2}:}}");
            lF2Title->SetNDC(); 
            lF2Title->SetTextAlign(22);
            lF2Title->SetTextFont(132); 
            lF2Title->SetTextSize(0.060); 
            lF2Title->Draw();

            const char* signIm2 = (TMath::Sin(theta2) < 0) ? "-" : "+";
            Double_t absSin2 = TMath::Abs(TMath::Sin(theta2));

            TLatex *lF2Eq = new TLatex(0.50, 0.30,
                TString::Format(
                    "e^{i(%.2f)(%.2f)(%.2f)} = e^{i%.2f} "
                    "= %.2f %s i %.2f",
                    fLambda2, fTimeScale, t, theta2,
                    TMath::Cos(theta2),
                    signIm2, absSin2
                ));
            lF2Eq->SetNDC(); 
            lF2Eq->SetTextAlign(22);
            lF2Eq->SetTextFont(132); 
            lF2Eq->SetTextSize(0.060); 
            lF2Eq->Draw();

            // Separator line bottom
            TLine *sepBot= new TLine(0.05, 0.11, 0.95, 0.11);
            sepBot->SetLineColor(kGray+1); 
            sepBot->SetLineWidth(1); 
            sepBot->Draw();

            TString noteText;
            if (TMath::Abs(fLambda1) > TMath::Abs(fLambda2)) {
                noteText = "#font[62]{#color[2]{Note:}} #lambda_{1} rotates faster than #lambda_{2}";
            } else if (TMath::Abs(fLambda2) > TMath::Abs(fLambda1)) {
                noteText = "#font[62]{#color[2]{Note:}} #lambda_{2} rotates faster than #lambda_{1}";
            } else {
                noteText = "#font[62]{#color[2]{Note:}} Both eigenvalues rotate at the same speed";
            }
            TLatex *lNote = new TLatex(0.50, 0.09, noteText);
            lNote->SetNDC(); 
            lNote->SetTextAlign(22); 
            lNote->SetTextSize(0.055); 
            lNote->Draw();

        }

    }  

    //? VISUAL SLIDER (Main canvas, aligned below padLeft)
    c->cd();

    Double_t sliderY = 0.065;
    Double_t sliderX1 = 0.04;   
    Double_t sliderX2 = 0.44;   

    // Slider rail
    TBox *sliderTrack = new TBox(sliderX1, sliderY - 0.005, sliderX2, sliderY + 0.005);
    sliderTrack->SetFillColor(kGray+1);
    sliderTrack->SetLineColor(kGray+2);
    sliderTrack->Draw();

    // Ticks: 8 posiciones fijas (0..7) alineadas con los pasos de animación
    Int_t nTicks = 8;
    Double_t tTickValues[8];
    
    if (fClockQubitsM == 1) {
        // m=1: 0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75
        for (Int_t i = 0; i < 8; i++) tTickValues[i] = 0.25 * i;
    } else if (fClockQubitsM == 2) {
        // m=2: 0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5
        for (Int_t i = 0; i < 8; i++) tTickValues[i] = 0.5 * i;
    } else {
        // m>=3: 0, 1, 2, 3, 4, 5, 6, 7
        for (Int_t i = 0; i < 8; i++) tTickValues[i] = (Double_t)i;
    }

    // Dibujar ticks y etiquetas
    for (Int_t i = 0; i < nTicks; i++) {

        Double_t fracTick = (Double_t)i / 7.0; // 0/7, 1/7, ..., 7/7
        Double_t xpos = sliderX1 + fracTick * (sliderX2 - sliderX1);

        // Vertical tick line
        TLine *tick = new TLine(xpos, sliderY - 0.015, xpos, sliderY + 0.015);
        tick->SetLineColor(kBlack); 
        tick->SetLineWidth(1); 
        tick->Draw();

        // Numeric label
        TString tickLabel;
        if (fClockQubitsM == 1) {
            if (i % 2 == 0) tickLabel = TString::Format("%.2f", tTickValues[i]);
            else            tickLabel = TString::Format("%.2f", tTickValues[i]);
        } else if (fClockQubitsM == 2) {
            tickLabel = TString::Format("%.1f", tTickValues[i]);
        } else {
            tickLabel = TString::Format("%.0f", tTickValues[i]);
        }
        
        TLatex *ltick = new TLatex(xpos, sliderY - 0.032, tickLabel);
        ltick->SetNDC(); 
        ltick->SetTextAlign(22); 
        ltick->SetTextSize(0.022); 
        ltick->Draw();

    }

    // Knob position based on microStep
    Double_t knobFrac = 0.0;
    if (microStep >= 13) {
        knobFrac = (Double_t)(microStep - 13) / 7.0; // 0/7, 1/7, ..., 7/7
        if (knobFrac > 1.0) knobFrac = 1.0;
    }
    
    Double_t knobX = sliderX1 + knobFrac * (sliderX2 - sliderX1);

    Color_t knobColor = (microStep >= 13) ? kBlue : kGray + 2;

    // Knob centered exactly on the tick mark.
    Double_t knobHalfWidth = 0.008;  
    Double_t knobHalfHeight = 0.018; 
    
    TBox *knob = new TBox(knobX - knobHalfWidth, sliderY - knobHalfHeight, 
        knobX + knobHalfWidth, sliderY + knobHalfHeight);
    knob->SetFillColor(knobColor);
    knob->SetLineColor(knobColor + 2);
    knob->SetLineWidth(2);
    knob->Draw();

    // Caption slider
    TString sliderCaption;
    if (microStep <= 12) {
        sliderCaption = "#font[62]{Clock Time}  t = 0.00  (animation starts at NEXT)";
    } else {
        if (fClockQubitsM == 1) {
            sliderCaption = TString::Format("#font[62]{Clock Time}  t = %.2f", t);
        } else if (fClockQubitsM == 2) {
            sliderCaption = TString::Format("#font[62]{Clock Time}  t = %.1f", t);
        } else {
            sliderCaption = TString::Format("#font[62]{Clock Time}  t = %.0f", t);
        }
    }
    TLatex *lSlider = new TLatex((sliderX1 + sliderX2)/2.0, sliderY + 0.042, sliderCaption.Data());
    lSlider->SetNDC(); 
    lSlider->SetTextAlign(22); 
    lSlider->SetTextSize(0.032);
    lSlider->SetTextColor(knobColor + 2); 
    lSlider->Draw();

    c->Modified();
    c->Update();
    c->cd();

}

//* MODULAR METHODS: STEP 5 (Inverse Quantum Fourier Transform) ---------------
void QHHLA_SoftEdu::DrawMath_Step5(Int_t microStep){

    // Common variables used across all microsteps
    TString b1Str = FormatComplex(fbetaNum1);
    TString b2Str = FormatComplex(fbetaNum2);
    TString sign1, val1, sign2, val2;
    DecomposeSign(b1Str, sign1, val1);
    DecomposeSign(b2Str, sign2, val2);
    
    Int_t m = fClockQubitsM;
    Int_t lim_t = ftotalStates - 1;
    
    // Calculate theta_j = lambda_j * tau / (2*pi) for each eigenvalue
    Double_t theta1 = fmappedLambda1 * fTimeScale / TMath::TwoPi();
    Double_t theta2 = fmappedLambda2 * fTimeScale / TMath::TwoPi();
    
    //? Rendering step 5.1: Clock Register Status
    if (microStep >= 1 && microStep < 4) {

        TString S51titleDesc = "#font[62]{#color[600]{5.1. Clock Register Status:}} "
            "Starting from the state evolved by each eigenvalue.";
        TLatex *lTitleS51 = new TLatex(0.02, 0.80, S51titleDesc.Data());
        lTitleS51->SetNDC();          
        lTitleS51->SetTextFont(42);   
        lTitleS51->SetTextSize(0.040);
        lTitleS51->SetTextColor(kGray+3);
        lTitleS51->Draw();
        
        // Show the clock register state before IQFT
        TString eq51a = TString::Format(
            "|#phi_{j}#GT = #frac{1}{#sqrt{2^{#color[635]{m}}}} = #sum_{t=0}^{2^{#color[635]{m}}-1}#scale[1.5]{e}^{i#lambda_{j}#taut}|t#GT_{C}"
            "   #color[2]{#rightarrow} "
            "#scale[0.8]{#font[42]{#color[635]{For m = %.i qubits}}}"
            "  #color[2]{#rightarrow}   "
            "|#phi_{j}#GT = #frac{1}{#sqrt{#color[419]{%d}}} #sum_{t=0}^{#color[419]{%d}}#scale[1.5]{e}^{i#lambda_{j}#tau t} |t#GT_{C}",
            m, ftotalStates, lim_t
        );
        TLatex *lEqS51a = new TLatex(0.04, 0.70, eq51a.Data());
        lEqS51a->SetNDC();
        lEqS51a->SetTextFont(132);     
        lEqS51a->SetTextSize(0.05);
        lEqS51a->SetTextColor(kBlack); 
        lEqS51a->Draw();
        
        // Define theta_j
        TString eq51b = TString::Format(
            "#scale[0.8]{#font[42]{#color[635]{   Defining the phase:}}}   "
            "#theta_{j} = #frac{#lambda_{j}#tau}{2#pi} "
            "#color[2]{#rightarrow}   "
            "|#phi_{j}#GT = #frac{1}{#sqrt{#color[419]{%d}}} #sum_{t=0}^{#color[419]{%d}}#scale[1.5]{e}^{2#pi i #theta_{j} t}|t#GT_{C}",
            ftotalStates, lim_t
        );
        TLatex *lEqS51b = new TLatex(0.04, 0.60, eq51b.Data());
        lEqS51b->SetNDC();
        lEqS51b->SetTextFont(132);     
        lEqS51b->SetTextSize(0.05);
        lEqS51b->SetTextColor(kBlack); 
        lEqS51b->Draw();
        
        // Show actual theta values for both eigenvalues
        TPaveText *pBox51 = new TPaveText(0.72, 0.60, 0.98, 0.80, "NDC");
        pBox51->SetFillColor(kYellow-9);
        pBox51->SetBorderSize(1);
        pBox51->SetTextAlign(22);
        pBox51->SetTextSize(0.045);
        pBox51->SetTextFont(132);
        pBox51->SetTextColor(kBlack); 
        pBox51->AddText(TString::Format(
            "#color[834]{#theta_{1} = #frac{%.2f(#pi/%.0f)}{2#pi} = #frac{%.2f}{%.i} = %.2f}", 
            fmappedLambda1, fDemTau, fmappedLambda1, ftotalStates, theta1).Data());
        pBox51->AddText(TString::Format(
            "#color[804]{#theta_{2} = #frac{%.2f(#pi/%.0f)}{2#pi} = #frac{%.2f}{%.i} = %.2f}", 
            fmappedLambda2, fDemTau, fmappedLambda2, ftotalStates, theta2).Data());
        pBox51->Draw();

    }
    
    //? Rendering step 5.2: Definition of the IQFT Operator
    if (microStep >= 2 && microStep < 4) {

        TString S52titleDesc = "#font[62]{#color[600]{5.2. Definition of the IQFT Operator:}} "
            "To extract the eigenvalues embedded in the unobservable phase.";
        TLatex *lTitleS52 = new TLatex(0.02, 0.50, S52titleDesc.Data());
        lTitleS52->SetNDC();          
        lTitleS52->SetTextFont(42);   
        lTitleS52->SetTextSize(0.040);
        lTitleS52->SetTextColor(kGray+3);
        lTitleS52->Draw();
        
        // IQFT definition
        TString eq52 = TString::Format(
            "IQFT(|t#GT) = #frac{1}{#sqrt{2^{#color[635]{m}}}} #sum_{y=0}^{2^{#color[635]{m}}-1}#scale[1.5]{e}^{-2#pii#frac{ty}{2^{m}}}|y#GT_{C}"
            "   #color[2]{#rightarrow} "
            "#scale[0.9]{#font[42]{#color[635]{For m = %.i qubits}}}"
            "  #color[2]{#rightarrow}   "
            "IQFT(|t#GT) = #frac{1}{#sqrt{#color[419]{%d}}} #sum_{y=0}^{#color[419]{%d}}#scale[1.5]{e}^{-2#pii#frac{ty}{#color[419]{%d}}}|y#GT_{C}",
            m, ftotalStates, lim_t, ftotalStates
        );
        TLatex *lEqS52 = new TLatex(0.04, 0.40, eq52.Data());
        lEqS52->SetNDC();
        lEqS52->SetTextFont(132);     
        lEqS52->SetTextSize(0.05);
        lEqS52->SetTextColor(kBlack); 
        lEqS52->Draw();

    }
    
    //? Rendering step 5.3: Applying the IQFT to the clock register:
    if (microStep >= 3 && microStep < 4) {

        TString S53titleDesc = "#font[62]{#color[600]{5.3. Applying the IQFT to the clock register:}} ";
        TLatex *lTitleS53 = new TLatex(0.02, 0.28, S53titleDesc.Data());
        lTitleS53->SetNDC();          
        lTitleS53->SetTextFont(42);   
        lTitleS53->SetTextSize(0.040);
        lTitleS53->SetTextColor(kGray+3);
        lTitleS53->Draw();
        
        TString eq53 = TString::Format(
            "IQFT|#phi_{j}#GT = #frac{1}{2^{m}} #sum_{t=0}^{2^{m}-1} "
            "#sum_{y=0}^{2^{m}-1}#scale[1.5]{e}^{2#piit#left(#theta_{j} - #frac{y}{2^{m}}#right)}|y#GT"
            "  #color[2]{#rightarrow}  "
            "#color[834]{|#phi_{1}#GT} = #frac{1}{%.i} #sum_{t=0}^{%.i} "
            "#sum_{y=0}^{%.i} #color[834]{#scale[1.5]{e}^{2#piit#left(#frac{%.2f}{%.i} - #frac{y}{%.i}#right)}}|y#GT_{C} ,   "
            "#color[804]{|#phi_{2}#GT} = #frac{1}{%.i} #sum_{t=0}^{%.i} "
            "#sum_{y=0}^{%.i} #color[804]{#scale[1.5]{e}^{2#piit#left(#frac{%.2f}{%.i} - #frac{y}{%.i}#right)}}|y#GT_{C}",
            ftotalStates, lim_t, lim_t, fmappedLambda1, ftotalStates, ftotalStates,
            ftotalStates, lim_t, lim_t, fmappedLambda2, ftotalStates, ftotalStates
        );
        TLatex *lEqS53 = new TLatex(0.02, 0.18, eq53.Data());
        lEqS53->SetNDC();
        lEqS53->SetTextFont(132);     
        lEqS53->SetTextSize(0.05);
        lEqS53->SetTextColor(kBlack); 
        lEqS53->Draw();

    }

    //? Rendering step 5.4: Expansion of the Interference Summation
    if (microStep == 4) {

        TString S54titleDesc = "#font[62]{#color[600]{5.4. Expansion of the Interference Summation:}} "
            "The phases add or cancel depending on the difference.";
        TLatex *lTitleS54 = new TLatex(0.02, 0.83, S54titleDesc.Data());
        lTitleS54->SetNDC();          
        lTitleS54->SetTextFont(42);   
        lTitleS54->SetTextSize(0.040);
        lTitleS54->SetTextColor(kGray+3);
        lTitleS54->Draw();
        
        // --- LINE 1: Theta 1 - phase difference (lambda1 - y)/totalStates ---
        TString line1 = "#color[834]{#theta_{1}} #color[2]{#rightarrow} ";
        line1 += "#sum_{y=0}^{" + TString::Format("%d", lim_t) + "} #scale[1.5]{e}^{2#piit#left(#frac{#color[635]{%.2f - y}}{%d}#right)}|y#GT = ";
        line1 = TString::Format(line1.Data(), fmappedLambda1, ftotalStates);
        
        if (m <= 3) {
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) line1 += " + ";
                line1 += TString::Format(
                    "#scale[1.5]{e}^{2#piit#left(#frac{#color[635]{%.2f - %d}}{%d}#right)}|%d#GT", 
                    fmappedLambda1, y, ftotalStates, y
                );
            }
        } else {
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) line1 += " + ";
                line1 += TString::Format(
                    "#scale[1.5]{e}^{2#piit#left(#frac{#color[635]{%.2f - %d}}{%d}#right)}|%d#GT", 
                    fmappedLambda1, y, ftotalStates, y
                );
            }
            line1 += " + ... + ";
            line1 += TString::Format(
                "#scale[1.5]{e}^{2#piit#left(#frac{#color[635]{%.2f - %d}}{%d}#right)}|%d#GT", 
                fmappedLambda1, lim_t, ftotalStates, lim_t
            );
        }
        
        TLatex *lLine1 = new TLatex(0.0, 0.72, line1.Data());
        lLine1->SetNDC();
        lLine1->SetTextFont(132);     
        if (m == 3) { 
            lLine1->SetTextSize(0.035);
        } else {
            lLine1->SetTextSize(0.050);
        }  
        lLine1->SetTextColor(kTeal-6); 
        lLine1->Draw();

        // --- LINE 2: Theta 1 - evaluated phase values ---
        TString line2 = "          = ";
        line2 = TString::Format(line2.Data(), fmappedLambda1, ftotalStates);

        if (m <= 3) {
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) line2 += " + ";
                Double_t phase = (fmappedLambda1 - y);
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    line2 += TString::Format("#color[635]{1}|%d#GT",y);
                } else {
                    line2 += TString::Format(
                        "#scale[1.5]{e}^{#piit#left(#frac{#color[635]{%.2f}}{%.d}#right)}|%d#GT",
                        phase, dem, y
                    );
                }
            }
        } else {
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) line2 += " + ";
                Double_t phase = fmappedLambda1 - y;
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    line2 += TString::Format("#color[635]{1}|%d#GT",y);
                } else {
                    line2 += TString::Format(
                        "#scale[1.5]{e}^{#piit#left(#frac{#color[635]{%.2f}}{%.d}#right)}|%d#GT",
                        phase, dem, y
                    );
                }
            }
            line2 += " + ... + ";
            Double_t phaseLast = (fmappedLambda1 - lim_t);
            Int_t dem = ftotalStates / 2;
            
            if (phaseLast == 0.0) {
                line2 += TString::Format("#color[635]{1}|%d#GT",lim_t);
            } else {
                line2 += TString::Format(
                    "#scale[1.5]{e}^{#piit#left(#frac{#color[635]{%.2f}}{%d}#right)}|%d#GT",
                    phaseLast, dem, lim_t
                );
            }
        }

        TLatex *lLine2 = new TLatex(0.0, 0.60, line2.Data());
        lLine2->SetNDC();
        lLine2->SetTextFont(132);     
        if (m == 3) { 
            lLine2->SetTextSize(0.033);
        } else {
            lLine2->SetTextSize(0.050);
        }  
        lLine2->SetTextColor(kTeal-6); 
        lLine2->Draw();
        
        // --- LINE 3: Theta 2 - phase difference (lambda2 - y)/totalStates ---
        TString line3 = "#color[804]{#theta_{2}} #color[2]{#rightarrow} ";
        line3 += "#sum_{y=0}^{" + TString::Format("%d", lim_t) + "} #scale[1.5]{e}^{2#piit#left(#frac{#color[419]{%.2f - y}}{%d}#right)}|y#GT = ";
        line3 = TString::Format(line3.Data(), fmappedLambda2, ftotalStates);
        
        if (m <= 3) {
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) line3 += " + ";
                line3 += TString::Format(
                    "#scale[1.5]{e}^{2#piit#left(#frac{#color[419]{%.2f - %d}}{%d}#right)}|%d#GT", 
                    fmappedLambda2, y, ftotalStates, y
                );
            }
        } else {
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) line3 += " + ";
                line3 += TString::Format(
                    "#scale[1.5]{e}^{2#piit#left(#frac{#color[419]{%.2f - %d}}{%d}#right)}|%d#GT", 
                    fmappedLambda2, y, ftotalStates, y
                );
            }
            line3 += " + ... + ";
            line3 += TString::Format(
                "#scale[1.5]{e}^{2#piit#left(#frac{#color[419]{%.2f - %d}}{%d}#right)}|%d#GT", 
                fmappedLambda2, lim_t, ftotalStates, lim_t
            );
        }

        TLatex *lLine3 = new TLatex(0.0, 0.45, line3.Data());
        lLine3->SetNDC();
        lLine3->SetTextFont(132);     
        if (m == 3) { 
            lLine3->SetTextSize(0.033);
        } else {
            lLine3->SetTextSize(0.050);
        }  
        lLine3->SetTextColor(kOrange+4); 
        lLine3->Draw();

        // --- LINE 4: Theta 2 - evaluated phase values ---
        TString line4 = "          = ";
        line4 = TString::Format(line4.Data(), fmappedLambda2, ftotalStates);
        
        if (m <= 3) {
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) line4 += " + ";
                Double_t phase = (fmappedLambda2 - y);
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    line4 += TString::Format("#color[419]{1}|%d#GT",y);
                } else {
                    line4 += TString::Format(
                        "#scale[1.5]{e}^{#piit#left(#frac{#color[419]{%.2f}}{%.d}#right)}|%d#GT",
                        phase, dem, y
                    );
                }
            }
        } else {
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) line4 += " + ";
                Double_t phase = fmappedLambda2 - y;
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    line4 += TString::Format("#color[419]{1}|%d#GT",y);
                } else {
                    line4 += TString::Format(
                        "#scale[1.5]{e}^{#piit#left(#frac{#color[419]{%.2f}}{%.d}#right)}|%d#GT",
                        phase, dem, y
                    );
                }
            }
            line4 += " + ... + ";
            Double_t phaseLast = (fmappedLambda2 - lim_t);
            Int_t dem = ftotalStates / 2;
            
            if (phaseLast == 0.0) {
                line4 += TString::Format("#color[419]{1}|%d#GT",lim_t);
            } else {
                line4 += TString::Format(
                    "#scale[1.5]{e}^{#piit#left(#frac{#color[419]{%.2f}}{%d}#right)}|%d#GT",
                    phaseLast, dem, lim_t
                );
            }
        }
        
        TLatex *lLine4 = new TLatex(0.0, 0.33, line4.Data());
        lLine4->SetNDC();
        lLine4->SetTextFont(132);     
        if (m == 3) { 
            lLine4->SetTextSize(0.035);
        } else {
            lLine4->SetTextSize(0.050);
        }  
        lLine4->SetTextColor(kOrange+4); 
        lLine4->Draw();
        
        // Resonance points box
        Int_t yRes1 = TMath::Nint(fmappedLambda1);
        Int_t yRes2 = TMath::Nint(fmappedLambda2);
        
        TPaveText *pBox54 = new TPaveText(0.025, 0.025, 0.40, 0.25, "NDC");
        pBox54->SetFillColor(kYellow-9);
        pBox54->SetBorderSize(1);
        pBox54->SetLineColor(kOrange-2);
        pBox54->SetTextAlign(22);
        pBox54->SetTextSize(0.035);
        pBox54->SetTextFont(42);
        pBox54->SetMargin(0.05);
        pBox54->AddText("#font[62]{#color[600]{Resonance Points:}}");
        pBox54->AddText("");
        pBox54->AddText(TString::Format("#color[834]{#theta_{1}:  y = %d} #color[2]{#rightarrow} phase = 0 (Construtive interference)", yRes1).Data());
        pBox54->AddText(TString::Format("#color[804]{#theta_{2}:  y = %d} #color[2]{#rightarrow} phase = 0 (Construtive interference)", yRes2).Data());
        pBox54->AddText("");
        pBox54->AddText("#font[62]{#color[635]{All other y: DESTRUCTIVE interference}}");
        pBox54->Draw();

    }

    //? Rendering step 5.5: Continuing the development of the IQFT in the clock register |C₁⟩
    if (microStep == 5) {

        TString S55titleDesc = "#font[62]{#color[600]{5.5. Continuing the development of the IQFT in the clock register |#phi_{1}#GT:}}";
        TLatex *lTitleS55 = new TLatex(0.02, 0.83, S55titleDesc.Data());
        lTitleS55->SetNDC();          
        lTitleS55->SetTextFont(42);   
        lTitleS55->SetTextSize(0.040);
        lTitleS55->SetTextColor(kGray+3);
        lTitleS55->Draw();

        TString Eq54 = TString::Format("#color[834]{|#phi_{1}#GT} = #frac{1}{%d}  ", ftotalStates);
        Eq54 = TString::Format(Eq54.Data(), fmappedLambda1, ftotalStates);

        if (m <= 3) {
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) Eq54 += " + ";
                Double_t phase = (fmappedLambda1 - y);
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    Eq54 += TString::Format("#sum_{t=0}^{%.i}#color[834]{1}|%d#GT",lim_t,y);
                } else {
                    Eq54 += TString::Format(
                        "#sum_{t=0}^{%.i}#color[834]{#scale[1.5]{e}^{i#frac{%.2f#pi}{%d}#color[1]{t}}}|%d#GT",
                        lim_t, phase, dem, y
                    );
                }
            }
        } else {
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) Eq54 += " + ";
                Double_t phase = fmappedLambda1 - y;
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    Eq54 += TString::Format("#sum_{t=0}^{%.i}#color[834]{1}|%d#GT",lim_t,y);
                } else {
                    Eq54 += TString::Format(
                        "#sum_{t=0}^{%.i}#color[834]{#scale[1.5]{e}^{i#frac{%.2f#pi}{%d}#color[1]{t}}}|%d#GT",
                        lim_t, phase, dem, y
                    );
                }
            }
            Eq54 += " + ... + ";
            Double_t phaseLast = (fmappedLambda1 - lim_t);
            Int_t dem = ftotalStates / 2;
            
            if (phaseLast == 0.0) {
                Eq54 += TString::Format("#sum_{t=0}^{%.i}#color[834]{1}|%d#GT",lim_t,lim_t);
            } else {
                Eq54 += TString::Format(
                    "#sum_{t=0}^{%.i}#color[834]{#scale[1.5]{e}^{i#frac{%.2f#pi}{%d}#color[1]{t}}}|%d#GT",
                    lim_t, phaseLast, dem, lim_t
                );
            }
        }

        TLatex *eq54 = new TLatex(0.02, 0.72, Eq54.Data());
        eq54->SetNDC();
        eq54->SetTextFont(132);     
        if (m == 3) { 
            eq54->SetTextSize(0.035);
        } else {
            eq54->SetTextSize(0.050);
        }  
        eq54->SetTextColor(kBlack); 
        eq54->Draw();

        // TPaveText to display the expanded sums row by row
        TPaveText *pBox55 = new TPaveText(0.0, 0.08, 0.98, 0.64, "NDC");
        pBox55->SetFillColor(kWhite);
        pBox55->SetBorderSize(0);
        pBox55->SetTextAlign(12); 
        pBox55->SetTextFont(132);
        pBox55->SetTextColor(kBlack);
        
        if (m == 3) {
            pBox55->SetTextSize(0.040);
        } else if (m > 3) {
            pBox55->SetTextSize(0.055);
        } else {
            pBox55->SetTextSize(0.055);
        }
        
        // For m = 1,2 we show all rows and all terms; for m > 3 we use ellipsis
        Bool_t showAllY = (m <= 3);
        Bool_t showAllT = (m <= 3);
        
        for (Int_t y = 0; y <= lim_t; y++) {
            // Vertical ellipsis for m > 3 between the 3rd and last expansion
            if (!showAllY && y > 2 && y < lim_t) {
                if (y == 3) {
                    pBox55->AddText("             + \\vdots");
                }
                continue;
            }
            
            Double_t phase = fmappedLambda1 - y;
            Int_t dem = ftotalStates / 2;
            Bool_t isResonance = (TMath::Abs(phase) < 1e-10);
            
            TString line;
            if (y == 0) {
                line = TString::Format("#color[834]{|#phi_{1}#GT} = #frac{1}{%.d} #left[",ftotalStates);
            } else {
                line = TString::Format("       + #frac{1}{%.d} #left[",ftotalStates);
            }
            
            // Expand the sum over t for the current |y>
            for (Int_t t = 0; t <= lim_t; t++) {
                // Horizontal ellipsis for m > 2 inside each row
                if (!showAllT && t > 2 && t < lim_t) {
                    if (t == 3) line += " + ... + ";
                    continue;
                }
                
                if (t > 0) line += " + ";
                
                if (isResonance) {
                    // When phase is zero, every term simplifies to 1
                    line += "#color[834]{1}";
                } else {
                    // t=0 always gives e^{0}=1; print it as 1 for cleanliness
                    if (t == 0) {
                        line += "#color[834]{1}";
                    } else {
                        line += TString::Format("#color[834]{#scale[1.5]{e}^{i#frac{%.2f#color[1]{(%d)}#pi}{%d}}}", phase, t, dem);
                    }
                }
            }
            
            line += TString::Format("#right] |%d#GT", y);
            pBox55->AddText(line.Data());
        }
        
        pBox55->Draw();

    }

    //? Rendering step 5.6: Evaluating each exponential term in the clock register |C₁⟩
    if (microStep >= 6 && microStep < 8) {

        TString S56titleDesc = "#font[62]{#color[600]{5.6. Evaluating the Exponentials in |#phi_{1}#GT:}} Applying the property #scale[1.5]{e}^{i#theta}=cos(#theta)+isin(#theta)";
        TLatex *lTitleS56 = new TLatex(0.02, 0.83, S56titleDesc.Data());
        lTitleS56->SetNDC();          
        lTitleS56->SetTextFont(42);   
        lTitleS56->SetTextSize(0.040);
        lTitleS56->SetTextColor(kGray+3);
        lTitleS56->Draw();

        // TPaveText to display the evaluated sums row by row
        TPaveText *pBox56 = new TPaveText(0.0, 0.28, 0.98, 0.80, "NDC");
        pBox56->SetFillColor(kWhite);
        pBox56->SetBorderSize(0);
        pBox56->SetTextAlign(12); 
        pBox56->SetTextFont(132);
        pBox56->SetTextColor(kBlack);
        
        if (m == 3) {
            pBox56->SetTextSize(0.040);
        } else if (m > 3) {
            pBox56->SetTextSize(0.055);
        } else {
            pBox56->SetTextSize(0.055);
        }
        
        // For m <= 3 we show all rows and all terms; for m > 3 we use ellipsis
        Bool_t showAllY = (m <= 3);
        Bool_t showAllT = (m <= 3);
        
        for (Int_t y = 0; y <= lim_t; y++) {
            // Vertical ellipsis for m > 3 between the 3rd and last expansion
            if (!showAllY && y > 2 && y < lim_t) {
                if (y == 3) {
                    pBox56->AddText("             + \\vdots");
                }
                continue;
            }
            
            Double_t phase = fmappedLambda1 - y;
            Int_t dem = ftotalStates / 2;
            Bool_t isResonance = (TMath::Abs(phase) < 1e-10);
            
            TString line;
            if (y == 0) {
                line = TString::Format("#color[834]{|#phi_{1}#GT} = #scale[0.8]{#frac{1}{%.d}} #left[", ftotalStates);
            } else {
                line = TString::Format("       + #scale[0.8]{#frac{1}{%.d}} #left[", ftotalStates);
            }
            
            // Expand the sum over t for the current |y>
            for (Int_t t = 0; t <= lim_t; t++) {
                // Horizontal ellipsis for m > 3 inside each row
                if (!showAllT && t > 2 && t < lim_t) {
                    if (t == 3) line += " + ... + ";
                    continue;
                }
                
                // Determine the evaluated term and its sign
                TString termVal;
                Bool_t isNegative = kFALSE;
                
                if (isResonance) {
                    termVal = "1";
                } else {
                    Double_t angle = phase * t * TMath::Pi() / dem;
                    Double_t s = TMath::Sin(angle);
                    Double_t c = TMath::Cos(angle);
                    const Double_t eps = 1e-6;
                    const Double_t invSqrt2 = 1.0 / TMath::Sqrt(2.0);
                    
                    if (TMath::Abs(s) < eps && TMath::Abs(c - 1.0) < eps) {
                        termVal = "1";
                    } else if (TMath::Abs(s) < eps && TMath::Abs(c + 1.0) < eps) {
                        termVal = "1";
                        isNegative = kTRUE;
                    } else if (TMath::Abs(s - 1.0) < eps && TMath::Abs(c) < eps) {
                        termVal = "i";
                    } else if (TMath::Abs(s + 1.0) < eps && TMath::Abs(c) < eps) {
                        termVal = "i";
                        isNegative = kTRUE;
                    } else if (TMath::Abs(c - invSqrt2) < eps && TMath::Abs(s - invSqrt2) < eps) {
                        // Quadrant I (π/4) -> + +
                        termVal = "#left(1/#sqrt{2} + i/#sqrt{2}#right)";
                    } else if (TMath::Abs(c + invSqrt2) < eps && TMath::Abs(s - invSqrt2) < eps) {
                        // Quadrant II (3π/4) -> - +
                        termVal = "#left(-1/#sqrt{2} + i/#sqrt{2}#right)";
                    } else if (TMath::Abs(c + invSqrt2) < eps && TMath::Abs(s + invSqrt2) < eps) {
                        // Quadrant III (5π/4) -> - -
                        termVal = "#left(1/#sqrt{2} + i/#sqrt{2}#right)";
                        isNegative = kTRUE;
                    } else if (TMath::Abs(c - invSqrt2) < eps && TMath::Abs(s + invSqrt2) < eps) {
                        // Quadrant IV (7π/4) -> + -
                        termVal = "#left(1/#sqrt{2} - i/#sqrt{2}#right)";
                    } else {
                        // Fallback: keep exponential form
                        termVal = TString::Format("#scale[1.5]{e}^{i#frac{%.2f#color[1]{(%d)}#pi}{%d}}", phase, t, dem);
                    }
                }
                
                // Append separator respecting sign (avoid "+ -")
                if (t == 0) {
                    if (isNegative) {
                        line += "- #color[834]{" + termVal + "}";
                    } else {
                        line += "#color[834]{" + termVal + "}";
                    }
                } else {
                    if (isNegative) {
                        line += " - #color[834]{" + termVal + "}";
                    } else {
                        line += " + #color[834]{" + termVal + "}";
                    }
                }
            }
            
            line += TString::Format("#right] |%d#GT", y);
            pBox56->AddText(line.Data());
        }
        
        pBox56->Draw();

    }

    //? Rendering step 5.7: Final collapsed state of the clock register |C₁⟩
    if (microStep >= 7 && microStep < 8) {

        TString S57titleDesc = "#font[62]{#color[600]{5.7. Final State of the Clock Register |#phi_{1}#GT:}} "
            "Only the resonant component survives after complete interference.";
        TLatex *lTitleS57 = new TLatex(0.02, 0.23, S57titleDesc.Data());
        lTitleS57->SetNDC();          
        lTitleS57->SetTextFont(42);   
        lTitleS57->SetTextSize(0.040);
        lTitleS57->SetTextColor(kGray+3);
        lTitleS57->Draw();

        Int_t yRes1 = TMath::Nint(fmappedLambda1);
        if (yRes1 < 0) yRes1 = 0;
        if (yRes1 > lim_t) yRes1 = lim_t;

        // Build the final state equation in one line
        TString eq57 = "#color[834]{|#phi_{1}#GT} = #frac{1}{#color[419]{" 
                + TString::Format("%d", ftotalStates) + "}} #left[";

        if (m <= 3) {
            // Show every term explicitly
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) eq57 += " + ";
                if (y == yRes1) {
                    eq57 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, y);
                } else {
                    eq57 += TString::Format("0|%d#GT", y);
                }
            }
        } else {
            // First three terms
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) eq57 += " + ";
                if (y == yRes1) {
                    eq57 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, y);
                } else {
                    eq57 += TString::Format("0|%d#GT", y);
                }
            }

            if (yRes1 < 3) {
                // Resonance already shown; just add ellipsis and last term
                eq57 += " + ... + ";
                if (yRes1 == lim_t) {
                    eq57 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, lim_t);
                } else {
                    eq57 += TString::Format("0|%d#GT", lim_t);
                }
            } else {
                // Resonance lies beyond the first three terms
                eq57 += " + ... + ";
                if (yRes1 < lim_t) {
                    // Show resonance, then ellipsis, then last term
                    eq57 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, yRes1);
                    eq57 += " + ... + ";
                    eq57 += TString::Format("0|%d#GT", lim_t);
                } else {
                    // Resonance is exactly the last term
                    eq57 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, lim_t);
                }
            }
        }
        eq57 += "#right]";

        TLatex *lEqS57 = new TLatex(0.04, 0.15, eq57.Data());
        lEqS57->SetNDC();
        lEqS57->SetTextFont(132);     
        lEqS57->SetTextSize(0.05);
        lEqS57->SetTextColor(kBlack); 
        lEqS57->Draw();
    }

    //? Rendering step 5.8: Continuing the development of the IQFT in the clock register |C₂⟩
    if (microStep == 8) {

        TString S58titleDesc = "#font[62]{#color[600]{5.8. Continuing the development of the IQFT in the clock register |#phi_{2}#GT:}}";
        TLatex *lTitleS58 = new TLatex(0.02, 0.83, S58titleDesc.Data());
        lTitleS58->SetNDC();          
        lTitleS58->SetTextFont(42);   
        lTitleS58->SetTextSize(0.040);
        lTitleS58->SetTextColor(kGray+3);
        lTitleS58->Draw();

        TString Eq58 = TString::Format("#color[804]{|#phi_{2}#GT} = #frac{1}{%d}  ", ftotalStates);
        Eq58 = TString::Format(Eq58.Data(), fmappedLambda2, ftotalStates);

        if (m <= 3) {
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) Eq58 += " + ";
                Double_t phase = (fmappedLambda2 - y);
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    Eq58 += TString::Format("#sum_{t=0}^{%.i}#color[804]{1}|%d#GT",lim_t,y);
                } else {
                    Eq58 += TString::Format(
                        "#sum_{t=0}^{%.i}#color[804]{#scale[1.5]{e}^{i#frac{%.2f#pi}{%d}#color[1]{t}}}|%d#GT",
                        lim_t, phase, dem, y
                    );
                }
            }
        } else {
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) Eq58 += " + ";
                Double_t phase = fmappedLambda2 - y;
                Int_t dem = ftotalStates / 2;
                
                if (phase == 0.0) {
                    Eq58 += TString::Format("#sum_{t=0}^{%.i}#color[804]{1}|%d#GT",lim_t,y);
                } else {
                    Eq58 += TString::Format(
                        "#sum_{t=0}^{%.i}#color[804]{#scale[1.5]{e}^{i#frac{%.2f#pi}{%d}#color[1]{t}}}|%d#GT",
                        lim_t, phase, dem, y
                    );
                }
            }
            Eq58 += " + ... + ";
            Double_t phaseLast = (fmappedLambda2 - lim_t);
            Int_t dem = ftotalStates / 2;
            
            if (phaseLast == 0.0) {
                Eq58 += TString::Format("#sum_{t=0}^{%.i}#color[804]{1}|%d#GT",lim_t,lim_t);
            } else {
                Eq58 += TString::Format(
                    "#sum_{t=0}^{%.i}#color[804]{#scale[1.5]{e}^{i#frac{%.2f#pi}{%d}#color[1]{t}}}|%d#GT",
                    lim_t, phaseLast, dem, lim_t
                );
            }
        }

        TLatex *eq58 = new TLatex(0.02, 0.72, Eq58.Data());
        eq58->SetNDC();
        eq58->SetTextFont(132);     
        if (m == 3) { 
            eq58->SetTextSize(0.035);
        } else {
            eq58->SetTextSize(0.050);
        }  
        eq58->SetTextColor(kBlack); 
        eq58->Draw();

        // TPaveText to display the expanded sums row by row
        TPaveText *pBox58 = new TPaveText(0.0, 0.08, 0.98, 0.64, "NDC");
        pBox58->SetFillColor(kWhite);
        pBox58->SetBorderSize(0);
        pBox58->SetTextAlign(12); 
        pBox58->SetTextFont(132);
        pBox58->SetTextColor(kBlack);
        
        if (m == 3) {
            pBox58->SetTextSize(0.040);
        } else if (m > 3) {
            pBox58->SetTextSize(0.055);
        } else {
            pBox58->SetTextSize(0.055);
        }
        
        // For m = 1,2 we show all rows and all terms; for m > 3 we use ellipsis
        Bool_t showAllY = (m <= 3);
        Bool_t showAllT = (m <= 3);
        
        for (Int_t y = 0; y <= lim_t; y++) {
            // Vertical ellipsis for m > 3 between the 3rd and last expansion
            if (!showAllY && y > 2 && y < lim_t) {
                if (y == 3) {
                    pBox58->AddText("             + \\vdots");
                }
                continue;
            }
            
            Double_t phase = fmappedLambda2 - y;
            Int_t dem = ftotalStates / 2;
            Bool_t isResonance = (TMath::Abs(phase) < 1e-10);
            
            TString line;
            if (y == 0) {
                line = TString::Format("#color[804]{|#phi_{2}#GT} = #frac{1}{%.d} #left[", ftotalStates);
            } else {
                line = TString::Format("       + #frac{1}{%.d} #left[", ftotalStates);
            }
            
            // Expand the sum over t for the current |y>
            for (Int_t t = 0; t <= lim_t; t++) {
                // Horizontal ellipsis for m > 2 inside each row
                if (!showAllT && t > 2 && t < lim_t) {
                    if (t == 3) line += " + ... + ";
                    continue;
                }
                
                if (t > 0) line += " + ";
                
                if (isResonance) {
                    // When phase is zero, every term simplifies to 1
                    line += "#color[804]{1}";
                } else {
                    // t=0 always gives e^{0}=1; print it as 1 for cleanliness
                    if (t == 0) {
                        line += "#color[804]{1}";
                    } else {
                        line += TString::Format("#color[804]{#scale[1.5]{e}^{i#frac{%.2f#color[1]{(%d)}#pi}{%d}}}", phase, t, dem);
                    }
                }
            }
            
            line += TString::Format("#right] |%d#GT", y);
            pBox58->AddText(line.Data());
        }
        
        pBox58->Draw();

    }

    //? Rendering step 5.9: Evaluating each exponential term in the clock register |C₂⟩
    if (microStep >= 9 && microStep < 11) {

        TString S59titleDesc = "#font[62]{#color[600]{5.9. Evaluating the Exponentials in |C_{2}#GT:}} Applying the property #scale[1.5]{e}^{i#theta}=cos(#theta)+isin(#theta)";
        TLatex *lTitleS59 = new TLatex(0.02, 0.83, S59titleDesc.Data());
        lTitleS59->SetNDC();          
        lTitleS59->SetTextFont(42);   
        lTitleS59->SetTextSize(0.040);
        lTitleS59->SetTextColor(kGray+3);
        lTitleS59->Draw();

        // TPaveText to display the evaluated sums row by row
        TPaveText *pBox59 = new TPaveText(0.0, 0.28, 0.98, 0.80, "NDC");
        pBox59->SetFillColor(kWhite);
        pBox59->SetBorderSize(0);
        pBox59->SetTextAlign(12); 
        pBox59->SetTextFont(132);
        pBox59->SetTextColor(kBlack);
        
        if (m == 3) {
            pBox59->SetTextSize(0.040);
        } else if (m > 3) {
            pBox59->SetTextSize(0.055);
        } else {
            pBox59->SetTextSize(0.055);
        }
        
        // For m <= 3 we show all rows and all terms; for m > 3 we use ellipsis
        Bool_t showAllY = (m <= 3);
        Bool_t showAllT = (m <= 3);
        
        for (Int_t y = 0; y <= lim_t; y++) {
            // Vertical ellipsis for m > 3 between the 3rd and last expansion
            if (!showAllY && y > 2 && y < lim_t) {
                if (y == 3) {
                    pBox59->AddText("             + \\vdots");
                }
                continue;
            }
            
            Double_t phase = fmappedLambda2 - y;
            Int_t dem = ftotalStates / 2;
            Bool_t isResonance = (TMath::Abs(phase) < 1e-10);
            
            TString line;
            if (y == 0) {
                line = TString::Format("#color[804]{|#phi_{2}#GT} = #scale[0.8]{#frac{1}{%.d}} #left[", ftotalStates);
            } else {
                line = TString::Format("       + #scale[0.8]{#frac{1}{%.d}} #left[", ftotalStates);
            }
            
            // Expand the sum over t for the current |y>
            for (Int_t t = 0; t <= lim_t; t++) {
                // Horizontal ellipsis for m > 3 inside each row
                if (!showAllT && t > 2 && t < lim_t) {
                    if (t == 3) line += " + ... + ";
                    continue;
                }
                
                // Determine the evaluated term and its sign
                TString termVal;
                Bool_t isNegative = kFALSE;
                
                if (isResonance) {
                    termVal = "1";
                } else {
                    Double_t angle = phase * t * TMath::Pi() / dem;
                    Double_t s = TMath::Sin(angle);
                    Double_t c = TMath::Cos(angle);
                    const Double_t eps = 1e-6;
                    const Double_t invSqrt2 = 1.0 / TMath::Sqrt(2.0);
                    
                    if (TMath::Abs(s) < eps && TMath::Abs(c - 1.0) < eps) {
                        termVal = "1";
                    } else if (TMath::Abs(s) < eps && TMath::Abs(c + 1.0) < eps) {
                        termVal = "1";
                        isNegative = kTRUE;
                    } else if (TMath::Abs(s - 1.0) < eps && TMath::Abs(c) < eps) {
                        termVal = "i";
                    } else if (TMath::Abs(s + 1.0) < eps && TMath::Abs(c) < eps) {
                        termVal = "i";
                        isNegative = kTRUE;
                    } else if (TMath::Abs(c - invSqrt2) < eps && TMath::Abs(s - invSqrt2) < eps) {
                        // Quadrant I (π/4) -> + +
                        termVal = "#left(1/#sqrt{2} + i/#sqrt{2}#right)";
                    } else if (TMath::Abs(c + invSqrt2) < eps && TMath::Abs(s - invSqrt2) < eps) {
                        // Quadrant II (3π/4) -> - +
                        termVal = "#left(-1/#sqrt{2} + i/#sqrt{2}#right)";
                    } else if (TMath::Abs(c + invSqrt2) < eps && TMath::Abs(s + invSqrt2) < eps) {
                        // Quadrant III (5π/4) -> - -
                        termVal = "#left(1/#sqrt{2} + i/#sqrt{2}#right)";
                        isNegative = kTRUE;
                    } else if (TMath::Abs(c - invSqrt2) < eps && TMath::Abs(s + invSqrt2) < eps) {
                        // Quadrant IV (7π/4) -> + -
                        termVal = "#left(1/#sqrt{2} - i/#sqrt{2}#right)";
                    } else {
                        // Fallback: keep exponential form
                        termVal = TString::Format("#scale[1.5]{e}^{i#frac{%.2f#color[1]{(%d)}#pi}{%d}}", phase, t, dem);
                    }
                }
                
                // Append separator respecting sign (avoid "+ -")
                if (t == 0) {
                    if (isNegative) {
                        line += "- #color[804]{" + termVal + "}";
                    } else {
                        line += "#color[804]{" + termVal + "}";
                    }
                } else {
                    if (isNegative) {
                        line += " - #color[804]{" + termVal + "}";
                    } else {
                        line += " + #color[804]{" + termVal + "}";
                    }
                }
            }
            
            line += TString::Format("#right] |%d#GT", y);
            pBox59->AddText(line.Data());
        }
        
        pBox59->Draw();

    }

    //? Rendering step 5.10: Final collapsed state of the clock register |C₂⟩
    if (microStep >= 10 && microStep < 11) {

        TString S510titleDesc = "#font[62]{#color[600]{5.7. Final State of the Clock Register |#phi_{2}#GT:}} "
            "Only the resonant component survives after complete interference.";
        TLatex *lTitleS510 = new TLatex(0.02, 0.23, S510titleDesc.Data());
        lTitleS510->SetNDC();          
        lTitleS510->SetTextFont(42);   
        lTitleS510->SetTextSize(0.040);
        lTitleS510->SetTextColor(kGray+3);
        lTitleS510->Draw();

        Int_t yRes1 = TMath::Nint(fmappedLambda2);
        if (yRes1 < 0) yRes1 = 0;
        if (yRes1 > lim_t) yRes1 = lim_t;

        // Build the final state equation in one line
        TString eq510 = "#color[804]{|#phi_{1}#GT} = #frac{1}{#color[419]{" 
                + TString::Format("%d", ftotalStates) + "}} #left[";

        if (m <= 3) {
            // Show every term explicitly
            for (Int_t y = 0; y <= lim_t; y++) {
                if (y > 0) eq510 += " + ";
                if (y == yRes1) {
                    eq510 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, y);
                } else {
                    eq510 += TString::Format("0|%d#GT", y);
                }
            }
        } else {
            // First three terms
            for (Int_t y = 0; y < 3 && y <= lim_t; y++) {
                if (y > 0) eq510 += " + ";
                if (y == yRes1) {
                    eq510 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, y);
                } else {
                    eq510 += TString::Format("0|%d#GT", y);
                }
            }

            if (yRes1 < 3) {
                // Resonance already shown; just add ellipsis and last term
                eq510 += " + ... + ";
                if (yRes1 == lim_t) {
                    eq510 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, lim_t);
                } else {
                    eq510 += TString::Format("0|%d#GT", lim_t);
                }
            } else {
                // Resonance lies beyond the first three terms
                eq510 += " + ... + ";
                if (yRes1 < lim_t) {
                    // Show resonance, then ellipsis, then last term
                    eq510 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, yRes1);
                    eq510 += " + ... + ";
                    eq510 += TString::Format("0|%d#GT", lim_t);
                } else {
                    // Resonance is exactly the last term
                    eq510 += TString::Format("#color[2]{%d}|%d#GT", ftotalStates, lim_t);
                }
            }
        }
        eq510 += "#right]";

        TLatex *lEqS510 = new TLatex(0.04, 0.15, eq510.Data());
        lEqS510->SetNDC();
        lEqS510->SetTextFont(132);     
        lEqS510->SetTextSize(0.05);
        lEqS510->SetTextColor(kBlack); 
        lEqS510->Draw();
    }

    //? Rendering step 5.11: Global Resulting State |Ψ_3⟩
    if (microStep >= 11){

        TString S511titleDesc = "#font[62]{#color[600]{5.11. Global Resulting State |#Psi_{3}#GT:}} ";
        TLatex *lTitleS511 = new TLatex(0.02, 0.70, S511titleDesc.Data());
        lTitleS511->SetNDC();          
        lTitleS511->SetTextFont(42);   
        lTitleS511->SetTextSize(0.040);
        lTitleS511->SetTextColor(kGray+3);
        lTitleS511->Draw();

        TString eq511a = TString::Format(
            "|#Psi_{3}#GT = #frac{%s}{#sqrt{%.0f}} #color[834]{|%.2f#GT_{C}} #otimes |u_{1}#GT_{I} #otimes |0#GT_{A}"
            " %s #frac{%s}{#sqrt{%.0f}} #color[804]{|%.2f#GT_{C}} #otimes |u_{2}#GT_{I} #otimes |0#GT_{A}", 
            b1Str.Data(), fIntDenomSq, fLambdaQPE1, sign2.Data(), val2.Data(), fIntDenomSq, fLambdaQPE2
        );
        TLatex *lEqS511a = new TLatex(0.04, 0.60, eq511a.Data());
        lEqS511a->SetNDC();
        lEqS511a->SetTextFont(132);     
        lEqS511a->SetTextSize(0.05);
        lEqS511a->SetTextColor(kBlack); 
        lEqS511a->Draw();

        TString eq511b = TString::Format(
            "In binary:"
        );
        TLatex *lEqS511b = new TLatex(0.04, 0.50, eq511b.Data());
        lEqS511b->SetNDC();
        lEqS511b->SetTextFont(42);     
        lEqS511b->SetTextSize(0.04);
        lEqS511b->SetTextColor(kRed+3); 
        lEqS511b->Draw();

        TString eq511c = TString::Format(
            "|#Psi_{3}#GT = #frac{%s}{#sqrt{%.0f}} #color[834]{|%s#GT_{C}} #otimes |u_{1}#GT_{I} #otimes |0#GT_{A}"
            " %s #frac{%s}{#sqrt{%.0f}} #color[804]{|%s#GT_{C}} #otimes |u_{2}#GT_{I} #otimes |0#GT_{A}", 
            b1Str.Data(), fIntDenomSq, fBinLambda1.Data(), sign2.Data(), val2.Data(), fIntDenomSq, fBinLambda2.Data()
        );
        TLatex *lEqS511c = new TLatex(0.04, 0.40, eq511c.Data());
        lEqS511c->SetNDC();
        lEqS511c->SetTextFont(132);     
        lEqS511c->SetTextSize(0.05);
        lEqS511c->SetTextColor(kBlack); 
        lEqS511c->Draw();

    }

}

void QHHLA_SoftEdu::DrawMatrix_Step5(Int_t microStep){

    Int_t lim_t = ftotalStates - 1;

    //? Rendering step 5.12: IQFT Matrix Definition
    if (microStep == 12) {

        TString S512titleDesc = TString::Format(
            "#font[62]{#color[600]{5.12. IQFT Matrix U_{IQFT} (%d#times%d):}} "
            "Inverse Quantum Fourier Transform operator.",
            ftotalStates, ftotalStates);
        TLatex *lTitleS512 = new TLatex(0.02, 0.80, S512titleDesc.Data());
        lTitleS512->SetNDC();          
        lTitleS512->SetTextFont(42);   
        lTitleS512->SetTextSize(0.040);
        lTitleS512->SetTextColor(kGray+3);
        lTitleS512->Draw();
        
        // Formula definition
        TString eq512 = TString::Format(
            "#hat{U}_{IQFT}(y,t) = #sum_{t,y=0}^{%i}#frac{1}{#sqrt{%d}} #scale[1.5]{e}^{-2#pi i #frac{yt}{%d}}",
            lim_t, ftotalStates, ftotalStates
        );
        TLatex *lEqS512 = new TLatex(0.10, 0.70, eq512.Data());
        lEqS512->SetNDC();
        lEqS512->SetTextFont(132);     
        lEqS512->SetTextSize(0.045);
        lEqS512->SetTextColor(kBlack); 
        lEqS512->Draw();

        //? Display IQFT Matrix elements
        // Calculate scaling parameters based on matrix size
        Double_t startX = 0.30;    
        Double_t startY = 0.55;    
        Double_t cellW = 0.0, cellH = 0.0;
        Int_t textSize = 0;
        
        if (ftotalStates <= 2) {       // m=1, N=2
            cellW = 0.14; cellH = 0.14; textSize = 70;
        } else if (ftotalStates <= 4) { // m=2, N=4
            cellW = 0.10; cellH = 0.10; textSize = 55;
        } else if (ftotalStates <= 8) { // m=3, N=8
            cellW = 0.06; cellH = 0.06; textSize = 35;
        } else {                        // m>3, N>8
            cellW = 0.04; cellH = 0.04; textSize = 25;
        }
        
        // Calculate the total dimensions of the matrix to center it.
        Double_t matWidth = (ftotalStates - 1) * cellW + cellW;
        //Double_t matHeight = (ftotalStates - 1) * cellH + cellH;
        
        // Adjust startX to center the matrix on the canvas.
        startX = 0.55 - matWidth / 2.0;
        
        // Calculate matrix boundaries to center the U_IQFT label.
        Double_t bLeft = startX - cellW * 0.5;
        Double_t bRight = startX + (ftotalStates - 1) * cellW + cellW * 0.5;
        Double_t bTop = startY + cellH * 0.5;
        Double_t bBot = startY - (ftotalStates - 1) * cellH - cellH * 0.5;
        Double_t matCenterY = (bTop + bBot) / 2.0;
        
        // Matrix label U_IQFT = 1/sqrt(N) 
        TLatex *lMatLabel = new TLatex(0.15, matCenterY, 
            TString::Format("#hat{U}_{IQFT} = #frac{1}{#sqrt{%d}}", ftotalStates));
        lMatLabel->SetNDC();
        lMatLabel->SetTextAlign(22);     
        lMatLabel->SetTextFont(132);
        lMatLabel->SetTextSize(0.060);   
        lMatLabel->SetTextColor(kBlack);
        lMatLabel->Draw();
        
        // Draw matrix grid with elements
        for (Int_t y = 0; y < ftotalStates; y++) {
            for (Int_t t = 0; t < ftotalStates; t++) {
                // Calculate phase angle: -2π * y * t / N
                Double_t phase = -2.0 * TMath::Pi() * y * t / (Double_t)ftotalStates;
                Double_t c = TMath::Cos(phase);
                Double_t s = TMath::Sin(phase);
                const Double_t eps = 1e-10;
                
                // Determine element string representation
                TString elemStr;
                Color_t elemColor = kBlack;
                
                if (TMath::Abs(c - 1.0) < eps && TMath::Abs(s) < eps) {
                    elemStr = "#color[4]{1}";      // Blue for +1
                    elemColor = kBlue;
                } else if (TMath::Abs(c + 1.0) < eps && TMath::Abs(s) < eps) {
                    elemStr = "#color[2]{-1}";     // Red for -1
                    elemColor = kRed;
                } else if (TMath::Abs(c) < eps && TMath::Abs(s - 1.0) < eps) {
                    elemStr = "#color[419]{i}";    // Green for +i
                    elemColor = kGreen+2;
                } else if (TMath::Abs(c) < eps && TMath::Abs(s + 1.0) < eps) {
                    elemStr = "#color[810]{-i}";    // Orange for -i
                    elemColor = kMagenta;
                } else {
                    // Complex value - show compact form
                    if (TMath::Abs(s) < eps) {
                        elemStr = TString::Format("%.1f", c);
                    } else if (TMath::Abs(c) < eps) {
                        elemStr = TString::Format("%.1fi", s);
                    } else {
                        elemStr = TString::Format("%.1f%+.1fi", c, s);
                    }
                    elemColor = kGray+2;
                }
                
                // Position in canvas
                Double_t xPos = startX + t * cellW;
                Double_t yPos = startY - y * cellH;
                
                // Draw cell background (light grid)
                TBox *cellBox = new TBox(xPos - cellW*0.45, yPos - cellH*0.45, 
                                        xPos + cellW*0.45, yPos + cellH*0.45);
                if (y == 0 || t == 0) {
                    cellBox->SetFillColor(kYellow-10); // Highlight first row/col
                } else {
                    cellBox->SetFillColor(kWhite);
                }
                cellBox->SetLineColor(kGray+1);
                cellBox->SetLineWidth(1);
                cellBox->Draw("l");
                
                // Draw element text
                TLatex *lElem = new TLatex(xPos, yPos, elemStr.Data());
                lElem->SetNDC();
                lElem->SetTextAlign(22);
                lElem->SetTextFont(42);
                lElem->SetTextSize(textSize * 0.001);
                lElem->SetTextColor(elemColor);
                lElem->Draw();
            }
        }
        
        // Draw matrix brackets
        TLine *lineBrack = new TLine();
        lineBrack->SetLineWidth(3);     
        
        // Left bracket '['
        lineBrack->DrawLine(bLeft, bTop, bLeft, bBot);
        lineBrack->DrawLine(bLeft, bTop, bLeft + 0.010, bTop);
        lineBrack->DrawLine(bLeft, bBot, bLeft + 0.010, bBot);
        
        // Right bracket ']'
        lineBrack->DrawLine(bRight, bTop, bRight, bBot);
        lineBrack->DrawLine(bRight, bTop, bRight - 0.010, bTop);
        lineBrack->DrawLine(bRight, bBot, bRight - 0.010, bBot);
        
        // Row labels (y) 
        for (Int_t i = 0; i < ftotalStates; i++) {
            TLatex *lRow = new TLatex(bLeft - 0.020, startY - i * cellH, 
                TString::Format("y=%d", i));
            lRow->SetNDC();
            lRow->SetTextAlign(32);
            lRow->SetTextFont(42);
            lRow->SetTextSize(0.028);   
            lRow->SetTextColor(kGray+2);
            lRow->Draw();
        }
        
        // Column labels (t) 
        for (Int_t i = 0; i < ftotalStates; i++) {
            TLatex *lCol = new TLatex(startX + i * cellW, bTop + 0.03, 
                TString::Format("t=%d", i));
            lCol->SetNDC();
            lCol->SetTextAlign(22);
            lCol->SetTextFont(42);
            lCol->SetTextSize(0.028);
            lCol->SetTextColor(kGray+2);
            lCol->Draw();
        }
        
    }
    
    //? Rendering step 5.13: Matrix IQFT + Vectors |C₁⟩ y |C₂⟩ 
    if (microStep >= 13) {

        TLatex *lTitleS513 = new TLatex(0.02, 0.82, "#font[62]{#color[600]{5.13. Applying the U_{IQFT} to the clock registers (Matrix notation):}}");
        lTitleS513->SetNDC(); 
        lTitleS513->SetTextFont(42); 
        lTitleS513->SetTextSize(0.040); 
        lTitleS513->SetTextColor(kGray+3);
        lTitleS513->Draw();
        
        // Scalable dimension configuration
        Int_t drawStates = (ftotalStates > 8) ? 6 : ftotalStates;
        Double_t cellSize = (ftotalStates <= 4) ? 0.060 : (ftotalStates <= 8) ? 0.030 : 0.035;
        Double_t tSize = cellSize * 0.85;
        
        // Lambda function to quickly draw brackets
        auto drawBrackets = [](Double_t x, Double_t y, Double_t width, Double_t height) {
            Double_t L = x - 0.007, R = x + width + 0.007;
            Double_t T = y + height/2.0 + 0.007, B = y - height/2.0 - 0.007;
            TLine *lb = new TLine(); lb->SetLineWidth(2); lb->SetLineColor(kBlack);
            lb->DrawLine(L, T, L, B); lb->DrawLine(L, T, L+0.005, T); lb->DrawLine(L, B, L+0.005, B);
            lb->DrawLine(R, T, R, B); lb->DrawLine(R, T, R-0.005, T); lb->DrawLine(R, B, R-0.005, B);
        };

        // Dynamic Horizontal Positioning
        Double_t startX = 0.20;
        Double_t mX = startX;
        Double_t mWidth = drawStates * cellSize;
        Double_t vcX = mX + mWidth + 0.03; 
        Double_t vcWidth = cellSize;
        Double_t eqX = vcX + vcWidth + 0.03;
        Double_t fracX = eqX + 0.03;
        Double_t resX = fracX + 0.03;
        Double_t resWidth = cellSize;
        Double_t finalX = resX + resWidth + 0.03;

        // Product U_IQFT |C₁⟩ 
        Double_t m1Y = 0.62;
        
        TLatex *lP1 = new TLatex(0.10, m1Y, TString::Format("U_{IQFT}#color[834]{|#phi_{1}#GT}  =  #frac{1}{%d}", ftotalStates).Data());
        lP1->SetNDC(); 
        lP1->SetTextAlign(22); 
        lP1->SetTextFont(132); 
        lP1->SetTextSize(0.055); 
        lP1->SetTextColor(kBlack);
        lP1->Draw();
        
        // IQFT Matrix 1
        for (Int_t r = 0; r < drawStates; r++) {
            Int_t y = r; bool isRowDots = false;
            // Row truncation logic
            if (ftotalStates > 8) {
                if (r == 4) { isRowDots = true; y = -1; }
                else if (r == 5) y = ftotalStates - 1;
            }
            
            for (Int_t c = 0; c < drawStates; c++) {
                Int_t t = c; bool isColDots = false;
                // Column truncation logic
                if (ftotalStates > 8) {
                    if (c == 4) { isColDots = true; t = -1; }
                    else if (c == 5) t = ftotalStates - 1;
                }
                
                TString elemStr;
                if (isRowDots && isColDots) elemStr = "\\ddots";
                else if (isRowDots) elemStr = "\\vdots";
                else if (isColDots) elemStr = "\\dots";
                else {
                    Double_t phase = -2.0 * TMath::Pi() * y * t / (Double_t)ftotalStates;
                    Double_t cosP = TMath::Cos(phase), sinP = TMath::Sin(phase);
                    const Double_t eps = 1e-10;
                    if (TMath::Abs(cosP-1.0)<eps && TMath::Abs(sinP)<eps) elemStr = "1";
                    else if (TMath::Abs(cosP+1.0)<eps && TMath::Abs(sinP)<eps) elemStr = "-1";
                    else if (TMath::Abs(cosP)<eps && TMath::Abs(sinP-1.0)<eps) elemStr = "i";
                    else if (TMath::Abs(cosP)<eps && TMath::Abs(sinP+1.0)<eps) elemStr = "-i";
                    else if (TMath::Abs(sinP)<eps) elemStr = TString::Format("%.0f", cosP);
                    else if (TMath::Abs(cosP)<eps) elemStr = TString::Format("%.0fi", sinP);
                    else elemStr = TString::Format("%.1f%+.1fi", cosP, sinP);
                }
                
                TLatex *le = new TLatex(mX + c*cellSize + cellSize/2 - 0.01, m1Y + (drawStates/2.0 - r)*cellSize - cellSize/2, elemStr.Data());
                le->SetNDC();
                le->SetTextAlign(22);
                le->SetTextFont(132);
                le->SetTextSize(tSize);
                le->SetTextColor(kBlack);
                le->Draw();
            }
        }

        drawBrackets(mX, m1Y, mWidth, drawStates * cellSize);
        
        // Vector |C₁⟩
        for (Int_t r = 0; r < drawStates; r++) {
            Int_t y = r; bool isRowDots = false;
            if (ftotalStates > 8) {
                if (r == 4) { isRowDots = true; y = -1; }
                else if (r == 5) y = ftotalStates - 1;
            }
            TString es;
            if (isRowDots) es = "\\vdots";
            else {
                TString ps = fPhaseStrings[0][y]; ps = ps.Strip(TString::kBoth);
                es = (ps=="")?"1":(ps=="-")?"-1":(ps=="i")?"i":(ps=="-i")?"-i"
                :(ps == "#left(1/#sqrt{2} + i/#sqrt{2}#right)")?"0.7 + 0.7i"
                :(ps == "#left(-1/#sqrt{2} + i/#sqrt{2}#right)")? "-0.7 + 0.7i"
                :(ps == "#left(-1/#sqrt{2} - i/#sqrt{2}#right)")? "-0.7 - 0.7i"
                :(ps == "#left(1/#sqrt{2} - i/#sqrt{2}#right)")?"0.7 - 0.7i":ps;
            }
            TLatex *le = new TLatex(vcX + cellSize/2 + 0.005, m1Y + (drawStates/2.0 - r)*cellSize - cellSize/2, es.Data());
            le->SetNDC();
            le->SetTextAlign(22);
            le->SetTextFont(132);
            le->SetTextSize(tSize);
            le->SetTextColor(kTeal-6);
            le->Draw();
        }

        drawBrackets(vcX, m1Y, vcWidth+0.01, drawStates * cellSize);
        
        TLatex *lEq1 = new TLatex(eqX, m1Y, "=");
        lEq1->SetNDC();
        lEq1->SetTextAlign(22);
        lEq1->SetTextFont(132);
        lEq1->SetTextSize(0.060);
        lEq1->SetTextColor(kBlack);
        lEq1->Draw();
        
        TLatex *lFrac1 = new TLatex(fracX, m1Y, TString::Format("#frac{1}{#color[419]{%d}}", ftotalStates).Data());
        lFrac1->SetNDC();
        lFrac1->SetTextAlign(22);
        lFrac1->SetTextFont(132);
        lFrac1->SetTextSize(0.055);
        lFrac1->SetTextColor(kBlack);
        lFrac1->Draw();
        
        // Result vector (peak in λ₁)
        for (Int_t r = 0; r < drawStates; r++) {
            Int_t y = r; bool isRowDots = false;
            if (ftotalStates > 8) {
                if (r == 4) { isRowDots = true; y = -1; }
                else if (r == 5) y = ftotalStates - 1;
            }
            TString elemStr;
            if (isRowDots) elemStr = "\\vdots";
            else elemStr = (y == (Int_t)TMath::Nint(fLambdaQPE1)) ? TString::Format("#color[2]{%d}", ftotalStates) : "0";
            TLatex *le = new TLatex(resX + cellSize/2, m1Y + (drawStates/2.0 - r)*cellSize - cellSize/2, elemStr.Data());
            le->SetNDC(); 
            le->SetTextAlign(22); 
            le->SetTextFont(132); 
            le->SetTextSize(tSize); 
            le->SetTextColor(kBlack);
            le->Draw();
        }

        drawBrackets(resX, m1Y, resWidth, drawStates * cellSize);
        
        // = |λ₁⟩
        TLatex *lFinal1 = new TLatex(finalX, m1Y, TString::Format("= |%s#GT", fBinLambda1.Data()).Data());
        lFinal1->SetNDC(); 
        lFinal1->SetTextAlign(12);
        lFinal1->SetTextFont(132); 
        lFinal1->SetTextSize(0.055); 
        lFinal1->SetTextColor(kBlack);
        lFinal1->Draw();
        
        // Product U_QFT† |C₂⟩
        Double_t m2Y = 0.28; // Equilibrado en la parte inferior
        
        TLatex *lP2 = new TLatex(0.10, m2Y, TString::Format("U_{IQFT}#color[804]{|#phi_{2}#GT}  =  #frac{1}{%d}", ftotalStates).Data());
        lP2->SetNDC(); 
        lP2->SetTextAlign(22); 
        lP2->SetTextFont(132); 
        lP2->SetTextSize(0.055); 
        lP2->SetTextColor(kBlack);
        lP2->Draw();
        
        // Matrix IQFT 2
        for (Int_t r = 0; r < drawStates; r++) {
            Int_t y = r; bool isRowDots = false;
            if (ftotalStates > 8) {
                if (r == 4) { isRowDots = true; y = -1; }
                else if (r == 5) y = ftotalStates - 1;
            }
            for (Int_t c = 0; c < drawStates; c++) {
                Int_t t = c; bool isColDots = false;
                if (ftotalStates > 8) {
                    if (c == 4) { isColDots = true; t = -1; }
                    else if (c == 5) t = ftotalStates - 1;
                }
                
                TString elemStr;
                if (isRowDots && isColDots) elemStr = "\\ddots";
                else if (isRowDots) elemStr = "\\vdots";
                else if (isColDots) elemStr = "\\dots";
                else {
                    Double_t phase = -2.0 * TMath::Pi() * y * t / (Double_t)ftotalStates;
                    Double_t cosP = TMath::Cos(phase), sinP = TMath::Sin(phase);
                    const Double_t eps = 1e-10;
                    if (TMath::Abs(cosP-1.0)<eps && TMath::Abs(sinP)<eps) elemStr = "1";
                    else if (TMath::Abs(cosP+1.0)<eps && TMath::Abs(sinP)<eps) elemStr = "-1";
                    else if (TMath::Abs(cosP)<eps && TMath::Abs(sinP-1.0)<eps) elemStr = "i";
                    else if (TMath::Abs(cosP)<eps && TMath::Abs(sinP+1.0)<eps) elemStr = "-i";
                    else if (TMath::Abs(sinP)<eps) elemStr = TString::Format("%.0f", cosP);
                    else if (TMath::Abs(cosP)<eps) elemStr = TString::Format("%.0fi", sinP);
                    else elemStr = TString::Format("%.1f%+.1fi", cosP, sinP);
                }
                TLatex *le = new TLatex(mX + c*cellSize + cellSize/2 - 0.01, m2Y + (drawStates/2.0 - r)*cellSize - cellSize/2, elemStr.Data());
                le->SetNDC(); 
                le->SetTextAlign(22);
                le->SetTextFont(132);
                le->SetTextSize(tSize);
                le->SetTextColor(kBlack);
                le->Draw();
            }
        }

        drawBrackets(mX, m2Y, mWidth, drawStates * cellSize);
        
        // Vector |C₂⟩
        for (Int_t r = 0; r < drawStates; r++) {
            Int_t y = r; bool isRowDots = false;
            if (ftotalStates > 8) {
                if (r == 4) { isRowDots = true; y = -1; }
                else if (r == 5) y = ftotalStates - 1;
            }
            TString es;
            if (isRowDots) es = "\\vdots";
            else {
                TString ps = fPhaseStrings[1][y]; ps = ps.Strip(TString::kBoth);
                es = (ps=="")?"1":(ps=="-")?"-1":(ps=="i")?"i":(ps=="-i")?"-i"
                :(ps == "#left(1/#sqrt{2} + i/#sqrt{2}#right)")?"0.7 + 0.7i"
                :(ps == "#left(-1/#sqrt{2} + i/#sqrt{2}#right)")? "-0.7 + 0.7i"
                :(ps == "#left(-1/#sqrt{2} - i/#sqrt{2}#right)")? "-0.7 - 0.7i"
                :(ps == "#left(1/#sqrt{2} - i/#sqrt{2}#right)")?"0.7 - 0.7i":ps;
            }
            TLatex *le = new TLatex(vcX + cellSize/2 + 0.005, m2Y + (drawStates/2.0 - r)*cellSize - cellSize/2, es.Data());
            le->SetNDC();
            le->SetTextAlign(22);
            le->SetTextFont(132);
            le->SetTextSize(tSize);
            le->SetTextColor(kOrange+4);
            le->Draw();
        }

        drawBrackets(vcX, m2Y, vcWidth+0.01, drawStates * cellSize);
        
        TLatex *lEq2 = new TLatex(eqX, m2Y, "=");
        lEq2->SetNDC();
        lEq2->SetTextAlign(22);
        lEq2->SetTextFont(132);
        lEq2->SetTextSize(0.060);
        lEq2->SetTextColor(kBlack);
        lEq2->Draw();
        
        TLatex *lFrac2 = new TLatex(fracX, m2Y, TString::Format("#frac{1}{#color[419]{%d}}", ftotalStates).Data());
        lFrac2->SetNDC();
        lFrac2->SetTextAlign(22);
        lFrac2->SetTextFont(132);
        lFrac2->SetTextSize(0.055);
        lFrac2->SetTextColor(kBlack);
        lFrac2->Draw();
        
        // Result vector (peak in λ₂) 
        for (Int_t r = 0; r < drawStates; r++) {
            Int_t y = r; bool isRowDots = false;
            if (ftotalStates > 8) {
                if (r == 4) { isRowDots = true; y = -1; }
                else if (r == 5) y = ftotalStates - 1;
            }
            TString elemStr;
            if (isRowDots) elemStr = "\\vdots";
            else elemStr = (y == (Int_t)TMath::Nint(fLambdaQPE2)) ? TString::Format("#color[2]{%d}", ftotalStates) : "0";
            TLatex *le = new TLatex(resX + cellSize/2, m2Y + (drawStates/2.0 - r)*cellSize - cellSize/2, elemStr.Data());
            le->SetNDC();
            le->SetTextAlign(22);
            le->SetTextFont(132);
            le->SetTextSize(tSize);
            le->SetTextColor(kBlack);
            le->Draw();
        }

        drawBrackets(resX, m2Y, resWidth, drawStates * cellSize);
        
        // = |λ₂⟩
        TLatex *lFinal2 = new TLatex(finalX, m2Y, TString::Format("= |%s#GT", fBinLambda2.Data()).Data());
        lFinal2->SetNDC(); lFinal2->SetTextAlign(12);
        lFinal2->SetTextFont(132);
        lFinal2->SetTextSize(0.055);
        lFinal2->SetTextColor(kBlack);
        lFinal2->Draw();
    }

}

void QHHLA_SoftEdu::DrawCircuit_Step5(Int_t microStep){

    // Position parameters
    Double_t xStart = 0.05;        // Start of the lines
    Double_t xEnd = 0.95;          // End of the lines
    Double_t yIndex = 0.75;        // Position Y of the Index record (top)
    Double_t yAncilla = 0.20;      // Y position of the Ancilla qubit (lower)
    Double_t yClockStart = 0.65;   // Clock bus start
    Double_t yClockSpacing = 0.10; // Space between clock qubits

    // Gate dimensions (Hadamard)
    Double_t hGateX1 = 0.07;
    Double_t hGateX2 = 0.11;
    Double_t hGateHalfHeight = 0.04;
    
    // Gate dimensions (Controlled-U)
    Double_t uGateWidth = 0.10;
    Double_t uGateHeight = 0.08;
    Double_t uGateXStart = 0.13;   // Starting X position for U gates
    Double_t uGateSpacing = 0.12;  // Spacing between U gates
    
    //? Rendering step 5.14: Circuit Diagram step 4
    if (microStep >= 14) {

        // TOP LINE: Memory/Index Register
        TLine *lineIndex = new TLine(xStart, yIndex, xEnd, yIndex);
        lineIndex->SetLineWidth(2);
        lineIndex->SetLineColor(kBlue+3);
        lineIndex->Draw();
        
        // Initial state |0⟩ for index record
        TLatex *stateIndex = new TLatex(xStart - 0.035, yIndex-0.015, "|b#GT_{I}");
        stateIndex->SetNDC();
        stateIndex->SetTextFont(62);
        stateIndex->SetTextSize(0.05);
        stateIndex->SetTextColor(kBlue+3);
        stateIndex->Draw();
        
        // CENTRAL LINES: Clock Register m-qubit bus
        for (Int_t i = 0; i < fClockQubitsM; i++) {
            Double_t yClock = yClockStart - (i * yClockSpacing);
            
            TLine *lineClock = new TLine(xStart, yClock, xEnd, yClock);
            lineClock->SetLineWidth(2);
            lineClock->SetLineColor(kGreen+3);
            lineClock->Draw();
            
            // Initial state |0⟩ for each qubit of the clock
            TLatex *stateClock = new TLatex(xStart - 0.035, yClock - 0.015, "|0#GT_{C}");
            stateClock->SetNDC();
            stateClock->SetTextFont(62);
            stateClock->SetTextSize(0.05);
            stateClock->SetTextColor(kGreen+3);
            stateClock->Draw();

            if (microStep >= 15) {

                // Background box for the gate
                TBox *hBox = new TBox(hGateX1, yClock - hGateHalfHeight, hGateX2, yClock + hGateHalfHeight);
                hBox->SetFillColor(kCyan-10);
                hBox->SetLineColor(kCyan+4);
                hBox->SetLineWidth(1.5);
                hBox->Draw("l");
                
                // Letter 'H' inside the box
                TLatex *hText = new TLatex((hGateX1 + hGateX2)/2.0, yClock, "H");
                hText->SetTextAlign(22);
                hText->SetTextFont(62);
                hText->SetTextSize(0.06);
                hText->SetTextColor(kCyan+4);
                hText->Draw();

            }

        }
        
        // BOTTOM LINE: Qubit Ancilla
        TLine *lineAncilla = new TLine(xStart, yAncilla, xEnd, yAncilla);
        lineAncilla->SetLineWidth(2);
        lineAncilla->SetLineColor(kCyan+3);
        lineAncilla->Draw();
        
        // Initial state |0⟩ for the ancilla
        TLatex *stateAncilla = new TLatex(xStart - 0.035, yAncilla - 0.015, "|0#GT_{A}");
        stateAncilla->SetNDC();
        stateAncilla->SetTextFont(62);
        stateAncilla->SetTextSize(0.05);
        stateAncilla->SetTextColor(kCyan+3);
        stateAncilla->Draw();
        
        //? Rendering step 5.16: Controlled-U operations
        if (microStep >= 16) {

            // Draw controlled-U gates for each clock qubit
            for (Int_t i = 0; i < fClockQubitsM; i++) {
                Double_t yClock = yClockStart - (i * yClockSpacing);
                Double_t uGateX = uGateXStart + (i * uGateSpacing);
                
                // Calculate the power: 2^i
                Int_t power = TMath::Power(2, i);
                
                // Draw control dot on clock qubit line
                TMarker *controlDot = new TMarker(uGateX + uGateWidth/2.0, yClock, 20);
                controlDot->SetMarkerSize(1.5);
                controlDot->SetMarkerColor(kBlue+4);
                controlDot->SetMarkerStyle(20);
                controlDot->Draw();
                
                // Draw vertical line from control to U gate
                TLine *controlLine = new TLine(uGateX + uGateWidth/2.0, yClock, 
                    uGateX + uGateWidth/2.0, yIndex);
                controlLine->SetLineWidth(1);
                controlLine->SetLineColor(kBlue+4);
                controlLine->Draw();
                
                // Draw U gate box on index register line
                TBox *uBox = new TBox(uGateX, yIndex - uGateHeight/2.0, 
                    uGateX + uGateWidth, yIndex + uGateHeight/2.0);
                uBox->SetFillColor(kBlue-10);
                uBox->SetLineColor(kBlue+4);
                uBox->SetLineWidth(1.5);
                uBox->Draw("l");
                
                // Label U gate with power notation
                TString uLabel;
                if (i == 0) {
                    uLabel = "U^{2^{0}}=e^{iA#tau(1)}";
                } else if (i == 1) {
                    uLabel = "U^{2^{1}}=e^{iA#tau(2)}";
                } else {
                    uLabel = TString::Format("U^{2^{%d}}=e^{iA#tau(%d)}", i, power);
                }
                
                TLatex *uText = new TLatex(uGateX + uGateWidth/2.0, yIndex, uLabel);
                uText->SetTextAlign(22);
                uText->SetTextFont(42);
                uText->SetTextSize(0.05);
                uText->SetTextColor(kBlue+4);
                uText->Draw();
    
            }

        }
        
        //? Rendering step 5.17: IQFT box at the end of clock register lines
        if (microStep >= 17) {

            // Calculate bounds for the IQFT box spanning all clock qubits
            Double_t yClockTop = yClockStart + hGateHalfHeight;      // Top of first clock qubit line
            Double_t yClockBottom = yClockStart - ((fClockQubitsM - 1) * yClockSpacing) - hGateHalfHeight; // Bottom of last clock qubit line
            
            // Calculate end position of last Controlled-U gate
            Int_t lastUIndex = fClockQubitsM - 1;
            Double_t lastUGateX = uGateXStart + (lastUIndex * uGateSpacing);
            Double_t uGatesEndX = lastUGateX + uGateWidth;
            
            Double_t iqftWidth = 0.05;
            Double_t xIQFT = uGatesEndX + 0.02;  // Small gap after last U gate
            Double_t xIQFTEnd = xIQFT + iqftWidth;
            
            // Draw IQFT box spanning all clock register lines
            TBox *iqftBox = new TBox(xIQFT, yClockBottom, xIQFTEnd, yClockTop);
            iqftBox->SetFillColor(kViolet-9);
            iqftBox->SetLineColor(kViolet+3);
            iqftBox->SetLineWidth(1.5);
            iqftBox->Draw("l");
            
            // Vertical "IQFT" label 
            TLatex *iqftLabel = new TLatex(xIQFT + iqftWidth/2.0, (yClockTop + yClockBottom)/2.0, "IQFT");
            iqftLabel->SetTextAlign(22);
            iqftLabel->SetTextFont(62);
            iqftLabel->SetTextSize(0.05);
            iqftLabel->SetTextColor(kViolet+3);
            iqftLabel->SetTextAngle(90);  // Vertical text
            iqftLabel->Draw();
            
            // QPE dashed bracket: from H gates to IQFT, covering H + U gates + IQFT vertically
            Double_t xQPE_Left = hGateX1;
            Double_t xQPE_Right = xIQFTEnd;
            
            // Vertical bounds: from top of U gates on index register to bottom of clock register
            Double_t yQPE_Top = yIndex + uGateHeight/2.0 + 0.02;     // Top of U gates on index line
            Double_t yQPE_Bottom = yClockBottom - 0.02;               // Bottom of last clock line
            
            // Draw dashed bracket (no fill, dashed lines)
            // Top edge - dashed
            TLine *qpeTop = new TLine(xQPE_Left, yQPE_Top, xQPE_Right, yQPE_Top);
            qpeTop->SetLineColor(kOrange+3);
            qpeTop->SetLineWidth(2);
            qpeTop->SetLineStyle(2);  // Dashed line
            qpeTop->Draw();
            
            // Bottom edge - dashed
            TLine *qpeBottom = new TLine(xQPE_Left, yQPE_Bottom, xQPE_Right, yQPE_Bottom);
            qpeBottom->SetLineColor(kOrange+3);
            qpeBottom->SetLineWidth(2);
            qpeBottom->SetLineStyle(2);  // Dashed line
            qpeBottom->Draw();
            
            // Left edge - dashed
            TLine *qpeLeft = new TLine(xQPE_Left, yQPE_Top, xQPE_Left, yQPE_Bottom);
            qpeLeft->SetLineColor(kOrange+3);
            qpeLeft->SetLineWidth(2);
            qpeLeft->SetLineStyle(2);  // Dashed line
            qpeLeft->Draw();
            
            // Right edge - dashed
            TLine *qpeRight = new TLine(xQPE_Right, yQPE_Top, xQPE_Right, yQPE_Bottom);
            qpeRight->SetLineColor(kOrange+3);
            qpeRight->SetLineWidth(2);
            qpeRight->SetLineStyle(2);  // Dashed line
            qpeRight->Draw();
            
            // QPE label at the center of the bottom edge
            TLatex *qpeLabel = new TLatex((xQPE_Left + xQPE_Right)/2.0, yQPE_Bottom - 0.015, "QPE");
            qpeLabel->SetTextAlign(23);  // Centered, bottom-aligned
            qpeLabel->SetTextFont(62);
            qpeLabel->SetTextSize(0.05);
            qpeLabel->SetTextColor(kOrange+3);
            qpeLabel->Draw();

        }

    }

}

void QHHLA_SoftEdu::DrawGraph_Step5(Int_t microStep){

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    if (!c) return;
    c->cd();
    c->Clear();

    //? TITLE AND PROGRESS BAR (Main Canvas) ----------------------------------
    DrawStepTitle(c);
    DrawProgressBar(c);

    //? COMMON CALCULATIONS ----------------------------------------------------
    Int_t m = fClockQubitsM;
    Int_t lim_t = ftotalStates - 1;
    
    // Determine iteration count based on microStep
    Int_t iter = -1;
    if (microStep == 18) {
        iter = -1;
    } else if (microStep == 19) {
        iter = 0;
    } else if (microStep == 20) {
        iter = 1;
    } else if (microStep == 21) {
        iter = 2;
    } else if (microStep == 22) {
        iter = 3;
    } else if (microStep == 23) {
        iter = 4;
    } else if (microStep == 24) {
        iter = 5;
    } else if (microStep == 25) {
        iter = 6;
    } else if (microStep >= 26) {
        iter = 7;
    }
    
    // Map iteration index to candidate state |y> based on clock qubits m
    auto GetYForIter = [&](Int_t i) -> Int_t {
        if (m == 1) {
            return (i > 1) ? 1 : i;
        } else if (m == 2) {
            return (i > 3) ? 3 : i; // For m=2 (4 states), iter 0,1,2,3 maping to y=0,1,2,3
        } else if (m == 3) {
            return (i > 7) ? 7 : i; // For m=3 (8 states), iter 0,1,2,3,4,5,6,7 maping to y=0,1,2,3,4,5,6,7
        } else {
            // For m > 3, interpolate the 4 slider ticks across the total states.
            return (Int_t)((Double_t)(ftotalStates - 1) * i / 7.0);
        }
    };

    // Symbolic label for a phase angle, following the same e^{i*theta} -> {1,-1,i,-i}
    auto PhaseLabel = [&](Double_t phi) -> TString {
        const Double_t eps = 1e-6;
        Double_t s = TMath::Sin(phi), c = TMath::Cos(phi);
        if (TMath::Abs(s) < eps && TMath::Abs(c - 1.0) < eps) return "1";
        if (TMath::Abs(s) < eps && TMath::Abs(c + 1.0) < eps) return "-1";
        if (TMath::Abs(s - 1.0) < eps && TMath::Abs(c) < eps) return "i";
        if (TMath::Abs(s + 1.0) < eps && TMath::Abs(c) < eps) return "-i";
        return "";
    };

    /*Draws, inside the given pad, the full tip-to-tail phasor chain (from t=0 up
    to the current microStep's t) for every candidate state |y>, one state at a
    time (y=0, then y=1, ...). Every arrow is colored with the same solid branch
    color, exactly like the text rows for each branch, so what
    distinguishes a surviving state from a cancelled one is purely the resulting
    geometry: a chain that walks outward and reaches the dashed circle
    (constructive interference) versus one that curls back and closes near the
    origin (destructive interference). */
    auto DrawPhasorFan = [&](Double_t lambda_j, Color_t baseColor, TPad* pad) {
        if (!pad || iter < 0) return;
        pad->cd();

        // Obtains only the current candidate state |y>
        Int_t y = GetYForIter(iter);

        Double_t X = 0.0, Y = 0.0;

        // Draw the complete geometric series for it and the current one.
        for (Int_t t = 0; t <= lim_t; t++) {
            Double_t phi = TMath::TwoPi() * (Double_t)t * (lambda_j - y) / (Double_t)ftotalStates;

            Double_t Xnew = X + TMath::Cos(phi);
            Double_t Ynew = Y + TMath::Sin(phi);

            TArrow *arrow = new TArrow(X, Y, Xnew, Ynew, 0.012, "|>");
            arrow->SetAngle(35);
            arrow->SetLineColor(baseColor);
            arrow->SetFillColor(baseColor);
            arrow->SetLineWidth(2);
            arrow->Draw();

            // Phase labels
            TString sym = PhaseLabel(phi);
            if (sym.Length() > 0) {
                Double_t dx = Xnew - X, dy = Ynew - Y;
                Double_t norm = TMath::Sqrt(dx*dx + dy*dy);
                Double_t offX = (norm > 1e-9) ? -dy / norm * 0.28 : 0.0;
                Double_t offY = (norm > 1e-9) ?  dx / norm * 0.28 : 0.0;

                TLatex *lab = new TLatex((X + Xnew)/2.0 + offX, (Y + Ynew)/2.0 + offY, sym.Data());
                lab->SetTextAlign(22);
                lab->SetTextSize(0.030);
                lab->SetTextFont(132);
                lab->SetTextColor(baseColor);
                lab->Draw();
            }

            X = Xnew; Y = Ynew;
        }

        // We mark the final result (survival probability) for this candidate.
        TMarker *tip = new TMarker(X, Y, 20);
        tip->SetMarkerColor(baseColor);
        tip->SetMarkerSize(1.0);
        tip->Draw();

        pad->Modified();
    };


    //? LEFT PAD: Lambda 1 Branch ---------------------------------------------
    if (microStep >= 18) {

        TPad *padLeft = new TPad("padLeftStep5", "Lambda 1 Interference", 0.00, 0.18, 0.50, 0.88);
        padLeft->SetLeftMargin(0.20);
        padLeft->SetRightMargin(0.20);
        padLeft->SetTopMargin(0.10);
        padLeft->SetBottomMargin(0.05);
        padLeft->Draw();
        padLeft->cd();
        padLeft->SetGrid(0, 0);
        padLeft->SetTicks(1, 1);

        // Frame: radius = totalStates (maximum constructive sum)
        Double_t lim = ftotalStates * 1.15;
        TH1F *frameL = padLeft->DrawFrame(-lim, -lim, lim, lim);
        frameL->SetStats(0);

        // Circle of radius totalStates
        TEllipse *circleL = new TEllipse(0, 0, ftotalStates, ftotalStates);
        circleL->SetFillStyle(0);
        circleL->SetLineColor(kGray+2);
        circleL->SetLineStyle(2);
        circleL->SetLineWidth(2);
        circleL->Draw();

        // Axes (same as Step 4)
        TLine *axXL = new TLine(-lim, 0, lim, 0);
        axXL->SetLineColor(kBlack);
        axXL->SetLineWidth(1);
        axXL->Draw();
        TLine *axYL = new TLine(0, -lim, 0, lim);
        axYL->SetLineColor(kBlack);
        axYL->SetLineWidth(1);
        axYL->Draw();

        TLatex *lReL = new TLatex(lim*0.88, -0.14, "Re");
        lReL->SetTextSize(0.05);
        lReL->Draw();
        TLatex *lImL = new TLatex(-0.16, lim*0.88, "Im");
        lImL->SetTextSize(0.05);
        lImL->Draw();

        // Title
        TLatex *titleL = new TLatex(0.5, 0.95, 
            TString::Format("#font[62]{#color[834]{#lambda_{1} = %.2f Branch}}", 
                fLambda1
            ));
        titleL->SetNDC();
        titleL->SetTextAlign(22);
        titleL->SetTextSize(0.055);
        titleL->SetTextColor(kTeal-6);
        titleL->Draw();

        // Drawing the branch phasors
        DrawPhasorFan(fmappedLambda1, kTeal-6, padLeft);

    }

    //? RIGHT PAD: Lambda 2 Branch ----------------------------------------------
    if (microStep >= 18) {

        c->cd();
        TPad *padRight = new TPad("padRightStep5", "Lambda 2 Interference", 0.50, 0.18, 1.00, 0.88);
        padRight->SetLeftMargin(0.20);
        padRight->SetRightMargin(0.20);
        padRight->SetTopMargin(0.10);
        padRight->SetBottomMargin(0.05);
        padRight->Draw();
        padRight->cd();
        padRight->SetGrid(0, 0);
        padRight->SetTicks(1, 1);

        Double_t lim = ftotalStates * 1.15;
        TH1F *frameR = padRight->DrawFrame(-lim, -lim, lim, lim);
        frameR->SetStats(0);

        TEllipse *circleR = new TEllipse(0, 0, ftotalStates, ftotalStates);
        circleR->SetFillStyle(0);
        circleR->SetLineColor(kGray+2);
        circleR->SetLineStyle(2);
        circleR->SetLineWidth(2);
        circleR->Draw();

        TLine *axXR = new TLine(-lim, 0, lim, 0);
        axXR->SetLineColor(kBlack);
        axXR->SetLineWidth(1);
        axXR->Draw();
        TLine *axYR = new TLine(0, -lim, 0, lim);
        axYR->SetLineColor(kBlack);
        axYR->SetLineWidth(1);
        axYR->Draw();

        TLatex *lReR = new TLatex(lim*0.88, -0.14, "Re");
        lReR->SetTextSize(0.05);
        lReR->Draw();
        TLatex *lImR = new TLatex(-0.16, lim*0.88, "Im");
        lImR->SetTextSize(0.05);
        lImR->Draw();

        TLatex *titleR = new TLatex(0.5, 0.95, 
            TString::Format("#font[62]{#color[804]{#lambda_{2} = %.2f Branch}}", 
                fLambda2
            ));
        titleR->SetNDC();
        titleR->SetTextAlign(22);
        titleR->SetTextSize(0.055);
        titleR->SetTextColor(kOrange+4);
        titleR->Draw();

        // Drawing the branch phasors
        DrawPhasorFan(fmappedLambda2, kOrange+4, padRight);

    }

    //? VISUAL SLIDER (Main canvas, full width) -------------------------------
    c->cd();
        
        Double_t sliderY = 0.060;
        Double_t sliderX1 = 0.05;   
        Double_t sliderX2 = 0.55;   

        TBox *sliderTrack = new TBox(sliderX1, sliderY - 0.005, sliderX2, sliderY + 0.005);
        sliderTrack->SetFillColor(kGray+1);
        sliderTrack->SetLineColor(kGray+2);
        sliderTrack->Draw();

        // 4. GENERACIÓN DE MARCAS (TICKS) ADAPTABLES
        Int_t nTicks = ftotalStates; // Si m=1 habrá 2 marcas, si m=2 habrá 4, si m=3 habrá 8.
        for (Int_t i = 0; i < nTicks; i++) {
            Double_t fracTick = (nTicks > 1) ? (Double_t)i / (nTicks - 1) : 0.5;
            Double_t xpos = sliderX1 + fracTick * (sliderX2 - sliderX1);

            TLine *tick = new TLine(xpos, sliderY - 0.015, xpos, sliderY + 0.015);
            tick->SetLineColor(kBlack); 
            tick->SetLineWidth(1); 
            tick->Draw();

            Int_t yVal = GetYForIter(i);
            TString tickLabel = TString::Format("y = %d", yVal);
            
            TLatex *ltick = new TLatex(xpos, sliderY - 0.032, tickLabel);
            ltick->SetNDC(); 
            ltick->SetTextAlign(22); 
            ltick->SetTextSize(0.025); 
            ltick->Draw();
        }

        // 5. MOVIMIENTO DEL DESLIZADOR (KNOB)
        Double_t knobFrac = 0.0;
        if (iter >= 0) {
            knobFrac = (lim_t > 0) ? (Double_t)iter / (Double_t)lim_t : 0.0;
            if (knobFrac > 1.0) knobFrac = 1.0; // Seguro contra desbordamientos
        }
        Double_t knobX = sliderX1 + knobFrac * (sliderX2 - sliderX1);

        Color_t knobColor = (iter >= 0) ? kBlue : kGray + 2;

        Double_t knobHalfWidth = 0.008;  
        Double_t knobHalfHeight = 0.018; 
        
        TBox *knob = new TBox(knobX - knobHalfWidth, sliderY - knobHalfHeight, 
            knobX + knobHalfWidth, sliderY + knobHalfHeight
        );
        knob->SetFillColor(knobColor);
        knob->SetLineColor(knobColor + 2);
        knob->SetLineWidth(2);
        knob->Draw();

        // 6. TEXTO INFORMATIVO (CAPTION) DINÁMICO
        TString sliderCaption;
        if (iter < 0) {
            sliderCaption = "#font[62]{Evaluating} |y#GT = |0#GT  (animation starts at NEXT)";
        } else {
            Int_t currentY = GetYForIter(iter);
            sliderCaption = TString::Format("#font[62]{Evaluating} |y#GT = |%d#GT  (step %d of %d)", 
                currentY, iter + 1, ftotalStates
            );
        }
        TLatex *lSlider = new TLatex((sliderX1 + sliderX2)/2.0, sliderY + 0.042, sliderCaption.Data());
        lSlider->SetNDC(); 
        lSlider->SetTextAlign(22); 
        lSlider->SetTextSize(0.032);
        lSlider->SetTextColor(knobColor + 2); 
        lSlider->Draw();

    c->Modified();
    c->Update();
    c->cd();


}

//* MODULAR METHODS: STEP 6 (Controlled Rotation & Eigenvalue Inversion) ------
void QHHLA_SoftEdu::DrawMath_Step6(Int_t microStep){
    
    //? Rendering step 6.1: Eigenvalue inversion
    if (microStep >= 1) {

        TString S61title = TString::Format(
            "#font[62]{#color[600]{6.1. Eigenvalue inversion:}} "
            "Applying a controlled Y-rotation (#font[132]{R_{y}}) to the ancilla qubit."
        );
        TLatex *lTitleS61 = new TLatex(0.02, 0.84, S61title.Data());
        lTitleS61->SetNDC();          
        lTitleS61->SetTextFont(42);   
        lTitleS61->SetTextSize(0.040);
        lTitleS61->SetTextColor(kGray+3);
        lTitleS61->Draw();

        TString eq61 = TString::Format(
            "R_{y}(#theta#scale[0.7]{j})|0#GT_{A} = "
            "cos#left(#frac{#theta#scale[0.7]{j}}{2}#right)|0#GT_{A} + sen#left(#frac{#theta#scale[0.7]{j}}{2}#right)|1#GT_{A}"
            "   #color[2]{#rightarrow}   "
            "#color[635]{#scale[0.7]{#font[42]{The rotation angle is}}}"
            "   #color[2]{#rightarrow}   "
        );
        TLatex *lEq61 = new TLatex(0.04, 0.76, eq61.Data()); 
        lEq61->SetNDC();
        lEq61->SetTextFont(132);     
        lEq61->SetTextSize(0.05);
        lEq61->SetTextColor(kBlack); 
        lEq61->Draw();

        TPaveText *pBox61 = new TPaveText(0.60, 0.83, 0.75, 0.74, "NDC");
        pBox61->SetFillColor(kYellow-9);
        pBox61->SetBorderSize(1);
        pBox61->SetTextAlign(22);
        pBox61->SetTextSize(0.040);
        pBox61->SetTextFont(132);
        pBox61->SetTextColor(kRed+3); 
        TString tauCalc = TString::Format(
            "#frac{#theta#scale[0.5]{j}}{2} = arcsin#left(#frac{C}{#lambda#scale[0.7]{j}}#right)"
        );
        pBox61->AddText(tauCalc.Data());
        pBox61->Draw();
        
    }

    //? Rendering step 6.2: Definition of Normalization Constant C 
    if (microStep >= 2){

        TString S62title = TString::Format(
            "#font[62]{#color[600]{6.2. Normalization Constant C:}} "
            "To ensure the rotation angle is physically valid, we need C#leqmin|#lambda#scale[0.7]{j}|:"
        );
        TLatex *lTitleS62 = new TLatex(0.02, 0.66, S62title.Data());
        lTitleS62->SetNDC();          
        lTitleS62->SetTextFont(42);   
        lTitleS62->SetTextSize(0.040);
        lTitleS62->SetTextColor(kGray+3);
        lTitleS62->Draw();

        TString eq62 = TString::Format(
            "#font[42]{For}  #scale[1.3]{#color[834]{#lambda_{1} = %.2f},  #color[804]{#lambda_{2} = %.2f}}"
            "    #color[2]{#rightarrow}    ",
            fLambda1, fLambda2
        );
        TLatex *lEq62 = new TLatex(0.04, 0.58, eq62.Data()); 
        lEq62->SetNDC();
        lEq62->SetTextFont(132);     
        lEq62->SetTextSize(0.040);
        lEq62->SetTextColor(kBlack); 
        lEq62->Draw();

        TPaveText *pBox62 = new TPaveText(0.33, 0.62, 0.40, 0.56, "NDC");
        pBox62->SetFillColor(kYellow-9);
        pBox62->SetBorderSize(1);
        pBox62->SetTextAlign(22);
        pBox62->SetTextSize(0.045);
        pBox62->SetTextFont(132);
        pBox62->SetTextColor(kRed+3); 
        TString tauCalc = TString::Format(
            "#scale[1.3]{C = %.0f}", fC
        );
        pBox62->AddText(tauCalc.Data());
        pBox62->Draw();

    }

    //? Rendering step 6.3: Resulting rotation operation for each Branch
    if (microStep >= 3){

        TString S63title = TString::Format(
            "#font[62]{#color[600]{6.3. Resulting rotation operation for each Branch:}}"
        );
        TLatex *lTitleS63 = new TLatex(0.02, 0.50, S63title.Data());
        lTitleS63->SetNDC();          
        lTitleS63->SetTextFont(42);   
        lTitleS63->SetTextSize(0.040);
        lTitleS63->SetTextColor(kGray+3);
        lTitleS63->Draw();

        TString eq63 = TString::Format(
            "#color[834]{R_{y}(#theta_{1})|0#GT_{A} = }"
            "#color[834]{ #sqrt{ 1 - #frac{(%.0f)^{2}}{(%.2f)^{2}}} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A}}"
            ",     "
            "#color[804]{R_{y}(#theta_{1})|0#GT_{A} = }"
            "#color[804]{ #sqrt{ 1 - #frac{(%.0f)^{2}}{(%.2f)^{2}}} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A}}",
            fC, fLambda1, fC, fLambda1, fC, fLambda2, fC, fLambda2
        );
        TLatex *lEq63 = new TLatex(0.04, 0.40, eq63.Data()); 
        lEq63->SetNDC();
        lEq63->SetTextFont(132);     
        lEq63->SetTextSize(0.05);
        lEq63->SetTextColor(kBlack); 
        lEq63->Draw();

    }

    //? Rendering step 6.4: Global Resulting State |Ψ_4⟩
    if (microStep >= 4){

        Int_t num1 = (fLambda1*fLambda1)-(fC*fC);
        Int_t num2 = (fLambda2*fLambda2)-(fC*fC);

        TString b1Str = FormatComplex(fbetaNum1);
        TString b2Str = FormatComplex(fbetaNum2);
        TString sign1, val1, sign2, val2;
        DecomposeSign(b1Str, sign1, val1);
        DecomposeSign(b2Str, sign2, val2);

        TString S64titleDesc = "#font[62]{#color[600]{6.4. Resulting Global State |#Psi_{4}#GT:}}";
        TLatex *lTitleS64 = new TLatex(0.02, 0.30, S64titleDesc.Data());
        lTitleS64->SetNDC();
        lTitleS64->SetTextFont(42);
        lTitleS64->SetTextSize(0.040);
        lTitleS64->SetTextColor(kGray+3);
        lTitleS64->Draw();

        TString eq64 = TString::Format(
            "|#Psi_{4}#GT = #frac{%s}{#sqrt{%.0f}} #color[834]{|%s#GT_{C}} #otimes |u_{1}#GT_{I} #otimes "
            "#color[834]{#left[ #frac{#sqrt{%i}}{%.2f} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A} #right]}"
            " %s #frac{%s}{#sqrt{%.0f}} #color[804]{|%s#GT_{C}} #otimes |u_{2}#GT_{I} #otimes "
            "#color[804]{#left[ #frac{#sqrt{%i}}{%.2f} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A} #right]}", 
            b1Str.Data(), fIntDenomSq, fBinLambda1.Data(), num1, fLambda1, fC, fLambda1,  
            sign2.Data(), val2.Data(), fIntDenomSq, fBinLambda2.Data(), num2, fLambda2, fC, fLambda2
        );
        TLatex *lEq64 = new TLatex(0.04, 0.20, eq64.Data()); 
        lEq64->SetNDC();
        lEq64->SetTextFont(132);     
        lEq64->SetTextSize(0.05);
        lEq64->SetTextColor(kBlack); 
        lEq64->Draw();
        
    }
    
}

void QHHLA_SoftEdu::DrawMatrix_Step6(Int_t microStep){
    
    //? Rendering step 6.5: Initial State of Ancilla Qubit
    if (microStep >= 5) {
        
        TString S65title = TString::Format(
            "#font[62]{#color[600]{6.5. Initial State of Ancilla Qubit:}} "
            "The ancilla qubit starts in the computational basis state |0#GT_{A}"
        );
        TLatex *lTitleS65 = new TLatex(0.02, 0.75, S65title.Data());
        lTitleS65->SetNDC();          
        lTitleS65->SetTextFont(42);   
        lTitleS65->SetTextSize(0.040);
        lTitleS65->SetTextColor(kGray+3);
        lTitleS65->Draw();

        TString eq65 = TString::Format(
            "|0#GT_{A} = #left[ #scale[0.7]{#splitline{1}{0} #right]}"
        );
        TLatex *lEq65 = new TLatex(0.04, 0.65, eq65.Data()); 
        lEq65->SetNDC();
        lEq65->SetTextFont(132);     
        lEq65->SetTextSize(0.06);
        lEq65->SetTextColor(kBlack); 
        lEq65->Draw();
    }

    //? Rendering step 6.6: Standard Rotation Matrix Ry(θj)
    if (microStep >= 6) {
        
        TString S66title = TString::Format(
            "#font[62]{#color[600]{6.6. Standard Rotation Matrix R_{y}(#theta#scale[0.7]{j}):}} "
            "This is a unitary matrix that performs a rotation by angle #theta_{j} around the Y-axis."
        );
        TLatex *lTitleS66 = new TLatex(0.02, 0.55, S66title.Data());
        lTitleS66->SetNDC();          
        lTitleS66->SetTextFont(42);   
        lTitleS66->SetTextSize(0.040);
        lTitleS66->SetTextColor(kGray+3);
        lTitleS66->Draw();

        TString eq66 = TString::Format(
            "R_{y}(#theta#scale[0.7]{j}) = "
            "#left[ #scale[0.7]{#splitline{cos(#theta#scale[0.7]{j}/2)}{sin(#theta#scale[0.7]{j}/2)}"
            "  #splitline{-sin(#theta#scale[0.7]{j}/2)}{ cos(#theta#scale[0.7]{j}/2)}} #right] "
        );
        TLatex *lEq66 = new TLatex(0.04, 0.45, eq66.Data()); 
        lEq66->SetNDC();
        lEq66->SetTextFont(132);     
        lEq66->SetTextSize(0.06);
        lEq66->SetTextColor(kBlack); 
        lEq66->Draw();
    }

    //? Rendering step 6.7: Matrix Multiplication Ry(θj)|0⟩_A
    if (microStep >= 7) {
        
        TString S67title = TString::Format(
            "#font[62]{#color[600]{6.7. Applying Rotation to Ancilla:}} "
            "Performing the matrix multiplication."
        );
        TLatex *lTitleS67 = new TLatex(0.02, 0.35, S67title.Data());
        lTitleS67->SetNDC();          
        lTitleS67->SetTextFont(42);   
        lTitleS67->SetTextSize(0.040);
        lTitleS67->SetTextColor(kGray+3);
        lTitleS67->Draw();

        TString eq67 = TString::Format(
            "R_{y}(#theta#scale[0.7]{j})|0#GT_{A} = "
            "#left[ #scale[0.7]{#splitline{cos(#theta#scale[0.7]{j}/2)}{sin(#theta#scale[0.7]{j}/2)}"
            "  #splitline{-sin(#theta#scale[0.7]{j}/2)}{ cos(#theta#scale[0.7]{j}/2)}} #right] "
            "#left[ #scale[0.7]{#splitline{1}{0} #right]} = "
            "#left[ #scale[0.7]{#splitline{cos(#theta#scale[0.7]{j}/2)}{sin(#theta#scale[0.7]{j}/2)} #right]} = "
            "#scale[0.7]{cos#left(#frac{#theta#scale[0.7]{j}}{2}#right)|0#GT_{A} + sen#left(#frac{#theta#scale[0.7]{j}}{2}#right)|1#GT_{A}}"
        );
        TLatex *lEq67 = new TLatex(0.04, 0.25, eq67.Data()); 
        lEq67->SetNDC();
        lEq67->SetTextFont(132);     
        lEq67->SetTextSize(0.06);
        lEq67->SetTextColor(kBlack); 
        lEq67->Draw();
    }
    
}

void QHHLA_SoftEdu::DrawCircuit_Step6(Int_t microStep){

    // Position parameters
    Double_t xStart = 0.05;        // Start of the lines
    Double_t xEnd = 0.95;          // End of the lines
    Double_t yIndex = 0.75;        // Position Y of the Index record (top)
    Double_t yAncilla = 0.20;      // Y position of the Ancilla qubit (lower)
    Double_t yClockStart = 0.65;   // Clock bus start
    Double_t yClockSpacing = 0.10; // Space between clock qubits

    // Gate dimensions (Hadamard)
    Double_t hGateX1 = 0.07;
    Double_t hGateX2 = 0.11;
    Double_t hGateHalfHeight = 0.04;
    
    // Gate dimensions (Controlled-U)
    Double_t uGateWidth = 0.10;
    Double_t uGateHeight = 0.08;
    Double_t uGateXStart = 0.13;   // Starting X position for U gates
    Double_t uGateSpacing = 0.12;  // Spacing between U gates
    
    //? Rendering step 6.8: Circuit Diagram step 4
    if (microStep >= 8) {

        // TOP LINE: Memory/Index Register
        TLine *lineIndex = new TLine(xStart, yIndex, xEnd, yIndex);
        lineIndex->SetLineWidth(2);
        lineIndex->SetLineColor(kBlue+3);
        lineIndex->Draw();
        
        // Initial state |0⟩ for index record
        TLatex *stateIndex = new TLatex(xStart - 0.035, yIndex-0.015, "|b#GT_{I}");
        stateIndex->SetNDC();
        stateIndex->SetTextFont(62);
        stateIndex->SetTextSize(0.05);
        stateIndex->SetTextColor(kBlue+3);
        stateIndex->Draw();
        
        // CENTRAL LINES: Clock Register m-qubit bus
        for (Int_t i = 0; i < fClockQubitsM; i++) {
            Double_t yClock = yClockStart - (i * yClockSpacing);
            
            TLine *lineClock = new TLine(xStart, yClock, xEnd, yClock);
            lineClock->SetLineWidth(2);
            lineClock->SetLineColor(kGreen+3);
            lineClock->Draw();
            
            // Initial state |0⟩ for each qubit of the clock
            TLatex *stateClock = new TLatex(xStart - 0.035, yClock - 0.015, "|0#GT_{C}");
            stateClock->SetNDC();
            stateClock->SetTextFont(62);
            stateClock->SetTextSize(0.05);
            stateClock->SetTextColor(kGreen+3);
            stateClock->Draw();

            if (microStep >= 9) {

                // Background box for the gate
                TBox *hBox = new TBox(hGateX1, yClock - hGateHalfHeight, hGateX2, yClock + hGateHalfHeight);
                hBox->SetFillColor(kCyan-10);
                hBox->SetLineColor(kCyan+4);
                hBox->SetLineWidth(1.5);
                hBox->Draw("l");
                
                // Letter 'H' inside the box
                TLatex *hText = new TLatex((hGateX1 + hGateX2)/2.0, yClock, "H");
                hText->SetTextAlign(22);
                hText->SetTextFont(62);
                hText->SetTextSize(0.06);
                hText->SetTextColor(kCyan+4);
                hText->Draw();

            }

        }
        
        // BOTTOM LINE: Qubit Ancilla
        TLine *lineAncilla = new TLine(xStart, yAncilla, xEnd, yAncilla);
        lineAncilla->SetLineWidth(2);
        lineAncilla->SetLineColor(kCyan+3);
        lineAncilla->Draw();
        
        // Initial state |0⟩ for the ancilla
        TLatex *stateAncilla = new TLatex(xStart - 0.035, yAncilla - 0.015, "|0#GT_{A}");
        stateAncilla->SetNDC();
        stateAncilla->SetTextFont(62);
        stateAncilla->SetTextSize(0.05);
        stateAncilla->SetTextColor(kCyan+3);
        stateAncilla->Draw();
        
        //? Rendering step 6.10: Controlled-U operations
        if (microStep >= 10) {

            // Draw controlled-U gates for each clock qubit
            for (Int_t i = 0; i < fClockQubitsM; i++) {
                Double_t yClock = yClockStart - (i * yClockSpacing);
                Double_t uGateX = uGateXStart + (i * uGateSpacing);
                
                // Calculate the power: 2^i
                Int_t power = TMath::Power(2, i);
                
                // Draw control dot on clock qubit line
                TMarker *controlDot = new TMarker(uGateX + uGateWidth/2.0, yClock, 20);
                controlDot->SetMarkerSize(1.5);
                controlDot->SetMarkerColor(kBlue+4);
                controlDot->SetMarkerStyle(20);
                controlDot->Draw();
                
                // Draw vertical line from control to U gate
                TLine *controlLine = new TLine(uGateX + uGateWidth/2.0, yClock, 
                    uGateX + uGateWidth/2.0, yIndex);
                controlLine->SetLineWidth(1);
                controlLine->SetLineColor(kBlue+4);
                controlLine->Draw();
                
                // Draw U gate box on index register line
                TBox *uBox = new TBox(uGateX, yIndex - uGateHeight/2.0, 
                    uGateX + uGateWidth, yIndex + uGateHeight/2.0);
                uBox->SetFillColor(kBlue-10);
                uBox->SetLineColor(kBlue+4);
                uBox->SetLineWidth(1.5);
                uBox->Draw("l");
                
                // Label U gate with power notation
                TString uLabel;
                if (i == 0) {
                    uLabel = "U^{2^{0}}=e^{iA#tau(1)}";
                } else if (i == 1) {
                    uLabel = "U^{2^{1}}=e^{iA#tau(2)}";
                } else {
                    uLabel = TString::Format("U^{2^{%d}}=e^{iA#tau(%d)}", i, power);
                }
                
                TLatex *uText = new TLatex(uGateX + uGateWidth/2.0, yIndex, uLabel);
                uText->SetTextAlign(22);
                uText->SetTextFont(42);
                uText->SetTextSize(0.05);
                uText->SetTextColor(kBlue+4);
                uText->Draw();
    
            }
        }
        
        //? Rendering step 6.11: IQFT box at the end of clock register lines
        if (microStep >= 11) {

            // Calculate bounds for the IQFT box spanning all clock qubits
            Double_t yClockTop = yClockStart + hGateHalfHeight;      // Top of first clock qubit line
            Double_t yClockBottom = yClockStart - ((fClockQubitsM - 1) * yClockSpacing) - hGateHalfHeight; // Bottom of last clock qubit line
            
            // Calculate end position of last Controlled-U gate
            Int_t lastUIndex = fClockQubitsM - 1;
            Double_t lastUGateX = uGateXStart + (lastUIndex * uGateSpacing);
            Double_t uGatesEndX = lastUGateX + uGateWidth;
            
            Double_t iqftWidth = 0.05;
            Double_t xIQFT = uGatesEndX + 0.02;  // Small gap after last U gate
            Double_t xIQFTEnd = xIQFT + iqftWidth;
            
            // Draw IQFT box spanning all clock register lines
            TBox *iqftBox = new TBox(xIQFT, yClockBottom, xIQFTEnd, yClockTop);
            iqftBox->SetFillColor(kViolet-9);
            iqftBox->SetLineColor(kViolet+3);
            iqftBox->SetLineWidth(1.5);
            iqftBox->Draw("l");
            
            // Vertical "IQFT" label 
            TLatex *iqftLabel = new TLatex(xIQFT + iqftWidth/2.0, (yClockTop + yClockBottom)/2.0, "IQFT");
            iqftLabel->SetTextAlign(22);
            iqftLabel->SetTextFont(62);
            iqftLabel->SetTextSize(0.05);
            iqftLabel->SetTextColor(kViolet+3);
            iqftLabel->SetTextAngle(90);  // Vertical text
            iqftLabel->Draw();
            
            // QPE dashed bracket: from H gates to IQFT, covering H + U gates + IQFT vertically
            Double_t xQPE_Left = hGateX1;
            Double_t xQPE_Right = xIQFTEnd;
            
            // Vertical bounds: from top of U gates on index register to bottom of clock register
            Double_t yQPE_Top = yIndex + uGateHeight/2.0 + 0.02;     // Top of U gates on index line
            Double_t yQPE_Bottom = yClockBottom - 0.02;               // Bottom of last clock line
            
            // Draw dashed bracket (no fill, dashed lines)
            // Top edge - dashed
            TLine *qpeTop = new TLine(xQPE_Left, yQPE_Top, xQPE_Right, yQPE_Top);
            qpeTop->SetLineColor(kOrange+3);
            qpeTop->SetLineWidth(2);
            qpeTop->SetLineStyle(2);  // Dashed line
            qpeTop->Draw();
            
            // Bottom edge - dashed
            TLine *qpeBottom = new TLine(xQPE_Left, yQPE_Bottom, xQPE_Right, yQPE_Bottom);
            qpeBottom->SetLineColor(kOrange+3);
            qpeBottom->SetLineWidth(2);
            qpeBottom->SetLineStyle(2);  // Dashed line
            qpeBottom->Draw();
            
            // Left edge - dashed
            TLine *qpeLeft = new TLine(xQPE_Left, yQPE_Top, xQPE_Left, yQPE_Bottom);
            qpeLeft->SetLineColor(kOrange+3);
            qpeLeft->SetLineWidth(2);
            qpeLeft->SetLineStyle(2);  // Dashed line
            qpeLeft->Draw();
            
            // Right edge - dashed
            TLine *qpeRight = new TLine(xQPE_Right, yQPE_Top, xQPE_Right, yQPE_Bottom);
            qpeRight->SetLineColor(kOrange+3);
            qpeRight->SetLineWidth(2);
            qpeRight->SetLineStyle(2);  // Dashed line
            qpeRight->Draw();
            
            // QPE label at the center of the bottom edge
            TLatex *qpeLabel = new TLatex((xQPE_Left + xQPE_Right)/2.0, yQPE_Bottom - 0.015, "QPE");
            qpeLabel->SetTextAlign(23);  // Centered, bottom-aligned
            qpeLabel->SetTextFont(62);
            qpeLabel->SetTextSize(0.05);
            qpeLabel->SetTextColor(kOrange+3);
            qpeLabel->Draw();

            //? Rendering step 6.12: Controlled-Ry(θ) gate converging from all clock qubits to ancilla
            if (microStep >= 12) {

                // Calculate X position for the Ry gate: placed after the IQFT box with a small gap
                Double_t xRyGate = xIQFTEnd;
                Double_t ryGateWidth = 0.10;
                
                // Draw control dots on each clock qubit line and vertical lines converging to ancilla
                for (Int_t i = 0; i < fClockQubitsM; i++) {
                    Double_t yClock = yClockStart - (i * yClockSpacing);
                    
                    // Draw control dot on clock qubit line at the Ry gate X position
                    TMarker *ryControlDot = new TMarker(xRyGate + ryGateWidth/2.0, yClock, 20);
                    ryControlDot->SetMarkerSize(1.5);
                    ryControlDot->SetMarkerColor(kRed+3);
                    ryControlDot->SetMarkerStyle(20);
                    ryControlDot->Draw();
                    
                    // Draw vertical line from control dot down to the ancilla line
                    TLine *ryControlLine = new TLine(xRyGate + ryGateWidth/2.0, yClock, 
                        xRyGate + ryGateWidth/2.0, yAncilla);
                    ryControlLine->SetLineWidth(1.5);
                    ryControlLine->SetLineColor(kRed+3);
                    ryControlLine->SetLineStyle(1);
                    ryControlLine->Draw();
                }
                
                // Draw the Ry(θ) gate box on the ancilla line
                Double_t yRyTop = yAncilla + 0.04;      // Extend slightly above top ancilla line
                Double_t yRyBottom = yAncilla - 0.04;   // Extend slightly below ancilla line
                
                TBox *ryBox = new TBox(xRyGate, yRyBottom, xRyGate + ryGateWidth, yRyTop);
                ryBox->SetFillColor(kRed-10);
                ryBox->SetLineColor(kRed+3);
                ryBox->SetLineWidth(1.5);
                ryBox->Draw("l");
                
                // Label Ry(θ) inside the box
                TLatex *ryText = new TLatex(xRyGate + ryGateWidth/2.0, (yRyTop + yRyBottom)/2.0, "R_{y}(#theta)");
                ryText->SetTextAlign(22);
                ryText->SetTextFont(62);
                ryText->SetTextSize(0.05);
                ryText->SetTextColor(kRed+3);
                ryText->Draw();
                
            }

        }

    }

}

void QHHLA_SoftEdu::DrawGraph_Step6(Int_t microStep){

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    if (!c) return;
    c->cd();
    c->Clear();

    if (gGeoManager) {
        delete gGeoManager; // Global Memory Cleanup
        gGeoManager = nullptr;
    }

    //? TITLE AND PROGRESS BAR (Main Canvas) ----------------------------------
    DrawStepTitle(c);
    DrawProgressBar(c);

    //? Only two visual states: the ancilla resting at |0>_A, and then each
    //  eigenvalue branch rotated by its own angle theta_j.
    Bool_t isRotated = (microStep >= 14);

    Double_t theta1Deg = fThetaAngles(0) * TMath::RadToDeg(); // polar angle from +Z toward +X
    Double_t theta2Deg = fThetaAngles(1) * TMath::RadToDeg();

    Double_t angle1 = isRotated ? theta1Deg : 0.0;
    Double_t angle2 = isRotated ? theta2Deg : 0.0; 

    //? Two pads, one 3D Bloch sphere per eigenvalue branch --------------------
    TPad *padL = new TPad("padBlochL_S6", "Bloch Sphere Lambda1", 0.02, 0.08, 0.50, 0.88);
    padL->SetFillColor(0);
    padL->Draw();

    TPad *padR = new TPad("padBlochR_S6", "Bloch Sphere Lambda2", 0.50, 0.08, 0.98, 0.88);
    padR->SetFillColor(0);
    padR->Draw();

    //? 3D geometry 
    TGeoManager  *geom   = new TGeoManager("geomStep6", "Bloch");
    TGeoMaterial *vacuum = new TGeoMaterial("vacuum", 0, 0, 0);
    TGeoMaterial *Fe     = new TGeoMaterial("Fe", 55.845, 26, 7.87);
    TGeoMedium   *Air    = new TGeoMedium("Vacuum", 0, vacuum);
    TGeoMedium   *Iron   = new TGeoMedium("Iron", 1, Fe);

    // Sphere surface (Radio inicial de 100)
    TGeoVolume *sphL = geom->MakeSphere("sphA", Iron, 0, 100, 0, 180, 0, 360);
    sphL->SetLineColorAlpha(kAzure-9, 0.15);
    sphL->SetFillColorAlpha(kAzure-9, 0.10);

    TGeoVolume *sphR = geom->MakeSphere("sphB", Iron, 0, 100, 0, 180, 0, 360);
    sphR->SetLineColorAlpha(kAzure-9, 0.15);
    sphR->SetFillColorAlpha(kAzure-9, 0.10);

    // Reference axes X, Y, Z (Semilongitud 110)
    TGeoVolume *axX = geom->MakeTube("axX", Iron, 0, 1, 110); axX->SetLineColor(kGray+1);
    TGeoVolume *axY = geom->MakeTube("axY", Iron, 0, 1, 110); axY->SetLineColor(kGray+1);
    TGeoVolume *axZ = geom->MakeTube("axZ", Iron, 0, 1, 110); axZ->SetLineColor(kGray+1);

    // Ancilla vector
    TGeoVolume *shaft1 = geom->MakeTube("shaft1", Iron, 0, 1, 40);
    TGeoVolume *shaft2 = geom->MakeTube("shaft2", Iron, 0, 1, 40);
    
    TGeoVolume *head1  = geom->MakeCone("head1", Iron, 10, 0, 10, 0, 0);
    TGeoVolume *head2  = geom->MakeCone("head2", Iron, 10, 0, 10, 0, 0);

    shaft1->SetLineColor(kRed);
    shaft1->SetFillColor(kRed);
    shaft1->SetLineWidth(4);

    head1->SetLineColor(kRed);
    head1->SetFillColor(kRed);

    shaft2->SetLineColor(kRed);
    shaft2->SetFillColor(kRed);
    shaft2->SetLineWidth(4);

    head2->SetLineColor(kRed);
    head2->SetFillColor(kRed);

    if (microStep >= 13) {

        // ----- LEFT VOLUME: lambda1 branch -----
            TGeoVolume *topL = geom->MakeBox("topL", Air, 140, 140, 140);
            topL->SetVisibility(0);
            topL->AddNodeOverlap(sphL, 1, new TGeoRotation("r0",  0, 0, 0));
            topL->AddNodeOverlap(axX,  1, new TGeoRotation("rx",  0, 90, 0));
            topL->AddNodeOverlap(axY,  1, new TGeoRotation("ry", 90, 90, 0));
            topL->AddNodeOverlap(axZ,  1, new TGeoRotation("rz",  0, 0, 0));

            // Left Assembly
            TGeoVolumeAssembly *arrow1 = new TGeoVolumeAssembly("arrow1");
        
            // The tube ranges from -40 to 40. We shift it by +40 so that it starts at 0 and ends at 80.
            arrow1->AddNode(shaft1, 1, new TGeoTranslation(0, 0, 40));

            // The cone ranges from -10 to 10. We center it at 90 so that it starts at 80 and ends at 100.
            arrow1->AddNode(head1, 1, new TGeoTranslation(0, 0, 90));

            // Rotation and anchoring
            TGeoRotation *rot1 = new TGeoRotation("rotArrow1", 0, angle1, 0);
            topL->AddNode(arrow1, 1, rot1);


        // ----- RIGHT VOLUME: lambda2 branch -----
            TGeoVolume *topR = geom->MakeBox("topR", Air, 140, 140, 140);
            topR->SetVisibility(0);
            topR->AddNodeOverlap(sphR, 1, new TGeoRotation("r0b", 0, 0, 0));
            topR->AddNodeOverlap(axX,  1, new TGeoRotation("rxb", 0, 90, 0));
            topR->AddNodeOverlap(axY,  1, new TGeoRotation("ryb",90, 90, 0));
            topR->AddNodeOverlap(axZ,  1, new TGeoRotation("rzb", 0, 0, 0));

            // Right Assembly
            TGeoVolumeAssembly *arrow2 = new TGeoVolumeAssembly("arrow2");
    
            arrow2->AddNode(shaft2, 1, new TGeoTranslation(0, 0, 40));
            arrow2->AddNode(head2, 1, new TGeoTranslation(0, 0, 90));

            // Rotation and anchoring
            TGeoRotation *rot2 = new TGeoRotation("rotArrow2", 0, angle2, 0);
            topR->AddNode(arrow2, 1, rot2);

            geom->SetTopVolume(topL); 
            geom->CloseGeometry();

        // Function to draw quantum labels
        auto DrawQuantumLabels = []() {
            TLatex *l;
            // North Pole (|0>)
            l = new TLatex(0.50, 0.80, "|0#GT"); 
            l->SetNDC();
            l->SetTextAlign(22);
            l->SetTextSize(0.05);
            l->Draw();
            // South Pole (|1>)
            l = new TLatex(0.50, 0.20, "|1#GT");
            l->SetNDC();
            l->SetTextAlign(22);
            l->SetTextSize(0.05);
            l->Draw();
        };

        //? Draw LEFT sphere: lambda1 branch ---------------------------------------
        padL->cd();
        topL->Draw(); 
        
        DrawQuantumLabels(); 

        TLatex *lblL = new TLatex(0.05, 0.85, "#color[834]{#bf{#lambda_{1} branch}}");
        lblL->SetNDC(); 
        lblL->SetTextSize(0.06); 
        lblL->Draw();

        TLatex *stateL = !isRotated
            ? new TLatex(0.25, 0.04, "|0#GT_{A}  (before rotation)")
            : new TLatex(0.25, 0.04, TString::Format("R_{y}(#theta_{1})|0#GT_{A}, #theta_{1} = %.2f#circ", theta1Deg));
        stateL->SetNDC(); 
        stateL->SetTextSize(0.05); 
        stateL->SetTextColor(kTeal-6); 
        stateL->Draw();
        padL->Modified();

        //? Draw RIGHT sphere: lambda2 branch ---------------------------------------
        padR->cd();
        topR->Draw(); 
        
        DrawQuantumLabels(); 

        TLatex *lblR = new TLatex(0.05, 0.85, "#color[804]{#bf{#lambda_{2} branch}}");
        lblR->SetNDC();
        lblR->SetTextSize(0.06);
        lblR->Draw();

        TLatex *stateR = !isRotated
            ? new TLatex(0.25, 0.04, "|0#GT_{A}  (before rotation)")
            : new TLatex(0.25, 0.04, TString::Format("R_{y}(#theta_{2})|0#GT_{A}, #theta_{2} = %.2f#circ", theta2Deg));
        stateR->SetNDC();
        stateR->SetTextSize(0.05);
        stateR->SetTextColor(kOrange+4);
        stateR->Draw();
        padR->Modified();

    }

    c->cd();
    c->Modified();
    c->Update();

}

//* MODULAR METHODS: STEP 7 (Uncomputing / IQPE) ------------------------------
void QHHLA_SoftEdu::DrawMath_Step7(Int_t microStep){

    Int_t num1 = (fLambda1*fLambda1)-(fC*fC);
    Int_t num2 = (fLambda2*fLambda2)-(fC*fC);

    TString b1Str = FormatComplex(fbetaNum1);
    TString b2Str = FormatComplex(fbetaNum2);
    TString sign1, val1, sign2, val2;
    DecomposeSign(b1Str, sign1, val1);
    DecomposeSign(b2Str, sign2, val2);

    std::string ceros_std(fClockQubitsM, '0'); 
    TString ceros(ceros_std.c_str());
    
    //? Rendering step 7.1: Anatomy of the U_IQPE Operator
    if (microStep >= 1) {

        TString S71title = TString::Format(
            "#font[62]{#color[600]{7.1. Anatomy of the #hat{U}_{IQPE} Operator:}} "
            "The uncomputing is the inverse of the operations performed in steps 3, 4, and 5."
        );
        TLatex *lTitleS71 = new TLatex(0.02, 0.80, S71title.Data());
        lTitleS71->SetNDC();          
        lTitleS71->SetTextFont(42);   
        lTitleS71->SetTextSize(0.040);
        lTitleS71->SetTextColor(kGray+3);
        lTitleS71->Draw();

        TString eq71 = TString::Format(
            "\\hat{U}_{IQPE} = (H^{\\otimes m})^{\\dagger} \\cdot (cU)^{\\dagger} \\cdot (IQFT)^{\\dagger}"
            "= H^{\\otimes m} \\cdot cU^{-1} \\cdot QFT"
        );
        TLatex *lEq71 = new TLatex(0.04, 0.70, eq71.Data()); 
        lEq71->SetNDC();
        lEq71->SetTextFont(152);     
        lEq71->SetTextSize(0.05);
        lEq71->SetTextColor(kBlack); 
        lEq71->Draw();
        
    }
    
    //? Rendering step 7.2: Mathematical Unraveling - Action on |₄⟩
    if (microStep >= 2) {

        TString S72title = TString::Format(
            "#font[62]{#color[600]{7.2. Mathematical Unraveling:}} "
            "Action of #hat{U}_{IQPE} on |#Psi_{4}#GT"
        );
        TLatex *lTitleS72 = new TLatex(0.02, 0.60, S72title.Data());
        lTitleS72->SetNDC();          
        lTitleS72->SetTextFont(42);   
        lTitleS72->SetTextSize(0.040);
        lTitleS72->SetTextColor(kGray+3);
        lTitleS72->Draw();
        
        TString eq72 = TString::Format(
            "#hat{U}_{IQPE} |#Psi_{4}#GT = #hat{U}_{IQPE} #left[ #frac{%s}{#sqrt{%.0f}} #color[635]{|%s#GT_{C}} |u_{1}#GT_{I} "
            "#left( #frac{#sqrt{%i}}{%.2f} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A} #right)"
            " %s #frac{%s}{#sqrt{%.0f}} #color[635]{|%s#GT_{C}} |u_{2}#GT_{I} "
            "#left( #frac{#sqrt{%i}}{%.2f} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A} #right) #right]", 
            b1Str.Data(), fIntDenomSq, fBinLambda1.Data(), num1, fLambda1, fC, fLambda1,  
            sign2.Data(), val2.Data(), fIntDenomSq, fBinLambda2.Data(), num2, fLambda2, fC, fLambda2
        );
        TLatex *lEq72 = new TLatex(0.04, 0.50, eq72.Data()); 
        lEq72->SetNDC();
        lEq72->SetTextFont(132);     
        lEq72->SetTextSize(0.05);
        lEq72->SetTextColor(kBlack); 
        lEq72->Draw();

        TString S72desc = "#color[2]{#rightarrow}  The IQPE reverses the phase encoding, returning the clock register to |0#GT^{#otimesm}_{C}:";
        TLatex *lDescS72 = new TLatex(0.07, 0.40, S72desc.Data());
        lDescS72->SetNDC();
        lDescS72->SetTextFont(42);
        lDescS72->SetTextSize(0.040);
        lDescS72->SetTextColor(kRed+3);
        lDescS72->Draw();
        
    }
    
    //? Rendering step 7.3: Resulting State |Ψ₅⟩
    if (microStep >= 3) {

        TString S73titleDesc = "#font[62]{#color[600]{7.3. Resulting Global State |#Psi_{5}#GT:}}";
        TLatex *lTitleS73 = new TLatex(0.02, 0.30, S73titleDesc.Data());
        lTitleS73->SetNDC();
        lTitleS73->SetTextFont(42);
        lTitleS73->SetTextSize(0.040);
        lTitleS73->SetTextColor(kGray+3);
        lTitleS73->Draw();

        TString eq73 = TString::Format(
            "|#Psi_{5}#GT =  #color[419]{|%s#GT_{C}} #otimes #left[ #frac{%s}{#sqrt{%.0f}} |u_{1}#GT_{I} "
            "#left( #frac{#sqrt{%i}}{%.2f} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A} #right)"
            " %s #frac{%s}{#sqrt{%.0f}} |u_{2}#GT_{I} "
            "#left( #frac{#sqrt{%i}}{%.2f} |0#GT_{A} + #frac{%.0f}{%.2f} |1#GT_{A} #right) #right]", 
            ceros.Data(), b1Str.Data(), fIntDenomSq, num1, fLambda1, fC, fLambda1,  
            sign2.Data(), val2.Data(), fIntDenomSq, num2, fLambda2, fC, fLambda2
        );
        TLatex *lEq73 = new TLatex(0.04, 0.20, eq73.Data()); 
        lEq73->SetNDC();
        lEq73->SetTextFont(132);     
        lEq73->SetTextSize(0.05);
        lEq73->SetTextColor(kBlack); 
        lEq73->Draw();
        
    }

}

void QHHLA_SoftEdu::DrawMatrix_Step7(Int_t microStep){

    Int_t totalStates = TMath::Power(2, fClockQubitsM);
    Int_t lim_t = totalStates - 1;

    //? Rendering step 7.4: Inverse Hadamard Matrix H^{-1}
    if (microStep >= 4 && microStep < 6) {

        TString S74titleDesc = "#font[62]{#color[600]{7.4. Inverse Hadamard Matrix H^{-1}:}} "
            "Since H is Hermitian and unitary, H^{-1} = H.";
        TLatex *lTitleS74 = new TLatex(0.02, 0.83, S74titleDesc.Data());
        lTitleS74->SetNDC();
        lTitleS74->SetTextFont(42);
        lTitleS74->SetTextSize(0.040);
        lTitleS74->SetTextColor(kGray+3);
        lTitleS74->Draw();

        // Global inverse Hadamard operator
        TString kronecker = "H^{-1#otimesm} = H^{#otimesm} = ";
        for(Int_t i = 0; i < fClockQubitsM; i++) {
            if(i > 0) kronecker += " #otimes ";
            kronecker += "H^{-1}";
        }

        TLatex *lEqS74b = new TLatex(0.08, 0.73, kronecker.Data());
        lEqS74b->SetNDC();
        lEqS74b->SetTextFont(132);
        lEqS74b->SetTextSize(0.055);
        lEqS74b->SetTextColor(kBlack);
        lEqS74b->Draw();

        TString explanation = TString::Format(
            "#color[2]{#rightarrow} #color[419]{Applied on m = %d clock qubits to reverse the superposition}",
            fClockQubitsM
        );
        TLatex *lExpS74 = new TLatex(0.40, 0.73, explanation.Data());
        lExpS74->SetNDC();
        lExpS74->SetTextFont(42);
        lExpS74->SetTextSize(0.045);
        lExpS74->SetTextColor(kGray+2);
        lExpS74->Draw();

        // Draw the expanded Walsh-Hadamard matrix (same as step 3.6)
        if (fClockQubitsM > 4) {
            TLatex *lWarn = new TLatex(0.20, 0.50, "#color[2]{[Matrix too large to display on screen]}");
            lWarn->SetNDC();
            lWarn->SetTextFont(42);
            lWarn->SetTextSize(0.04);
            lWarn->SetTextColor(kRed+2);
            lWarn->Draw();
        } else {
            Int_t dim = totalStates;
            Double_t centerY = 0.52; 
            Double_t startX = 0.30;
            Double_t stepX = 0.02;
            Double_t stepY = 0.02;
            Int_t textSize = 0;

            if (dim == 2) { stepX = 0.10; stepY = 0.10; textSize = 60; centerY = 0.32; }
            if (dim == 4) { stepX = 0.08; stepY = 0.08; textSize = 50; }
            if (dim == 8) { stepX = 0.05; stepY = 0.05; textSize = 42; }
            if (dim == 16){ stepX = 0.035; stepY = 0.015; textSize = 20; startX = 0.25; centerY = 0.18; }

            Double_t b_top = centerY + (dim * stepY) / 2.0;
            Double_t b_bot = centerY - (dim * stepY) / 2.0;

            // Draw external normalization fraction
            TString norm = TString::Format("H^{%d} = #frac{1}{#sqrt{%d}}", fClockQubitsM, dim);
            TLatex *lNorm = new TLatex(0.18, centerY, norm.Data());
            lNorm->SetNDC();
            lNorm->SetTextAlign(22);
            lNorm->SetTextFont(132);
            lNorm->SetTextSize(0.055);
            lNorm->SetTextColor(kBlack);
            lNorm->Draw();

            // Matrix generation via bit manipulation (same as H, since H^{-1} = H)
            for (Int_t r = 0; r < dim; ++r) {
                for (Int_t col = 0; col < dim; ++col) {
                    Int_t bitwiseAnd = r & col;
                    Int_t count = 0;
                    while (bitwiseAnd > 0) {
                        count += (bitwiseAnd & 1);
                        bitwiseAnd >>= 1;
                    }

                    Double_t x = startX + col * stepX;
                    Double_t y = b_top - (r + 0.5) * stepY;

                    if (count % 2 == 0) {
                        TLatex *lPos = new TLatex(x, y, "#color[4]{1}");
                        lPos->SetNDC();
                        lPos->SetTextAlign(22);
                        lPos->SetTextFont(42);
                        lPos->SetTextSize(textSize * 0.001);
                        lPos->Draw();
                    } else {
                        TLatex *lNeg = new TLatex(x, y, "#color[2]{-1}");
                        lNeg->SetNDC();
                        lNeg->SetTextAlign(22);
                        lNeg->SetTextFont(42);
                        lNeg->SetTextSize(textSize * 0.001);
                        lNeg->Draw();
                    }
                }
            }

            // Draw brackets
            TLine *lineLeft = new TLine();
            lineLeft->SetLineWidth(2);
            Double_t b_left = startX - stepX/2.0;
            Double_t b_right = startX + (dim - 1)*stepX + stepX/2.0;

            lineLeft->DrawLine(b_left, b_top, b_left, b_bot);
            lineLeft->DrawLine(b_left, b_top, b_left+0.01, b_top);
            lineLeft->DrawLine(b_left, b_bot, b_left+0.01, b_bot);

            lineLeft->DrawLine(b_right, b_top, b_right, b_bot);
            lineLeft->DrawLine(b_right, b_top, b_right-0.01, b_top);
            lineLeft->DrawLine(b_right, b_bot, b_right-0.01, b_bot);

        }

    }

    //? Rendering step 7.5: Inverse Unitary Evolution Matrix U^{-1}
    if (microStep == 5) {

        TString S75title = TString::Format(
            "#font[62]{#color[600]{7.5. Inverse Unitary Evolution Matrix U^{-1}:}} "
            "The inverse of #hat{U} = e^{iA#tau} is #hat{U}^{-1} = e^{-iA#tau}."
        );
        TLatex *lTitleS75 = new TLatex(0.02, 0.26, S75title.Data());
        lTitleS75->SetNDC();          
        lTitleS75->SetTextFont(42);   
        lTitleS75->SetTextSize(0.040);
        lTitleS75->SetTextColor(kGray+3);
        lTitleS75->Draw();

        // U^{-1} is diagonal in eigenbasis with negative phases
        TString eq75 = TString::Format(
            "#hat{U}^{-1} = #left[ #splitline{#color[834]{#scale[1.5]{e}^{-i(%.2f)#tau}}}{    0  }   "
            "#splitline{    0  }{#color[804]{#scale[1.5]{e}^{-i(%.2f)#tau}}} #right]"
            "  #color[2]{#rightarrow} "
            "#scale[0.7]{#font[42]{#color[635]{Each diagonal entry has the NEGATIVE phase of the original U.}}}",
            fLambda1, fLambda2
        );
        TLatex *lEqS75 = new TLatex(0.02, 0.16, eq75.Data());
        lEqS75->SetNDC();
        lEqS75->SetTextFont(132);
        lEqS75->SetTextSize(0.060);
        lEqS75->SetTextColor(kBlack);
        lEqS75->Draw();

        // Show the relationship: U^{-1} = U^{dagger}
        TString eq75b = "\\text{Note:} \\hat{U}^{-1} = \\hat{U}^{\\dagger} \\text{since U is unitary} (\\hat{U}^{\\dagger}\\hat{U} = I)";
        TLatex *lEqS75b = new TLatex(0.40, 0.10, eq75b.Data());
        lEqS75b->SetNDC();
        lEqS75b->SetTextFont(152);
        lEqS75b->SetTextSize(0.040);
        lEqS75b->SetTextColor(kGray+3);
        lEqS75b->Draw();

    }

    //? Rendering step 7.6: Quantum Fourier Transform Matrix QFT (inverse of IQFT)
    if (microStep == 6) {

        TString S76titleDesc = TString::Format(
            "#font[62]{#color[600]{7.6. Quantum Fourier Transform Matrix QFT (%d#times%d):}} "
            "The QFT is the inverse of the IQFT.",
            totalStates, totalStates);
        TLatex *lTitleS76 = new TLatex(0.02, 0.82, S76titleDesc.Data());
        lTitleS76->SetNDC();          
        lTitleS76->SetTextFont(42);   
        lTitleS76->SetTextSize(0.040);
        lTitleS76->SetTextColor(kGray+3);
        lTitleS76->Draw();

        // Formula definition: QFT has POSITIVE exponent (vs negative in IQFT)
        TString eq76 = TString::Format(
            "#hat{U}_{QFT}(y,t) = #sum_{t,y=0}^{%i}#frac{1}{#sqrt{%d}} #scale[1.5]{e}^{+2#pi i #frac{yt}{%d}}"
            "  #color[2]{#rightarrow}  #color[635]{Note the + sign in the exponent (vs - in IQFT)}",
            lim_t, totalStates, totalStates
        );
        TLatex *lEqS76 = new TLatex(0.10, 0.72, eq76.Data());
        lEqS76->SetNDC();
        lEqS76->SetTextFont(132);     
        lEqS76->SetTextSize(0.045);
        lEqS76->SetTextColor(kBlack); 
        lEqS76->Draw();

        // Display QFT Matrix elements (same structure as IQFT but with positive phase)
        Double_t startX = 0.30;    
        Double_t startY = 0.55;    
        Double_t cellW = 0.0, cellH = 0.0;
        Int_t textSize = 0;

        if (totalStates <= 2) {       
            cellW = 0.14; cellH = 0.14; textSize = 70;
        } else if (totalStates <= 4) { 
            cellW = 0.10; cellH = 0.10; textSize = 55;
        } else if (totalStates <= 8) { 
            cellW = 0.06; cellH = 0.06; textSize = 35;
        } else {                        
            cellW = 0.04; cellH = 0.04; textSize = 25;
        }

        Double_t matWidth = (totalStates - 1) * cellW + cellW;
        startX = 0.55 - matWidth / 2.0;

        Double_t bLeft = startX - cellW * 0.5;
        Double_t bRight = startX + (totalStates - 1) * cellW + cellW * 0.5;
        Double_t bTop = startY + cellH * 0.5;
        Double_t bBot = startY - (totalStates - 1) * cellH - cellH * 0.5;
        Double_t matCenterY = (bTop + bBot) / 2.0;

        // Matrix label
        TLatex *lMatLabel = new TLatex(0.15, matCenterY, 
            TString::Format("#hat{U}_{QFT} = #frac{1}{#sqrt{%d}}", totalStates));
        lMatLabel->SetNDC();
        lMatLabel->SetTextAlign(22);     
        lMatLabel->SetTextFont(132);
        lMatLabel->SetTextSize(0.060);   
        lMatLabel->SetTextColor(kBlack);
        lMatLabel->Draw();

        // Draw matrix grid with elements (positive phase vs negative in IQFT)
        for (Int_t y = 0; y < totalStates; y++) {
            for (Int_t t = 0; t < totalStates; t++) {
                // QFT: +2π * y * t / N (positive sign!)
                Double_t phase = +2.0 * TMath::Pi() * y * t / (Double_t)totalStates;
                Double_t c = TMath::Cos(phase);
                Double_t s = TMath::Sin(phase);
                const Double_t eps = 1e-10;

                TString elemStr;
                Color_t elemColor = kBlack;

                if (TMath::Abs(c - 1.0) < eps && TMath::Abs(s) < eps) {
                    elemStr = "#color[4]{1}";
                    elemColor = kBlue;
                } else if (TMath::Abs(c + 1.0) < eps && TMath::Abs(s) < eps) {
                    elemStr = "#color[2]{-1}";
                    elemColor = kRed;
                } else if (TMath::Abs(c) < eps && TMath::Abs(s - 1.0) < eps) {
                    elemStr = "#color[419]{i}";
                    elemColor = kGreen+2;
                } else if (TMath::Abs(c) < eps && TMath::Abs(s + 1.0) < eps) {
                    elemStr = "#color[810]{-i}";
                    elemColor = kMagenta;
                } else {
                    if (TMath::Abs(s) < eps) {
                        elemStr = TString::Format("%.1f", c);
                    } else if (TMath::Abs(c) < eps) {
                        elemStr = TString::Format("%.1fi", s);
                    } else {
                        elemStr = TString::Format("%.1f%+.1fi", c, s);
                    }
                    elemColor = kGray+2;
                }

                Double_t xPos = startX + t * cellW;
                Double_t yPos = startY - y * cellH;

                TBox *cellBox = new TBox(xPos - cellW*0.45, yPos - cellH*0.45, 
                                        xPos + cellW*0.45, yPos + cellH*0.45);
                if (y == 0 || t == 0) {
                    cellBox->SetFillColor(kCyan-10); // Different color to distinguish from IQFT
                } else {
                    cellBox->SetFillColor(kWhite);
                }
                cellBox->SetLineColor(kGray+1);
                cellBox->SetLineWidth(1);
                cellBox->Draw("l");

                TLatex *lElem = new TLatex(xPos, yPos, elemStr.Data());
                lElem->SetNDC();
                lElem->SetTextAlign(22);
                lElem->SetTextFont(42);
                lElem->SetTextSize(textSize * 0.001);
                lElem->SetTextColor(elemColor);
                lElem->Draw();

            }

        }

        // Draw brackets
        TLine *lineBrack = new TLine();
        lineBrack->SetLineWidth(3);     

        lineBrack->DrawLine(bLeft, bTop, bLeft, bBot);
        lineBrack->DrawLine(bLeft, bTop, bLeft + 0.010, bTop);
        lineBrack->DrawLine(bLeft, bBot, bLeft + 0.010, bBot);

        lineBrack->DrawLine(bRight, bTop, bRight, bBot);
        lineBrack->DrawLine(bRight, bTop, bRight - 0.010, bTop);
        lineBrack->DrawLine(bRight, bBot, bRight - 0.010, bBot);

        // Row and column labels
        for (Int_t i = 0; i < totalStates; i++) {
            TLatex *lRow = new TLatex(bLeft - 0.020, startY - i * cellH, 
                TString::Format("y=%d", i));
            lRow->SetNDC();
            lRow->SetTextAlign(32);
            lRow->SetTextFont(42);
            lRow->SetTextSize(0.028);   
            lRow->SetTextColor(kGray+2);
            lRow->Draw();
        }

        for (Int_t i = 0; i < totalStates; i++) {
            TLatex *lCol = new TLatex(startX + i * cellW, bTop + 0.03, 
                TString::Format("t=%d", i));
            lCol->SetNDC();
            lCol->SetTextAlign(22);
            lCol->SetTextFont(42);
            lCol->SetTextSize(0.028);
            lCol->SetTextColor(kGray+2);
            lCol->Draw();
        }

        // Comparison note
        TString compNote = "#color[635]{Comparison:} IQFT has e^{-2#pi i yt/N} #color[2]{#rightarrow} QFT has e^{+2#pi i yt/N}";
        TLatex *lComp = new TLatex(0.05, 0.05, compNote.Data());
        lComp->SetNDC();
        lComp->SetTextAlign(12);
        lComp->SetTextFont(42);
        lComp->SetTextSize(0.040);
        lComp->SetTextColor(kGray+2);
        lComp->Draw();

    }

    //? Rendering step 7.7: Combined U_IQPE = H^{-1} · U^{-1} · QFT
    if (microStep >= 7) {

        TString S77titleDesc = "#font[62]{#color[600]{7.7. Combined Matrix Operator #hat{U}_{IQPE}:}} "
            "The full uncomputing operator is the product of the three inverses.";
        TLatex *lTitleS77 = new TLatex(0.02, 0.80, S77titleDesc.Data());
        lTitleS77->SetNDC();
        lTitleS77->SetTextFont(42);
        lTitleS77->SetTextSize(0.040);
        lTitleS77->SetTextColor(kGray+3);
        lTitleS77->Draw();

        // Mathematical property: U_IQPE reverses the QPE
        TString eq77b = "#color[635]{Property:} #hat{U}_{IQPE} #upoint #hat{U}_{QPE} = I  #color[2]{#rightarrow}  "
            "Applying IQPE after QPE returns the clock register to |0#GT^{#otimes m}";
        TLatex *lEqS77b = new TLatex(0.10, 0.72, eq77b.Data());
        lEqS77b->SetNDC();
        lEqS77b->SetTextFont(42);
        lEqS77b->SetTextSize(0.040);
        lEqS77b->SetTextColor(kGray+2);
        lEqS77b->Draw();

        // Visual representation of the product
        TString eq77c = TString::Format(
            "#hat{U}_{IQPE} = #left( #frac{1}{#sqrt{%d}} H_{%d#times%d}^{#otimes m} #right) "
            "#upoint #left[ #splitline{e^{-i%.2f#tau}}{0} #splitline{0}{e^{-i%.2f#tau}} #right] "
            "#upoint #left( #frac{1}{#sqrt{%d}} QFT_{%d#times%d} #right)",
            totalStates, totalStates, totalStates,
            fLambda1, fLambda2,
            totalStates, totalStates, totalStates
        );
        TLatex *lEqS77c = new TLatex(0.05, 0.60, eq77c.Data());
        lEqS77c->SetNDC();
        lEqS77c->SetTextFont(132);
        lEqS77c->SetTextSize(0.060);
        lEqS77c->SetTextColor(kBlack);
        lEqS77c->Draw();

        // Result: U_IQPE effectively returns clock to |0...0>
        TString eq77d = "#color[2]{#rightarrow}  #color[419]{Result:} U_{IQPE} |#lambda_{j}#GT_{C} = |0...0#GT_{C}  "
            "(for any encoded eigenvalue #lambda_{j})";
        TLatex *lEqS77d = new TLatex(0.10, 0.48, eq77d.Data());
        lEqS77d->SetNDC();
        lEqS77d->SetTextFont(42);
        lEqS77d->SetTextSize(0.045);
        lEqS77d->SetTextColor(kGreen+3);
        lEqS77d->Draw();

        // Summary box
        TPaveText *pBox77 = new TPaveText(0.15, 0.10, 0.85, 0.40, "NDC");
        pBox77->SetFillColor(kYellow-9);
        pBox77->SetBorderSize(1);
        pBox77->SetLineColor(kOrange-2);
        pBox77->SetTextAlign(12);
        pBox77->SetTextSize(0.040);
        pBox77->SetTextFont(42);
        pBox77->SetMargin(0.05);
        pBox77->AddText("#font[62]{#color[600]{Summary of Uncomputing:}}");
        pBox77->AddText("");
        pBox77->AddText("1. H^{-1} = H    #color[2]{#rightarrow}  Reverses the Hadamard superposition (Step 3)");
        pBox77->AddText("2. U^{-1} = e^{-iA#tau}   #color[2]{#rightarrow}  Reverses the unitary evolution (Step 4)");
        pBox77->AddText("3. QFT = IQFT^{-1} #color[2]{#rightarrow}  Reverses the Inverse Quantum Fourier Transform (Step 5)");
        pBox77->AddText("");
        pBox77->AddText("#font[62]{#color[2]{Combined effect: Clock register returns to |0#GT^{#otimes m}_{C}}}");
        pBox77->Draw();

    }

}

void QHHLA_SoftEdu::DrawCircuit_Step7(Int_t microStep){

    // Position parameters
    Double_t xStart = 0.05;        // Start of the lines
    Double_t xEnd = 0.95;          // End of the lines
    Double_t yIndex = 0.75;        // Position Y of the Index record (top)
    Double_t yAncilla = 0.20;      // Y position of the Ancilla qubit (lower)
    Double_t yClockStart = 0.65;   // Clock bus start
    Double_t yClockSpacing = 0.10; // Space between clock qubits

    // Gate dimensions (Hadamard)
    Double_t hGateX1 = 0.07;
    Double_t hGateX2 = 0.11;
    Double_t hGateHalfHeight = 0.04;
    
    // Gate dimensions (Controlled-U)
    Double_t uGateWidth = 0.10;
    Double_t uGateHeight = 0.08;
    Double_t uGateXStart = 0.13;   // Starting X position for U gates
    Double_t uGateSpacing = 0.12;  // Spacing between U gates
    
    //? Rendering step 7.8: Circuit Diagram step 4
    if (microStep >= 8) {

        // TOP LINE: Memory/Index Register
        TLine *lineIndex = new TLine(xStart, yIndex, xEnd, yIndex);
        lineIndex->SetLineWidth(2);
        lineIndex->SetLineColor(kBlue+3);
        lineIndex->Draw();
        
        // Initial state |0⟩ for index record
        TLatex *stateIndex = new TLatex(xStart - 0.035, yIndex-0.015, "|b#GT_{I}");
        stateIndex->SetNDC();
        stateIndex->SetTextFont(62);
        stateIndex->SetTextSize(0.05);
        stateIndex->SetTextColor(kBlue+3);
        stateIndex->Draw();
        
        // CENTRAL LINES: Clock Register m-qubit bus
        for (Int_t i = 0; i < fClockQubitsM; i++) {
            Double_t yClock = yClockStart - (i * yClockSpacing);
            
            TLine *lineClock = new TLine(xStart, yClock, xEnd, yClock);
            lineClock->SetLineWidth(2);
            lineClock->SetLineColor(kGreen+3);
            lineClock->Draw();
            
            // Initial state |0⟩ for each qubit of the clock
            TLatex *stateClock = new TLatex(xStart - 0.035, yClock - 0.015, "|0#GT_{C}");
            stateClock->SetNDC();
            stateClock->SetTextFont(62);
            stateClock->SetTextSize(0.05);
            stateClock->SetTextColor(kGreen+3);
            stateClock->Draw();

            if (microStep >= 9) {
                // Background box for the gate
                TBox *hBox = new TBox(hGateX1, yClock - hGateHalfHeight, hGateX2, yClock + hGateHalfHeight);
                hBox->SetFillColor(kCyan-10);
                hBox->SetLineColor(kCyan+4);
                hBox->SetLineWidth(1.5);
                hBox->Draw("l");
                
                // Letter 'H' inside the box
                TLatex *hText = new TLatex((hGateX1 + hGateX2)/2.0, yClock, "H");
                hText->SetTextAlign(22);
                hText->SetTextFont(62);
                hText->SetTextSize(0.06);
                hText->SetTextColor(kCyan+4);
                hText->Draw();

            }

        }
        
        // BOTTOM LINE: Qubit Ancilla
        TLine *lineAncilla = new TLine(xStart, yAncilla, xEnd, yAncilla);
        lineAncilla->SetLineWidth(2);
        lineAncilla->SetLineColor(kCyan+3);
        lineAncilla->Draw();
        
        // Initial state |0⟩ for the ancilla
        TLatex *stateAncilla = new TLatex(xStart - 0.035, yAncilla - 0.015, "|0#GT_{A}");
        stateAncilla->SetNDC();
        stateAncilla->SetTextFont(62);
        stateAncilla->SetTextSize(0.05);
        stateAncilla->SetTextColor(kCyan+3);
        stateAncilla->Draw();
        
        //? Rendering step 7.10: Controlled-U operations
        if (microStep >= 10) {

            // Draw controlled-U gates for each clock qubit
            for (Int_t i = 0; i < fClockQubitsM; i++) {
                Double_t yClock = yClockStart - (i * yClockSpacing);
                Double_t uGateX = uGateXStart + (i * uGateSpacing);
                
                // Calculate the power: 2^i
                Int_t power = TMath::Power(2, i);
                
                // Draw control dot on clock qubit line
                TMarker *controlDot = new TMarker(uGateX + uGateWidth/2.0, yClock, 20);
                controlDot->SetMarkerSize(1.5);
                controlDot->SetMarkerColor(kBlue+4);
                controlDot->SetMarkerStyle(20);
                controlDot->Draw();
                
                // Draw vertical line from control to U gate
                TLine *controlLine = new TLine(uGateX + uGateWidth/2.0, yClock, 
                    uGateX + uGateWidth/2.0, yIndex);
                controlLine->SetLineWidth(1);
                controlLine->SetLineColor(kBlue+4);
                controlLine->Draw();
                
                // Draw U gate box on index register line
                TBox *uBox = new TBox(uGateX, yIndex - uGateHeight/2.0, 
                    uGateX + uGateWidth, yIndex + uGateHeight/2.0);
                uBox->SetFillColor(kBlue-10);
                uBox->SetLineColor(kBlue+4);
                uBox->SetLineWidth(1.5);
                uBox->Draw("l");
                
                // Label U gate with power notation
                TString uLabel;
                if (i == 0) {
                    uLabel = "U^{2^{0}}=e^{iA#tau(1)}";
                } else if (i == 1) {
                    uLabel = "U^{2^{1}}=e^{iA#tau(2)}";
                } else {
                    uLabel = TString::Format("U^{2^{%d}}=e^{iA#tau(%d)}", i, power);
                }
                
                TLatex *uText = new TLatex(uGateX + uGateWidth/2.0, yIndex, uLabel);
                uText->SetTextAlign(22);
                uText->SetTextFont(42);
                uText->SetTextSize(0.05);
                uText->SetTextColor(kBlue+4);
                uText->Draw();
    
            }

        }
        
        //? Rendering step 7.11: IQFT box at the end of clock register lines
        if (microStep >= 11) {

            // Calculate bounds for the IQFT box spanning all clock qubits
            Double_t yClockTop = yClockStart + hGateHalfHeight;      // Top of first clock qubit line
            Double_t yClockBottom = yClockStart - ((fClockQubitsM - 1) * yClockSpacing) - hGateHalfHeight; // Bottom of last clock qubit line
            
            // Calculate end position of last Controlled-U gate
            Int_t lastUIndex = fClockQubitsM - 1;
            Double_t lastUGateX = uGateXStart + (lastUIndex * uGateSpacing);
            Double_t uGatesEndX = lastUGateX + uGateWidth;
            
            Double_t iqftWidth = 0.05;
            Double_t xIQFT = uGatesEndX + 0.02;  // Small gap after last U gate
            Double_t xIQFTEnd = xIQFT + iqftWidth;
            
            // Draw IQFT box spanning all clock register lines
            TBox *iqftBox = new TBox(xIQFT, yClockBottom, xIQFTEnd, yClockTop);
            iqftBox->SetFillColor(kViolet-9);
            iqftBox->SetLineColor(kViolet+3);
            iqftBox->SetLineWidth(1.5);
            iqftBox->Draw("l");
            
            // Vertical "IQFT" label 
            TLatex *iqftLabel = new TLatex(xIQFT + iqftWidth/2.0, (yClockTop + yClockBottom)/2.0, "IQFT");
            iqftLabel->SetTextAlign(22);
            iqftLabel->SetTextFont(62);
            iqftLabel->SetTextSize(0.05);
            iqftLabel->SetTextColor(kViolet+3);
            iqftLabel->SetTextAngle(90);  // Vertical text
            iqftLabel->Draw();
            
            // QPE dashed bracket: from H gates to IQFT, covering H + U gates + IQFT vertically
            Double_t xQPE_Left = hGateX1;
            Double_t xQPE_Right = xIQFTEnd;
            
            // Vertical bounds: from top of U gates on index register to bottom of clock register
            Double_t yQPE_Top = yIndex + uGateHeight/2.0 + 0.02;     // Top of U gates on index line
            Double_t yQPE_Bottom = yClockBottom - 0.02;               // Bottom of last clock line
            
            // Draw dashed bracket (no fill, dashed lines)
            // Top edge - dashed
            TLine *qpeTop = new TLine(xQPE_Left, yQPE_Top, xQPE_Right, yQPE_Top);
            qpeTop->SetLineColor(kOrange+3);
            qpeTop->SetLineWidth(2);
            qpeTop->SetLineStyle(2);  // Dashed line
            qpeTop->Draw();
            
            // Bottom edge - dashed
            TLine *qpeBottom = new TLine(xQPE_Left, yQPE_Bottom, xQPE_Right, yQPE_Bottom);
            qpeBottom->SetLineColor(kOrange+3);
            qpeBottom->SetLineWidth(2);
            qpeBottom->SetLineStyle(2);  // Dashed line
            qpeBottom->Draw();
            
            // Left edge - dashed
            TLine *qpeLeft = new TLine(xQPE_Left, yQPE_Top, xQPE_Left, yQPE_Bottom);
            qpeLeft->SetLineColor(kOrange+3);
            qpeLeft->SetLineWidth(2);
            qpeLeft->SetLineStyle(2);  // Dashed line
            qpeLeft->Draw();
            
            // Right edge - dashed
            TLine *qpeRight = new TLine(xQPE_Right, yQPE_Top, xQPE_Right, yQPE_Bottom);
            qpeRight->SetLineColor(kOrange+3);
            qpeRight->SetLineWidth(2);
            qpeRight->SetLineStyle(2);  // Dashed line
            qpeRight->Draw();
            
            // QPE label at the center of the bottom edge
            TLatex *qpeLabel = new TLatex((xQPE_Left + xQPE_Right)/2.0, yQPE_Bottom - 0.015, "QPE");
            qpeLabel->SetTextAlign(23);  // Centered, bottom-aligned
            qpeLabel->SetTextFont(62);
            qpeLabel->SetTextSize(0.05);
            qpeLabel->SetTextColor(kOrange+3);
            qpeLabel->Draw();

            //? Rendering step 7.12: Controlled-Ry(θ) gate converging from all clock qubits to ancilla
            if (microStep >= 12) {

                // Calculate X position for the Ry gate: placed after the IQFT box with a small gap
                Double_t xRyGate = xIQFTEnd;
                Double_t ryGateWidth = 0.10;
                
                // Draw control dots on each clock qubit line and vertical lines converging to ancilla
                for (Int_t i = 0; i < fClockQubitsM; i++) {
                    Double_t yClock = yClockStart - (i * yClockSpacing);
                    
                    // Draw control dot on clock qubit line at the Ry gate X position
                    TMarker *ryControlDot = new TMarker(xRyGate + ryGateWidth/2.0, yClock, 20);
                    ryControlDot->SetMarkerSize(1.5);
                    ryControlDot->SetMarkerColor(kRed+3);
                    ryControlDot->SetMarkerStyle(20);
                    ryControlDot->Draw();
                    
                    // Draw vertical line from control dot down to the ancilla line
                    TLine *ryControlLine = new TLine(xRyGate + ryGateWidth/2.0, yClock, 
                        xRyGate + ryGateWidth/2.0, yAncilla);
                    ryControlLine->SetLineWidth(1.5);
                    ryControlLine->SetLineColor(kRed+3);
                    ryControlLine->SetLineStyle(1);
                    ryControlLine->Draw();
                }
                
                // Draw the Ry(θ) gate box on the ancilla line
                Double_t yRyTop = yAncilla + 0.04;      // Extend slightly above top ancilla line
                Double_t yRyBottom = yAncilla - 0.04;   // Extend slightly below ancilla line
                
                TBox *ryBox = new TBox(xRyGate, yRyBottom, xRyGate + ryGateWidth, yRyTop);
                ryBox->SetFillColor(kRed-10);
                ryBox->SetLineColor(kRed+3);
                ryBox->SetLineWidth(1.5);
                ryBox->Draw("l");
                
                // Label Ry(θ) inside the box
                TLatex *ryText = new TLatex(xRyGate + ryGateWidth/2.0, (yRyTop + yRyBottom)/2.0, "R_{y}(#theta)");
                ryText->SetTextAlign(22);
                ryText->SetTextFont(62);
                ryText->SetTextSize(0.05);
                ryText->SetTextColor(kRed+3);
                ryText->Draw();

                //? Rendering step 7.13: IQPE box spanning index and all clock qubit lines
                if (microStep >= 13) {

                    // Calculate X position for the IQPE box: placed after the Ry gate with a small gap
                    Double_t iqpeWidth = 0.05;
                    Double_t xIQPE = xRyGate + ryGateWidth;  // Small gap after Ry gate
                    Double_t xIQPEEnd = xIQPE + iqpeWidth;
                    
                    // Vertical bounds: from index register line down to last clock qubit line
                    // Use same bounds as the QPE dashed bracket for visual consistency
                    Double_t yIQPE_Top = yIndex + uGateHeight/2.0 + 0.02;     // Top of U gates on index line
                    Double_t yIQPE_Bottom = yClockBottom - 0.02;              // Bottom of last clock line
                    
                    // Draw IQPE box spanning index register and all clock register lines
                    TBox *iqpeBox = new TBox(xIQPE, yIQPE_Bottom, xIQPEEnd, yIQPE_Top);
                    iqpeBox->SetFillColor(kOrange-9);
                    iqpeBox->SetLineColor(kOrange+3);
                    iqpeBox->SetLineWidth(1.5);
                    iqpeBox->Draw("l");
                    
                    // Vertical "IQPE" label inside the box
                    TLatex *iqpeLabel = new TLatex(xIQPE + iqpeWidth/2.0, (yIQPE_Top + yIQPE_Bottom)/2.0, "IQPE");
                    iqpeLabel->SetTextAlign(22);
                    iqpeLabel->SetTextFont(62);
                    iqpeLabel->SetTextSize(0.05);
                    iqpeLabel->SetTextColor(kOrange+3);
                    iqpeLabel->SetTextAngle(90);
                    iqpeLabel->Draw();

                }

            }

        }

    }

}

void QHHLA_SoftEdu::DrawGraph_Step7(Int_t microStep){ 

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    c->cd();
    c->Clear();
    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right

    // --- CALCULATION OF PARAMETERS ---
    Int_t m = fClockQubitsM;
    Int_t numStates = ftotalStates; // 2^m
    
    // Calculate beta probabilities 
    Double_t prob1 = fBeta1.Rho2(); 
    Double_t prob2 = fBeta2.Rho2();
    
    if (TMath::IsNaN(prob1)) prob1 = 0.0;
    if (TMath::IsNaN(prob2)) prob2 = 0.0;
    
    // Determine the clock register states corresponding to the eigenvalues
    Int_t idxLambda1 = static_cast<Int_t>(fLambdaQPE1);
    Int_t idxLambda2 = static_cast<Int_t>(fLambdaQPE2);
    
    // Clamp to valid range [0, numStates-1]
    if (idxLambda1 < 0) idxLambda1 = 0;
    if (idxLambda1 >= numStates) idxLambda1 = numStates - 1;
    if (idxLambda2 < 0) idxLambda2 = 0;
    if (idxLambda2 >= numStates) idxLambda2 = numStates - 1;
    
    // Avoid collision: if both map to same bin (degenerate eigenvalues), separate slightly
    // though physically they might be the same state. We'll keep them as calculated.
    
    // --- STATE EQUATION BOX (Bottom-Left) ---
    if (microStep >= 14 && microStep < 15) {

        TPaveText *eqBox = new TPaveText(0.01, 0.01, 0.60, 0.12, "NDC");
        eqBox->SetFillColor(kWhite);
        eqBox->SetBorderSize(1);
        eqBox->SetLineColor(kGray+1);
        eqBox->SetTextAlign(22);
        eqBox->SetTextSize(0.035);
        eqBox->SetTextFont(132);
        eqBox->SetTextColor(kRed+3);
        
        TString eq714 = TString::Format(
            "|#Psi_{4}#GT = #beta_{1}|u_{1}#GT|#lambda_{1}#GT_{C} " 
            "#left( #sqrt{ 1 + #frac{C^{2}}{#lambda_{1}^{2}}}|0#GT_{A} + #frac{C}{#lambda_{1}}|1#GT_{A} #right)"
            " + #beta_{2}|u_{2}#GT|#lambda_{2}#GT_{C} "
            "#left( #sqrt{ 1 + #frac{C^{2}}{#lambda_{2}^{2}}}|0#GT_{A} + #frac{C}{#lambda_{2}}|1#GT_{A} #right)"
        );
        eqBox->AddText(eq714.Data());
        eqBox->Draw();

    }
    
    if (microStep >= 15) {

        TPaveText *eqBox = new TPaveText(0.01, 0.01, 0.60, 0.12, "NDC");
        eqBox->SetFillColor(kWhite);
        eqBox->SetBorderSize(1);
        eqBox->SetLineColor(kGray+1);
        eqBox->SetTextAlign(22);
        eqBox->SetTextSize(0.035);
        eqBox->SetTextFont(132);
        eqBox->SetTextColor(kRed+3);
        
        TString eq715 = TString::Format(
            "|#Psi_{5}#GT = |00..0#GT_{C} #otimes #left[ #beta_{1}|u_{1}#GT " 
            "#left( #sqrt{ 1 + #frac{C^{2}}{#lambda_{1}^{2}}}|0#GT_{A} + #frac{C}{#lambda_{1}}|1#GT_{A} #right)"
            " + #beta_{2}|u_{2}#GT "
            "#left( #sqrt{ 1 + #frac{C^{2}}{#lambda_{2}^{2}}}|0#GT_{A} + #frac{C}{#lambda_{2}}|1#GT_{A} #right) #right]"
        );
        eqBox->AddText(eq715.Data());
        eqBox->Draw();

    }

    // --- CREATION OF THE PLOT CONTAINER ---
    TPad *plotPad = new TPad("plotPadStep7", "Región del Gráfico 7", 0.01, 0.12, 0.99, 0.88);
    plotPad->Draw();
    plotPad->cd();
    
    plotPad->SetBottomMargin(0.18); 
    plotPad->SetTopMargin(0.12);
    plotPad->SetGrid(1, 1); 
    
    // --- HISTOGRAM RENDERING ---
    if (microStep >= 14) {
        
        // Base histogram (axis framework)
        TH1F *hBase = new TH1F("hBaseStep7", ";Clock Register State |j#GT_{C};Probability P", numStates, 0, numStates);
        hBase->SetDirectory(0); 
        hBase->SetStats(0);     
        
        hBase->SetMinimum(0.0);   
        hBase->SetMaximum(1.15);
        
        // Configure binary labels for all states
        for (Int_t i = 0; i < numStates; i++) {
            TString binLabel = "|";
            for (Int_t bit = m - 1; bit >= 0; bit--) {
                binLabel += ((i >> bit) & 1) ? "1" : "0";
            }
            binLabel += "#GT";
            hBase->GetXaxis()->SetBinLabel(i + 1, binLabel.Data());
            hBase->SetBinContent(i + 1, 0.001); // Minimum visual baseline
        }
        
        // Axis configuration (consistent with Steps 2 and 3)
        hBase->GetXaxis()->SetLabelSize(0.05);
        hBase->GetXaxis()->SetTitleSize(0.045); 
        hBase->GetXaxis()->SetLabelFont(42);
        hBase->GetXaxis()->SetTickLength(0);   
        
        hBase->GetYaxis()->SetTitleSize(0.04);
        hBase->GetYaxis()->SetTitleOffset(1.1);
        hBase->GetYaxis()->SetLabelSize(0.04);
        hBase->GetYaxis()->SetTitleSize(0.045);
        
        hBase->SetFillColor(kGray+1);
        hBase->SetFillStyle(1001);
        hBase->SetLineColor(kGray+1);
        hBase->SetLineWidth(1);
        hBase->SetBarOffset(0.15); 
        hBase->SetBarWidth(0.7);  
        
        // --- SUBSTEP 14: After IQPE (peaks at lambda1, lambda2) ---
        if (microStep >= 14 && microStep < 15) {
            
            // Histogram for lambda1 peak
            TH1F *hL1 = new TH1F("hL1Step7", "", numStates, 0, numStates);
            hL1->SetDirectory(0);
            hL1->SetStats(0);
            hL1->SetMinimum(0.0);
            hL1->SetMaximum(1.2);
            for (Int_t i = 0; i < numStates; i++) hL1->SetBinContent(i + 1, 0.001);
            hL1->SetBinContent(idxLambda1 + 1, prob1);
            hL1->SetFillColor(kAzure-5);
            hL1->SetFillStyle(1001);
            hL1->SetLineColor(kAzure+2);
            hL1->SetLineWidth(2);
            hL1->SetBarOffset(0.15);
            hL1->SetBarWidth(0.7);
            
            // Histogram for lambda2 peak
            TH1F *hL2 = new TH1F("hL2Step7", "", numStates, 0, numStates);
            hL2->SetDirectory(0);
            hL2->SetStats(0);
            hL2->SetMinimum(0.0);
            hL2->SetMaximum(1.2);
            for (Int_t i = 0; i < numStates; i++) hL2->SetBinContent(i + 1, 0.001);
            hL2->SetBinContent(idxLambda2 + 1, prob2);
            hL2->SetFillColor(kRed-7);
            hL2->SetFillStyle(1001);
            hL2->SetLineColor(kRed+2);
            hL2->SetLineWidth(2);
            hL2->SetBarOffset(0.15);
            hL2->SetBarWidth(0.7);
            
            // Draw layers
            hBase->Draw("BAR");
            hL1->Draw("BAR SAME");
            hL2->Draw("BAR SAME");
            
            // Value labels above peaks
            TLatex *labelL1 = new TLatex(idxLambda1 + 0.5, prob1 + 0.04, TString::Format("%.2f", prob1).Data());
            labelL1->SetTextAlign(22); 
            labelL1->SetTextSize(0.045); 
            labelL1->SetTextColor(kAzure+2);
            labelL1->Draw();
            
            TLatex *labelL2 = new TLatex(idxLambda2 + 0.5, prob2 + 0.04, TString::Format("%.2f", prob2).Data());
            labelL2->SetTextAlign(22); 
            labelL2->SetTextSize(0.045); 
            labelL2->SetTextColor(kRed+2);
            labelL2->Draw();
            
            // Peak identification labels
            TLatex *idL1 = new TLatex(idxLambda1 + 0.5, prob1 + 0.11, "#lambda_{1}");
            idL1->SetTextAlign(22);
            idL1->SetTextSize(0.035);
            idL1->SetTextColor(kAzure+3);
            idL1->SetTextFont(132);
            idL1->Draw();
            
            TLatex *idL2 = new TLatex(idxLambda2 + 0.5, prob2 + 0.11, "#lambda_{2}");
            idL2->SetTextAlign(22);
            idL2->SetTextSize(0.035);
            idL2->SetTextColor(kRed+3);
            idL2->SetTextFont(132);
            idL2->Draw();
            
            // Title
            TLatex *titleText = new TLatex(0.5, 0.93, "#color[600]{#font[62]{Probability Distribution after IQPE (Clock Register)}}");
            titleText->SetNDC();
            titleText->SetTextAlign(22);
            titleText->SetTextSize(0.050);
            titleText->SetTextColor(kBlack);
            titleText->Draw();

        }
        
        // --- SUBSTEP 15: After IQPE (ground state |0...0> reaches 100%) ---
        if (microStep >= 15) {
            
            // Histogram for residual lambda peaks (diminished)
            TH1F *hL1 = new TH1F("hL1Step7_15", "", numStates, 0, numStates);
            hL1->SetDirectory(0);
            hL1->SetStats(0);
            hL1->SetMinimum(0.0);
            hL1->SetMaximum(1.2);
            for (Int_t i = 0; i < numStates; i++) hL1->SetBinContent(i + 1, 0.001);
            hL1->SetBinContent(idxLambda1 + 1, 0.001); // Diminished to baseline
            hL1->SetFillColor(kGray+2);
            hL1->SetFillStyle(1001);
            hL1->SetLineColor(kGray+2);
            hL1->SetLineWidth(1);
            hL1->SetBarOffset(0.15);
            hL1->SetBarWidth(0.7);
            
            TH1F *hL2 = new TH1F("hL2Step7_15", "", numStates, 0, numStates);
            hL2->SetDirectory(0);
            hL2->SetStats(0);
            hL2->SetMinimum(0.0);
            hL2->SetMaximum(1.2);
            for (Int_t i = 0; i < numStates; i++) hL2->SetBinContent(i + 1, 0.001);
            hL2->SetBinContent(idxLambda2 + 1, 0.001); // Diminished to baseline
            hL2->SetFillColor(kGray+2);
            hL2->SetFillStyle(1001);
            hL2->SetLineColor(kGray+2);
            hL2->SetLineWidth(1);
            hL2->SetBarOffset(0.15);
            hL2->SetBarWidth(0.7);
            
            // Histogram for |0...0> ground state (probability = 1.0)
            TH1F *hZero = new TH1F("hZeroStep7", "", numStates, 0, numStates);
            hZero->SetDirectory(0);
            hZero->SetStats(0);
            hZero->SetMinimum(0.0);
            hZero->SetMaximum(1.2);
            for (Int_t i = 0; i < numStates; i++) hZero->SetBinContent(i + 1, 0.001);
            hZero->SetBinContent(1, 1.0); // State |00...0> is bin 1
            hZero->SetFillColor(kGreen-7);
            hZero->SetFillStyle(1001);
            hZero->SetLineColor(kGreen+2);
            hZero->SetLineWidth(2);
            hZero->SetBarOffset(0.15);
            hZero->SetBarWidth(0.7);
            
            // Draw layers: base (gray) -> residual peaks -> ground state on top
            hBase->Draw("BAR");
            hL1->Draw("BAR SAME");
            hL2->Draw("BAR SAME");
            hZero->Draw("BAR SAME");
            
            // Label for |0...0> peak
            TLatex *labelZero = new TLatex(0.5, 1.04, "1.000");
            labelZero->SetTextAlign(22);
            labelZero->SetTextSize(0.045);
            labelZero->SetTextColor(kGreen+3);
            labelZero->Draw();
            
            TLatex *idZero = new TLatex(0.5, 1.10, "|00...0#GT");
            idZero->SetTextAlign(22);
            idZero->SetTextSize(0.035);
            idZero->SetTextColor(kGreen+3);
            idZero->SetTextFont(132);
            idZero->Draw();
            
            // Title
            TLatex *titleText = new TLatex(0.5, 0.93, "#color[416]{#font[62]{Probability Distribution after IQPE (Uncomputed Clock)}}");
            titleText->SetNDC();
            titleText->SetTextAlign(22);
            titleText->SetTextSize(0.050);
            titleText->SetTextColor(kBlack);
            titleText->Draw();

        }

    }
    
    // --- STATISTICAL SUMMARY BOX ---
    if (microStep >= 14 && microStep < 15) {

        TPaveText *probBox = new TPaveText(0.85, 0.78, 0.98, 0.98, "NDC");
        probBox->SetFillColor(kYellow-9);
        probBox->SetBorderSize(1);
        probBox->SetLineColor(kOrange-2);
        probBox->SetTextAlign(12);
        probBox->SetTextSize(0.035);
        probBox->SetTextFont(42);
        probBox->SetMargin(0.08);
        
        probBox->AddText("QPE Peaks:");
        probBox->AddText(TString::Format("P(#lambda_{1}) = %.2f", prob1).Data());
        probBox->AddText(TString::Format("P(#lambda_{2}) = %.2f", prob2).Data());
        probBox->AddLine(0.1, 0.25, 0.9, 0.25); 
        probBox->AddText(TString::Format("Sum = %.2f", prob1 + prob2).Data());
        probBox->Draw();

    }
    
    if (microStep >= 15) {

        TPaveText *probBox = new TPaveText(0.85, 0.75, 0.98, 0.98, "NDC");
        probBox->SetFillColor(kYellow-9);
        probBox->SetBorderSize(1);
        probBox->SetLineColor(kOrange-2);
        probBox->SetTextAlign(12);
        probBox->SetTextSize(0.035);
        probBox->SetTextFont(42);
        probBox->SetMargin(0.08);
        
        probBox->AddText("After IQPE:");
        probBox->AddText("P(|00...0#GT) = 1.0000");
        probBox->AddText(TString::Format("P(#lambda_{1}) #approx %.2f", 0.0).Data());
        probBox->AddText(TString::Format("P(#lambda_{2}) #approx %.2f", 0.0).Data());
        probBox->AddLine(0.1, 0.21, 0.9, 0.21); 
        probBox->AddText("Clock uncomputed");
        probBox->Draw();

    }
    
    c->Modified();
    c->Update();
    c->cd();
    
}

//* MODULAR METHODS: STEP 8 (Measurement & Post-selection) --------------------
void QHHLA_SoftEdu::DrawMath_Step8(Int_t microStep) {

    TString b1Str = FormatComplex(fbetaNum1);
    TString b2Str = FormatComplex(fbetaNum2);
    TString sign1, val1, sign2, val2;
    DecomposeSign(b1Str, sign1, val1);
    DecomposeSign(b2Str, sign2, val2);

    Int_t num1 = (fLambda1*fLambda1)-(fC*fC);
    Int_t num2 = (fLambda2*fLambda2)-(fC*fC);


    TComplex am1 = (fBeta1 * fC) / fLambda1;
    TComplex am2 = (fBeta2 * fC) / fLambda2;

    Double_t Coff1 = am1.Rho2();  // |am1|²
    Double_t Coff2 = am2.Rho2();  // |am2|²

    TComplex Amp1 = fBeta1/(fLambda1*TMath::Sqrt(fProb1));
    TComplex Amp2 = fBeta2/(fLambda2*TMath::Sqrt(fProb1));

    TString Amp1Str = FormatComplex(Amp1);
    TString Amp2Str = FormatComplex(Amp2);

    TString Asign1, Aval1, Asign2, Aval2;
    DecomposeSign(Amp1Str, Asign1, Aval1);
    DecomposeSign(Amp2Str, Asign2, Aval2);
    
    //? Rendering step 8.1: Factorization into Ancilla Branches
    if (microStep >= 1) {

        TString S81title = TString::Format(
            "#font[62]{#color[600]{8.1. Rewriting by Factorization:}} "
            "Grouping |#Psi_{5}#GT by ancilla states |0#GT_{A} and |1#GT_{A}."
        );
        TLatex *lTitleS81 = new TLatex(0.02, 0.85, S81title.Data());
        lTitleS81->SetNDC();
        lTitleS81->SetTextFont(42);
        lTitleS81->SetTextSize(0.040);
        lTitleS81->SetTextColor(kGray+3);
        lTitleS81->Draw();
        
        // Factorized state |Ψ₆⟩
        TString eq81 = TString::Format(
            "|#Psi_{6}#GT = #left[ #frac{%s}{#sqrt{%.0f}} #frac{#sqrt{%i}}{%.2f} "
            "|u_{1}#GT_{I} %s #frac{%s}{#sqrt{%.0f}} #frac{#sqrt{%i}}{%.2f} |u_{2}#GT_{I} " 
            "#right] #otimes #color[635]{|0#GT_{A}} + "
            "#left[ #frac{%s}{#sqrt{%.0f}} #frac{%.0f}{%.2f} |u_{1}#GT_{I} %s " 
            " #frac{%s}{#sqrt{%.0f}} #frac{%.0f}{%.2f} |u_{2}#GT_{I} #right] #otimes #color[635]{|1#GT_{A}}", 
            b1Str.Data(), fIntDenomSq, num1, fLambda1, sign2.Data(), val2.Data(), fIntDenomSq, num2, fLambda2,
            b1Str.Data(), fIntDenomSq, fC, fLambda1, sign2.Data(), val2.Data(), fIntDenomSq, fC, fLambda2
        );
        TLatex *lEq81 = new TLatex(0.04, 0.75, eq81.Data());
        lEq81->SetNDC();
        lEq81->SetTextFont(132);
        lEq81->SetTextSize(0.05);
        lEq81->SetTextColor(kBlack);
        lEq81->Draw();
        
    }

    //? Rendering step 8.2: Success Probability Calculation
    if (microStep >= 2) {

        TString S82title = TString::Format(
            "#font[62]{#color[600]{8.2. Success Probability P(#font[132]{|1#GT}):}} "
            "This is the probability of measuring the ancilla in state #font[132]{|1#GT_{A}}."
        );
        TLatex *lTitleS82 = new TLatex(0.02, 0.65, S82title.Data());
        lTitleS82->SetNDC();
        lTitleS82->SetTextFont(42);
        lTitleS82->SetTextSize(0.040);
        lTitleS82->SetTextColor(kGray+3);
        lTitleS82->Draw();

        TString eq82 = TString::Format(
            "P(|1#GT) = #sum_{j=1}^{N} #left| #beta_{j} #frac{C}{#lambda_{j}} #right|^{2}"
            "  #color[2]{#rightarrow}  "
            "P(|1#GT) = #left| #frac{%s}{#sqrt{%.0f}} #frac{%.0f}{%.2f} #right|^{2} + "
            "#left| #frac{%s}{#sqrt{%.0f}} #frac{%.0f}{%.2f} #right|^{2} = "
            "#color[419]{%.2f + %.2f = %.2f}",
            b1Str.Data(), fIntDenomSq, fC, fLambda1, b2Str.Data(), fIntDenomSq, fC, fLambda2,
            Coff1, Coff2, fProb1
        );
        TLatex *lEq82 = new TLatex(0.04, 0.55, eq82.Data()); 
        lEq82->SetNDC();
        lEq82->SetTextFont(132);
        lEq82->SetTextSize(0.05);
        lEq82->SetTextColor(kBlack);
        lEq82->Draw();

    }

    //? Rendering step 8.3: Collapse (Post-selection)
    if (microStep >= 3) {

        TString S83titleDesc = "#font[62]{#color[600]{8.3. Collapse (Post-selection):}} Measurement of ancilla";
        TLatex *lTitleS83 = new TLatex(0.02, 0.45, S83titleDesc.Data());
        lTitleS83->SetNDC();
        lTitleS83->SetTextFont(42);
        lTitleS83->SetTextSize(0.040);
        lTitleS83->SetTextColor(kGray+3);
        lTitleS83->Draw();

        // Status after measurement
        TString eq83 = TString::Format(
            "#scale[0.8]{#color[635]{#font[42]{After measuring} |1#GT:}}"
            "  #color[2]{#rightarrow}  "
            "|#Psi_{post}#GT = #sum_{j=1}^{N} #beta_{j} #frac{C}{#lambda_{j}} |u_{j}#GT_{I}" 
        );
        TLatex *lEq83 = new TLatex(0.04, 0.35, eq83.Data()); 
        lEq83->SetNDC();
        lEq83->SetTextFont(132);     
        lEq83->SetTextSize(0.05);
        lEq83->SetTextColor(kBlack); 
        lEq83->Draw();
        
        TPaveText *pBoxS83 = new TPaveText(0.50, 0.30, 0.98, 0.50, "NDC");
        pBoxS83->SetFillColor(kYellow-9);
        pBoxS83->SetBorderSize(1);
        pBoxS83->SetTextAlign(12);
        pBoxS83->SetTextSize(0.032);
        pBoxS83->SetMargin(0.03);
        pBoxS83->AddText("#font[62]{#color[4]{When we measure the ancilla qubit and obtain |1#GT:}}");
        pBoxS83->AddText("");
        pBoxS83->AddText("#bullet The branch accompanied by |0#GT_{A} #color[1]{vanishes (collapses to zero)}");
        pBoxS83->AddText("#bullet Only the branch with |1#GT_{A} #color[2]{survives}");
        pBoxS83->AddText("#bullet The system collapses to the normalized solution state");
        pBoxS83->Draw();

    }


    //? Rendering step 8.4: Solution State |x⟩
    if (microStep >= 4) {

        TString S84titleDesc = "#font[62]{#color[600]{8.4. Solution State |x#GT:}} Normalized final state";
        TLatex *lTitleS84 = new TLatex(0.02, 0.25, S84titleDesc.Data());
        lTitleS84->SetNDC();
        lTitleS84->SetTextFont(42);
        lTitleS84->SetTextSize(0.040);
        lTitleS84->SetTextColor(kGray+3);
        lTitleS84->Draw();

        TString eq84 = TString::Format(
            "|x#GT = #frac{1}{#sqrt{P(|1#GT)}} #sum_{j=1}^{N} #beta_{j} #frac{C}{#lambda_{j}} |u_{j}#GT_{I}" 
            "   #color[2]{#rightarrow}   "
            "|x#GT = #color[635]{#frac{1}{#sqrt{%.2f}} #frac{%s}{#sqrt{%.0f}} #frac{%.0f}{%.2f}} |u_{1}#GT_{I} %s "
            " #color[635]{#frac{1}{#sqrt{%.2f}} #frac{%s}{#sqrt{%.0f}} #frac{%.0f}{%.2f}} |u_{2}#GT_{I} "
            "= #color[419]{%s} |u_{1}#GT_{I} %s #color[419]{%s} |u_{2}#GT_{I}",
            fProb1, b1Str.Data(), fIntDenomSq, fC, fLambda1, sign2.Data(), 
            fProb1, val2.Data(), fIntDenomSq, fC, fLambda2, Amp1Str.Data(), Asign2.Data(), Aval2.Data()
        );
        TLatex *lEq84 = new TLatex(0.04, 0.15, eq84.Data()); 
        lEq84->SetNDC();
        lEq84->SetTextFont(132);     
        lEq84->SetTextSize(0.05);
        lEq84->SetTextColor(kBlack); 
        lEq84->Draw();

    }

}

void QHHLA_SoftEdu::DrawMatrix_Step8(Int_t microStep){

    //EXTRACTION OF A, b AND CLASSICAL SOLUTION
    TComplex a = fMatrixA[0][0], b = fMatrixA[0][1];
    TComplex c = fMatrixA[1][0], d = fMatrixA[1][1];
    TComplex b0 = fVectorB[0], b1 = fVectorB[1];
    TComplex det = a*d - b*c;

    TString aStr = FormatComplex(a);
    TString bStr = FormatComplex(b);
    TString cStr = FormatComplex(c);
    TString dStr = FormatComplex(d);
    TString detStr = FormatComplex(det);
    TString b0Str = FormatComplex(b0);
    TString b1Str = FormatComplex(b1);

    // Classical solution: x = A^{-1} b  (Cramer's rule for 2x2)
    TComplex x1 = (d * b0 - b * b1) / det;
    TComplex x2 = (-c * b0 + a * b1) / det; 

    TString x1Str = FormatComplex(x1);
    TString x2Str = FormatComplex(x2);

    // Probability amplitudes
    TComplex Amp1 = fBeta1/(fLambda1*TMath::Sqrt(fProb1));
    TComplex Amp2 = fBeta2/(fLambda2*TMath::Sqrt(fProb1));

    TString Amp1Str = FormatComplex(Amp1);
    TString Amp2Str = FormatComplex(Amp2);

    TString Asign1, Aval1, Asign2, Aval2;
    DecomposeSign(Amp1Str, Asign1, Aval1);
    DecomposeSign(Amp2Str, Asign2, Aval2);

    TComplex u11 = fEigenvectors[0][0];
    TComplex u12 = fEigenvectors[1][0];
    TComplex u21 = fEigenvectors[0][1];
    TComplex u22 = fEigenvectors[1][1];

    TString u11Str = FormatComplex(u11); 
    TString u12Str = FormatComplex(u12);
    TString u21Str = FormatComplex(u21);
    TString u22Str = FormatComplex(u22);

    // Verify unit norm
    TComplex xq1 = fVectorQX[0];
    TComplex xq2 = fVectorQX[1];

    TString xq1Str = FormatComplex(xq1);
    TString xq2Str = FormatComplex(xq2);

    Double_t normCheck = TMath::Sqrt(xq1.Rho2() + xq2.Rho2());

    //? Rendering step 8.5: Classical Solution Vector
    if (microStep >= 5) {

        TString S85title = TString::Format(
            "#font[62]{#color[600]{8.5. Classical Solution Vector:}} "
            "Obtained directly from the linear system Ax = b."
        );
        TLatex *lTitleS85 = new TLatex(0.02, 0.85, S85title.Data());
        lTitleS85->SetNDC();
        lTitleS85->SetTextFont(42);
        lTitleS85->SetTextSize(0.040);
        lTitleS85->SetTextColor(kGray+3);
        lTitleS85->Draw();

        // Inverse formula: (1/det) * [[d, -b], [-c, a]]
        TComplex inv_11 = d,  inv_12 = -b;
        TComplex inv_21 = -c, inv_22 = a;

        TString inv_11Str = FormatComplex(inv_11);
        TString inv_12Str = FormatComplex(inv_12);
        TString inv_21Str = FormatComplex(inv_21);
        TString inv_22Str = FormatComplex(inv_22); 
        

        TString eq85 = TString::Format(
            "#color[1]{x = A^{-1}b = #frac{1}{%s} #left[ #splitline{%s    %s}{%s    %s} #right]}"
            "#color[1]{#left[ #splitline{%.0f}{%.0f} #right] = "
            "#left[ #splitline{%s}{%s} #right]}",
            detStr.Data(), inv_11Str.Data(), inv_12Str.Data(), inv_21Str.Data(), 
            inv_22Str.Data(), b0.Re(), b1.Re(), x1Str.Data(), x2Str.Data()
        );
        TLatex *lEq85 = new TLatex(0.04, 0.75, eq85.Data());
        lEq85->SetNDC();
        lEq85->SetTextFont(132);
        lEq85->SetTextSize(0.060);
        lEq85->SetTextColor(kBlack);
        lEq85->Draw();

    }

    //? Rendering step 8.6: Quantum Solution Vector
    if (microStep >= 6) {

        TString S85title = TString::Format(
            "#font[62]{#color[600]{8.6. Quantum Solution Vector:}} "
            "Index register state after post-selecting ancilla replacing |u_{1}#GT, |u_{2}#GT."
        );
        TLatex *lTitleS85 = new TLatex(0.02, 0.65, S85title.Data());
        lTitleS85->SetNDC();
        lTitleS85->SetTextFont(42);
        lTitleS85->SetTextSize(0.040);
        lTitleS85->SetTextColor(kGray+3);
        lTitleS85->Draw();

        TString eq86 = TString::Format(
            "|x#GT = %s #color[635]{|u_{1}#GT_{I}} %s %s #color[635]{|u_{2}#GT_{I}} = "
            "#frac{%s}{#sqrt{%.0f}} #color[419]{#left[ #splitline{%s}{%s} #right]} "
            "%s "
            "#frac{%s}{#sqrt{%.0f}} #color[419]{#left[ #splitline{%s}{%s} #right]} = "
            "#color[416]{#left[ #splitline{%s}{%s} #right]}",
            Amp1Str.Data(), Asign2.Data(), Aval2.Data(), Amp1Str.Data(), fNormUSq, u11Str.Data(), u12Str.Data(),
            Asign2.Data(), Aval2.Data(), fNormUSq, u21Str.Data(), u22Str.Data(), xq1Str.Data(), xq2Str.Data()
        );
        TLatex *lEq86 = new TLatex(0.04, 0.55, eq86.Data());
        lEq86->SetNDC();
        lEq86->SetTextFont(132);
        lEq86->SetTextSize(0.060);
        lEq86->SetTextColor(kBlack);
        lEq86->Draw();

        TString eq86b = TString::Format(
            "#color[635]{|||x#GT|| = #sqrt{(%s)^{2} + (%s)^{2}} = #color[2]{%.2f}}",
            xq1Str.Data(), xq2Str.Data(), normCheck
        );
        TLatex *lEq86b = new TLatex(0.04, 0.45, eq86b.Data());
        lEq86b->SetNDC();
        lEq86b->SetTextFont(132);
        lEq86b->SetTextSize(0.050);
        lEq86b->SetTextColor(kRed+2);
        lEq86b->Draw();

    }

    //? Rendering step 8.7: Parallelism & Normalization Equivalence
    if (microStep >= 7) {

        TString S87title = "#font[62]{#color[600]{8.7. Parallelism & Equivalence:}} ";
        TLatex *lTitleS87 = new TLatex(0.02, 0.35, S87title.Data());
        lTitleS87->SetNDC();
        lTitleS87->SetTextFont(42);
        lTitleS87->SetTextSize(0.040);
        lTitleS87->SetTextColor(kGray+3);
        lTitleS87->Draw();

        // Explicit proportionality: |x> = (1/||x||) * x
        TString eq87a = TString::Format(
            "#color[632]{|x#GT} = #color[419]{%.2f} #color[1]{#vec{x}}  "
            "#color[2]{#Leftrightarrow}  "
            "#color[1]{#vec{x}} = #color[419]{#frac{1}{%.2f}} #color[632]{|x#GT}",
            fNGlobal, fNGlobal
        );
        TLatex *lEq87a = new TLatex(0.04, 0.25, eq87a.Data());
        lEq87a->SetNDC();
        lEq87a->SetTextFont(132);
        lEq87a->SetTextSize(0.06);
        lEq87a->SetTextColor(kBlack);
        lEq87a->Draw();

        TString S87des_1 = "#color[2]{#rightarrow} Both vectors are parallel;";
        TLatex *lDesS87_1 = new TLatex(0.04, 0.15, S87des_1.Data());
        lDesS87_1->SetNDC();
        lDesS87_1->SetTextFont(42);
        lDesS87_1->SetTextSize(0.040);
        lDesS87_1->SetTextColor(kGray+3);
        lDesS87_1->Draw();

        TString S87des_2 = "they differ only by a Normalization factor.";
        TLatex *lDesS87_2 = new TLatex(0.04, 0.10, S87des_2.Data());
        lDesS87_2->SetNDC();
        lDesS87_2->SetTextFont(42);
        lDesS87_2->SetTextSize(0.040);
        lDesS87_2->SetTextColor(kGray+3);
        lDesS87_2->Draw();

        //Component-wise Verification Box
        TPaveText *pBox87 = new TPaveText(0.45, 0.09, 0.90, 0.50, "NDC");
        pBox87->SetFillColor(kYellow-9);
        pBox87->SetBorderSize(1);
        pBox87->SetLineColor(kOrange-2);
        pBox87->SetShadowColor(kGray);
        pBox87->SetTextAlign(12);
        pBox87->SetTextSize(0.038);
        pBox87->SetTextFont(42);
        pBox87->SetMargin(0.05);
        pBox87->AddText("#font[62]{#color[600]{Component-wise Verification:}}");
        pBox87->AddText("");
        pBox87->AddText(TString::Format(
            "#color[1]{x_{1}} = %s   #color[2]{#rightarrow}   #color[632]{|x#GT_{1}} = %s(%.2f) = %s",
            x1Str.Data(), x1Str.Data(), fNGlobal, xq1Str.Data()));
        pBox87->AddText(TString::Format(
            "#color[1]{x_{2}} = %s   #color[2]{#rightarrow}   #color[632]{|x#GT_{2}} = %s(%.2f) = %s",
            x2Str.Data(), x2Str.Data(), fNGlobal, xq2Str.Data()));
        pBox87->AddText("");
        pBox87->AddText(TString::Format(
            "#color[419]{Constant:}  N = #frac{C}{#sqrt{P|1#GT}||b||} = %.4f",
            fNGlobal).Data());
        pBox87->AddText("");
        pBox87->AddText("#color[2]{#font[62]{Conclusion:}} The quantum state is the");
        pBox87->AddText("classical solution normalized to unit length.");
        pBox87->AddText("Removing the factor #color[419]{N} makes them identical.");
        pBox87->Draw();

    }

}

void QHHLA_SoftEdu::DrawCircuit_Step8(Int_t microStep){

    // Position parameters
    Double_t xStart = 0.05;        // Start of the lines
    Double_t xEnd = 0.95;          // End of the lines
    Double_t yIndex = 0.75;        // Position Y of the Index record (top)
    Double_t yAncilla = 0.20;      // Y position of the Ancilla qubit (lower)
    Double_t yClockStart = 0.65;   // Clock bus start
    Double_t yClockSpacing = 0.10; // Space between clock qubits

    // Gate dimensions (Hadamard)
    Double_t hGateX1 = 0.07;
    Double_t hGateX2 = 0.11;
    Double_t hGateHalfHeight = 0.04;
    
    // Gate dimensions (Controlled-U)
    Double_t uGateWidth = 0.10;
    Double_t uGateHeight = 0.08;
    Double_t uGateXStart = 0.13;   // Starting X position for U gates
    Double_t uGateSpacing = 0.12;  // Spacing between U gates
    
    //? Rendering step 8.8: Circuit Diagram step 4
    if (microStep >= 8) {

        // TOP LINE: Memory/Index Register
        TLine *lineIndex = new TLine(xStart, yIndex, xEnd, yIndex);
        lineIndex->SetLineWidth(2);
        lineIndex->SetLineColor(kBlue+3);
        lineIndex->Draw();
        
        // Initial state |0⟩ for index record
        TLatex *stateIndex = new TLatex(xStart - 0.035, yIndex-0.015, "|b#GT_{I}");
        stateIndex->SetNDC();
        stateIndex->SetTextFont(62);
        stateIndex->SetTextSize(0.05);
        stateIndex->SetTextColor(kBlue+3);
        stateIndex->Draw();
        
        // CENTRAL LINES: Clock Register m-qubit bus
        for (Int_t i = 0; i < fClockQubitsM; i++) {
            Double_t yClock = yClockStart - (i * yClockSpacing);
            
            TLine *lineClock = new TLine(xStart, yClock, xEnd, yClock);
            lineClock->SetLineWidth(2);
            lineClock->SetLineColor(kGreen+3);
            lineClock->Draw();
            
            // Initial state |0⟩ for each qubit of the clock
            TLatex *stateClock = new TLatex(xStart - 0.035, yClock - 0.015, "|0#GT_{C}");
            stateClock->SetNDC();
            stateClock->SetTextFont(62);
            stateClock->SetTextSize(0.05);
            stateClock->SetTextColor(kGreen+3);
            stateClock->Draw();

            if (microStep >= 9) {
                // Background box for the gate
                TBox *hBox = new TBox(hGateX1, yClock - hGateHalfHeight, hGateX2, yClock + hGateHalfHeight);
                hBox->SetFillColor(kCyan-10);
                hBox->SetLineColor(kCyan+4);
                hBox->SetLineWidth(1.5);
                hBox->Draw("l");
                
                // Letter 'H' inside the box
                TLatex *hText = new TLatex((hGateX1 + hGateX2)/2.0, yClock, "H");
                hText->SetTextAlign(22);
                hText->SetTextFont(62);
                hText->SetTextSize(0.06);
                hText->SetTextColor(kCyan+4);
                hText->Draw();

            }

        }
        
        // BOTTOM LINE: Qubit Ancilla
        TLine *lineAncilla = new TLine(xStart, yAncilla, xEnd, yAncilla);
        lineAncilla->SetLineWidth(2);
        lineAncilla->SetLineColor(kCyan+3);
        lineAncilla->Draw();
        
        // Initial state |0⟩ for the ancilla
        TLatex *stateAncilla = new TLatex(xStart - 0.035, yAncilla - 0.015, "|0#GT_{A}");
        stateAncilla->SetNDC();
        stateAncilla->SetTextFont(62);
        stateAncilla->SetTextSize(0.05);
        stateAncilla->SetTextColor(kCyan+3);
        stateAncilla->Draw();
        
        //? Rendering step b.10: Controlled-U operations
        if (microStep >= 10) {

            // Draw controlled-U gates for each clock qubit
            for (Int_t i = 0; i < fClockQubitsM; i++) {
                Double_t yClock = yClockStart - (i * yClockSpacing);
                Double_t uGateX = uGateXStart + (i * uGateSpacing);
                
                // Calculate the power: 2^i
                Int_t power = TMath::Power(2, i);
                
                // Draw control dot on clock qubit line
                TMarker *controlDot = new TMarker(uGateX + uGateWidth/2.0, yClock, 20);
                controlDot->SetMarkerSize(1.5);
                controlDot->SetMarkerColor(kBlue+4);
                controlDot->SetMarkerStyle(20);
                controlDot->Draw();
                
                // Draw vertical line from control to U gate
                TLine *controlLine = new TLine(uGateX + uGateWidth/2.0, yClock, 
                    uGateX + uGateWidth/2.0, yIndex);
                controlLine->SetLineWidth(1);
                controlLine->SetLineColor(kBlue+4);
                controlLine->Draw();
                
                // Draw U gate box on index register line
                TBox *uBox = new TBox(uGateX, yIndex - uGateHeight/2.0, 
                    uGateX + uGateWidth, yIndex + uGateHeight/2.0);
                uBox->SetFillColor(kBlue-10);
                uBox->SetLineColor(kBlue+4);
                uBox->SetLineWidth(1.5);
                uBox->Draw("l");
                
                // Label U gate with power notation
                TString uLabel;
                if (i == 0) {
                    uLabel = "U^{2^{0}}=e^{iA#tau(1)}";
                } else if (i == 1) {
                    uLabel = "U^{2^{1}}=e^{iA#tau(2)}";
                } else {
                    uLabel = TString::Format("U^{2^{%d}}=e^{iA#tau(%d)}", i, power);
                }
                
                TLatex *uText = new TLatex(uGateX + uGateWidth/2.0, yIndex, uLabel);
                uText->SetTextAlign(22);
                uText->SetTextFont(42);
                uText->SetTextSize(0.05);
                uText->SetTextColor(kBlue+4);
                uText->Draw();
    
            }

        }
        
        //? Rendering step 8.11: IQFT box at the end of clock register lines
        if (microStep >= 11) {

            // Calculate bounds for the IQFT box spanning all clock qubits
            Double_t yClockTop = yClockStart + hGateHalfHeight;      // Top of first clock qubit line
            Double_t yClockBottom = yClockStart - ((fClockQubitsM - 1) * yClockSpacing) - hGateHalfHeight; // Bottom of last clock qubit line
            
            // Calculate end position of last Controlled-U gate
            Int_t lastUIndex = fClockQubitsM - 1;
            Double_t lastUGateX = uGateXStart + (lastUIndex * uGateSpacing);
            Double_t uGatesEndX = lastUGateX + uGateWidth;
            
            Double_t iqftWidth = 0.05;
            Double_t xIQFT = uGatesEndX + 0.02;  // Small gap after last U gate
            Double_t xIQFTEnd = xIQFT + iqftWidth;
            
            // Draw IQFT box spanning all clock register lines
            TBox *iqftBox = new TBox(xIQFT, yClockBottom, xIQFTEnd, yClockTop);
            iqftBox->SetFillColor(kViolet-9);
            iqftBox->SetLineColor(kViolet+3);
            iqftBox->SetLineWidth(1.5);
            iqftBox->Draw("l");
            
            // Vertical "IQFT" label 
            TLatex *iqftLabel = new TLatex(xIQFT + iqftWidth/2.0, (yClockTop + yClockBottom)/2.0, "IQFT");
            iqftLabel->SetTextAlign(22);
            iqftLabel->SetTextFont(62);
            iqftLabel->SetTextSize(0.05);
            iqftLabel->SetTextColor(kViolet+3);
            iqftLabel->SetTextAngle(90);  // Vertical text
            iqftLabel->Draw();
            
            // QPE dashed bracket: from H gates to IQFT, covering H + U gates + IQFT vertically
            Double_t xQPE_Left = hGateX1;
            Double_t xQPE_Right = xIQFTEnd;
            
            // Vertical bounds: from top of U gates on index register to bottom of clock register
            Double_t yQPE_Top = yIndex + uGateHeight/2.0 + 0.02;     // Top of U gates on index line
            Double_t yQPE_Bottom = yClockBottom - 0.02;               // Bottom of last clock line
            
            // Draw dashed bracket (no fill, dashed lines)
            // Top edge - dashed
            TLine *qpeTop = new TLine(xQPE_Left, yQPE_Top, xQPE_Right, yQPE_Top);
            qpeTop->SetLineColor(kOrange+3);
            qpeTop->SetLineWidth(2);
            qpeTop->SetLineStyle(2);  // Dashed line
            qpeTop->Draw();
            
            // Bottom edge - dashed
            TLine *qpeBottom = new TLine(xQPE_Left, yQPE_Bottom, xQPE_Right, yQPE_Bottom);
            qpeBottom->SetLineColor(kOrange+3);
            qpeBottom->SetLineWidth(2);
            qpeBottom->SetLineStyle(2);  // Dashed line
            qpeBottom->Draw();
            
            // Left edge - dashed
            TLine *qpeLeft = new TLine(xQPE_Left, yQPE_Top, xQPE_Left, yQPE_Bottom);
            qpeLeft->SetLineColor(kOrange+3);
            qpeLeft->SetLineWidth(2);
            qpeLeft->SetLineStyle(2);  // Dashed line
            qpeLeft->Draw();
            
            // Right edge - dashed
            TLine *qpeRight = new TLine(xQPE_Right, yQPE_Top, xQPE_Right, yQPE_Bottom);
            qpeRight->SetLineColor(kOrange+3);
            qpeRight->SetLineWidth(2);
            qpeRight->SetLineStyle(2);  // Dashed line
            qpeRight->Draw();
            
            // QPE label at the center of the bottom edge
            TLatex *qpeLabel = new TLatex((xQPE_Left + xQPE_Right)/2.0, yQPE_Bottom - 0.015, "QPE");
            qpeLabel->SetTextAlign(23);  // Centered, bottom-aligned
            qpeLabel->SetTextFont(62);
            qpeLabel->SetTextSize(0.05);
            qpeLabel->SetTextColor(kOrange+3);
            qpeLabel->Draw();

            //? Rendering step 8.12: Controlled-Ry(θ) gate converging from all clock qubits to ancilla
            if (microStep >= 12) {

                // Calculate X position for the Ry gate: placed after the IQFT box with a small gap
                Double_t xRyGate = xIQFTEnd;
                Double_t ryGateWidth = 0.10;
                
                // Draw control dots on each clock qubit line and vertical lines converging to ancilla
                for (Int_t i = 0; i < fClockQubitsM; i++) {
                    Double_t yClock = yClockStart - (i * yClockSpacing);
                    
                    // Draw control dot on clock qubit line at the Ry gate X position
                    TMarker *ryControlDot = new TMarker(xRyGate + ryGateWidth/2.0, yClock, 20);
                    ryControlDot->SetMarkerSize(1.5);
                    ryControlDot->SetMarkerColor(kRed+3);
                    ryControlDot->SetMarkerStyle(20);
                    ryControlDot->Draw();
                    
                    // Draw vertical line from control dot down to the ancilla line
                    TLine *ryControlLine = new TLine(xRyGate + ryGateWidth/2.0, yClock, 
                        xRyGate + ryGateWidth/2.0, yAncilla);
                    ryControlLine->SetLineWidth(1.5);
                    ryControlLine->SetLineColor(kRed+3);
                    ryControlLine->SetLineStyle(1);
                    ryControlLine->Draw();
                }
                
                // Draw the Ry(θ) gate box on the ancilla line
                Double_t yRyTop = yAncilla + 0.04;      // Extend slightly above top ancilla line
                Double_t yRyBottom = yAncilla - 0.04;   // Extend slightly below ancilla line
                
                TBox *ryBox = new TBox(xRyGate, yRyBottom, xRyGate + ryGateWidth, yRyTop);
                ryBox->SetFillColor(kRed-10);
                ryBox->SetLineColor(kRed+3);
                ryBox->SetLineWidth(1.5);
                ryBox->Draw("l");
                
                // Label Ry(θ) inside the box
                TLatex *ryText = new TLatex(xRyGate + ryGateWidth/2.0, (yRyTop + yRyBottom)/2.0, "R_{y}(#theta)");
                ryText->SetTextAlign(22);
                ryText->SetTextFont(62);
                ryText->SetTextSize(0.05);
                ryText->SetTextColor(kRed+3);
                ryText->Draw();

                //? Rendering step 8.13: IQPE box spanning index and all clock qubit lines
                if (microStep >= 13) {

                    // Calculate X position for the IQPE box: placed after the Ry gate with a small gap
                    Double_t iqpeWidth = 0.05;
                    Double_t xIQPE = xRyGate + ryGateWidth;  // Small gap after Ry gate
                    Double_t xIQPEEnd = xIQPE + iqpeWidth;
                    
                    // Vertical bounds: from index register line down to last clock qubit line
                    // Use same bounds as the QPE dashed bracket for visual consistency
                    Double_t yIQPE_Top = yIndex + uGateHeight/2.0 + 0.02;     // Top of U gates on index line
                    Double_t yIQPE_Bottom = yClockBottom - 0.02;              // Bottom of last clock line
                    
                    // Draw IQPE box spanning index register and all clock register lines
                    TBox *iqpeBox = new TBox(xIQPE, yIQPE_Bottom, xIQPEEnd, yIQPE_Top);
                    iqpeBox->SetFillColor(kOrange-9);
                    iqpeBox->SetLineColor(kOrange+3);
                    iqpeBox->SetLineWidth(1.5);
                    iqpeBox->Draw("l");
                    
                    // Vertical "IQPE" label inside the box
                    TLatex *iqpeLabel = new TLatex(xIQPE + iqpeWidth/2.0, (yIQPE_Top + yIQPE_Bottom)/2.0, "IQPE");
                    iqpeLabel->SetTextAlign(22);
                    iqpeLabel->SetTextFont(62);
                    iqpeLabel->SetTextSize(0.05);
                    iqpeLabel->SetTextColor(kOrange+3);
                    iqpeLabel->SetTextAngle(90);
                    iqpeLabel->Draw();

                    //? Rendering step 8.14: Measurement symbol and final state labels
                    if (microStep >= 14) {

                        // --- Measurement symbol on ancilla qubit line (right end) ---
                        Double_t measBoxW = 0.10;   // Width of measurement box
                        Double_t measBoxH = 0.10;   // Height of measurement box
                        Double_t xMeas = xEnd - measBoxW - 0.05;  // Place at right end of circuit
                        Double_t xMeasCenter = xMeas + measBoxW/2.0;
                        
                        // Measurement box background (light blue fill)
                        TBox *measBox = new TBox(xMeas, yAncilla - measBoxH/2.0, 
                            xMeas + measBoxW, yAncilla + measBoxH/2.0);
                        measBox->SetFillColor(kYellow-9);
                        measBox->SetLineColor(kCyan+4);
                        measBox->SetLineWidth(1.5);
                        measBox->Draw("l");
                        
                        // Semicircle (larger arc from 0 to 180 degrees)
                        Double_t arcRadius = 0.035;
                        TArc *measArc = new TArc(xMeasCenter, yAncilla - 0.025, arcRadius, 0, 180);
                        measArc->SetLineColor(kCyan+4);
                        measArc->SetFillColor(kYellow-9);
                        measArc->SetLineWidth(2);
                        measArc->SetNoEdges();
                        measArc->Draw();
                        
                        // Arrow more vertical, crossing the semicircle
                        TArrow *measArrow = new TArrow(xMeasCenter - 0.005, yAncilla - 0.030,
                            xMeasCenter + 0.005, yAncilla + 0.040, 0.010, "|>");
                        measArrow->SetLineColor(kCyan+4);
                        measArrow->SetLineWidth(2);
                        measArrow->SetFillColor(kCyan+4);
                        measArrow->Draw();
                        
                        // --- Final state labels at the right end of each line ---
                        
                        // Clock qubits: |0⟩ at the end of each clock line
                        for (Int_t i = 0; i < fClockQubitsM; i++) {
                            Double_t yClock = yClockStart - (i * yClockSpacing);
                            TLatex *finalClock = new TLatex(xEnd + 0.01, yClock - 0.015, "|0#GT");
                            finalClock->SetNDC();
                            finalClock->SetTextFont(62);
                            finalClock->SetTextSize(0.05);
                            finalClock->SetTextColor(kGreen+3);
                            finalClock->Draw();
                        }
                        
                        // Ancilla qubit: |1⟩ at the end
                        TLatex *finalAncilla = new TLatex(xEnd + 0.01, yAncilla - 0.015, "|1#GT");
                        finalAncilla->SetNDC();
                        finalAncilla->SetTextFont(62);
                        finalAncilla->SetTextSize(0.05);
                        finalAncilla->SetTextColor(kCyan+3);
                        finalAncilla->Draw();
                        
                        // Index register: |x⟩ at the end
                        TLatex *finalIndex = new TLatex(xEnd + 0.01, yIndex - 0.015, "|x#GT");
                        finalIndex->SetNDC();
                        finalIndex->SetTextFont(62);
                        finalIndex->SetTextSize(0.05);
                        finalIndex->SetTextColor(kBlue+3);
                        finalIndex->Draw();

                    }

                }

            }

        }

    }

}

void QHHLA_SoftEdu::DrawGraph_Step8(Int_t microStep){

    TCanvas *c = ECanvasGRAPH->GetCanvas();
    if (!c) return;
    c->cd();
    c->Clear();
    DrawStepTitle(c);       // Title box at the top
    DrawProgressBar(c);     // Progress bar at the bottom-right

    //? Rendering step 8.15: Ancilla Measurement Probabilities
    if (microStep == 15) {

        // Equation of state before measurement 
        TPaveText *eqBox = new TPaveText(0.01, 0.01, 0.55, 0.12, "NDC");
        eqBox->SetFillColor(kWhite);
        eqBox->SetBorderSize(1);
        eqBox->SetLineColor(kGray+1);
        eqBox->SetShadowColor(0);
        eqBox->SetTextAlign(22);
        eqBox->SetTextSize(0.038);
        eqBox->SetTextFont(132);
        eqBox->SetTextColor(kRed+3);
        eqBox->SetMargin(0.03);
        
        TString eqText= "|#Psi_{6}#GT = #sum_{j=1}^{N} #beta_{j} #sqrt{ 1 - #frac{C^{2}}{#lambda_{j}^{2}} } |u_{j}#GT_{I} |0#GT " 
                        " + #sum_{j=1}^{N} #beta_{j} #frac{C}{#lambda_{j}} |u_{j}#GT_{I} |1#GT";
        eqBox->AddText(eqText.Data());
        eqBox->Draw();

        // Histogram pad
        TPad *plotPad = new TPad("plotPadStep8", "Measurement Region", 0.01, 0.12, 0.99, 0.88);
        plotPad->Draw();
        plotPad->cd();
        plotPad->SetBottomMargin(0.18); 
        plotPad->SetTopMargin(0.12);
        plotPad->SetGrid(1, 1); 

        // 2-bin histogram: |0>_A and |1>_A
        Double_t p0 = 1.0 - fProb1;   // Probability of measuring |0>
        Double_t p1 = fProb1;         // Probability of measuring |1>

        TH1F *hist = new TH1F("probHistStep8", 
                            ";Ancilla State |a#GT_{A};Probability P", 
                            2, 0, 2);
        hist->SetDirectory(0); 
        hist->SetStats(0);     
        hist->SetMinimum(0.0);   
        hist->SetMaximum(1.15);

        hist->SetBinContent(1, p0);
        hist->SetBinContent(2, p1);

        // X-axis labels
        hist->GetXaxis()->SetBinLabel(1, "|0#GT_{A}");
        hist->GetXaxis()->SetBinLabel(2, "|1#GT_{A}");
        hist->GetXaxis()->SetLabelSize(0.07);
        hist->GetXaxis()->SetTitleSize(0.045); 
        hist->GetXaxis()->SetLabelFont(42);
        hist->GetXaxis()->SetTickLength(0);   
        hist->GetXaxis()->SetTitleOffset(1.2);

        hist->GetYaxis()->SetTitleSize(0.04);
        hist->GetYaxis()->SetTitleOffset(1.1);
        hist->GetYaxis()->SetLabelSize(0.04);

        // Bar style (distinctive color for step 8)
        hist->SetFillColor(kSpring-9);
        hist->SetFillStyle(1001);
        hist->SetLineColor(kSpring-7);
        hist->SetLineWidth(2);
        hist->SetBarOffset(0.2); 
        hist->SetBarWidth(0.6);  

        hist->Draw("BAR");

        // Numeric values ​​on each bar 
        TLatex *label0 = new TLatex(0.5, p0 + 0.04, TString::Format("%.2f", p0).Data());
        label0->SetTextAlign(22); 
        label0->SetTextSize(0.04); 
        label0->SetTextColor(kSpring-7);
        label0->Draw();

        TLatex *label1 = new TLatex(1.5, p1 + 0.04, TString::Format("%.2f", p1).Data());
        label1->SetTextAlign(22); 
        label1->SetTextSize(0.04); 
        label1->SetTextColor(kSpring-7);
        label1->Draw();

        // Title of the graph
        TLatex *titleText = new TLatex(0.5, 0.93, 
            "#color[600]{#font[62]{Ancilla Measurement Probabilities}}");
        titleText->SetNDC();
        titleText->SetTextAlign(22);
        titleText->SetTextSize(0.050);
        titleText->SetTextColor(kBlack);
        titleText->Draw();

        // Yellow summary box for probabilities
        TPaveText *probBox = new TPaveText(0.80, 0.75, 0.95, 0.93, "NDC");
        probBox->SetFillColor(kYellow-9);
        probBox->SetBorderSize(1);
        probBox->SetLineColor(kOrange-2);
        probBox->SetTextAlign(12);
        probBox->SetTextSize(0.035);
        probBox->SetTextFont(42);
        probBox->SetMargin(0.08);

        probBox->AddText(TString::Format("     P(|0#GT_{A}) = %.2f", p0).Data());
        probBox->AddText(TString::Format("     P(|1#GT_{A}) = %.2f", p1).Data());
        probBox->AddLine(0.1, 0.35, 0.9, 0.35); 
        probBox->AddText("Total Sum = 1.00");
        probBox->Draw();

    }

    //? Rendering step 8.16: Comparison of classical vs. quantum vectors (Step 1 style)
    if (microStep >= 16) {

        // ===== LOCKING MECHANISM FOR COMPLEX MATRICES =====
        if (fIsComplexMatrix) {
            TPaveText *msg = new TPaveText(0.1, 0.25, 0.9, 0.75, "NDC");
            msg->SetFillColor(kYellow-9);
            msg->SetBorderSize(2);
            msg->SetShadowColor(kGray+2);
            msg->SetTextAlign(22);
            msg->SetTextFont(42);
            msg->SetTextSize(0.045);
            msg->SetMargin(0.05);
            msg->AddText(" ");
            msg->AddText("#font[62]{#color[600]{#scale[1.3]{Complex Matrix Mode}}}");
            msg->AddText(" ");
            msg->AddText("\\text{The eigenvectors have imaginary components and live in } \\mathbb{C}^{2}.");
            msg->AddText("\\text{They cannot be represented in a real 2D Cartesian plane } \\mathbb{R}^{2}.");
            msg->AddText("Please refer to the MATH and MATRIX tabs for the algebraic representation.");
            msg->AddText(" ");
            msg->Draw();
            c->Modified(); 
            c->Update(); 
            c->cd();
            return;
        }

        // Equation box at the bottom
        TPaveText *ptEq = new TPaveText(0.01, 0.01, 0.35, 0.12, "NDC");
        ptEq->SetFillColor(kWhite);
        ptEq->SetBorderSize(1);
        ptEq->SetShadowColor(0);
        ptEq->SetTextAlign(22);
        ptEq->SetTextSize(0.035);
        ptEq->SetTextFont(42);
        ptEq->SetMargin(0.03);
        ptEq->AddText(TString::Format(
            "#color[2]{#vec{x}_{classical}} = (%.2f, %.2f)", 
            fVectorCX[0].Re(), fVectorCX[1].Re()).Data()
        );
        ptEq->AddText(TString::Format(
            "#color[4]{#vec{x}_{quantum}}  = (%.2f, %.2f)", 
            fVectorQX[0].Re(), fVectorQX[1].Re()).Data()
        );
        ptEq->Draw();

        // Creation of the graphing container
        TPad *plotPad = new TPad("plotPadStep8Vec", "Solution Vectors", 
                                0.01, 0.12, 0.99, 0.88);
        plotPad->Draw();
        plotPad->cd();
        plotPad->SetGrid();

        // Vector coordinates
        Double_t cx_x = fVectorCX[0].Re(); 
        Double_t cx_y = fVectorCX[1].Re();
        Double_t qx_x = fVectorQX[0].Re(); 
        Double_t qx_y = fVectorQX[1].Re();

        // Automatic scaling of the frame so that both vectors fit
        Double_t max_val = std::max({
            std::abs(cx_x), std::abs(cx_y), 
            std::abs(qx_x), std::abs(qx_y), 1.0
        }); 

        TH1F *frame = plotPad->DrawFrame(-max_val * 1.3, -max_val * 1.3, 
                                          max_val * 1.3,  max_val * 1.3);
        frame->SetStats(0);

        // Cartesian axes
        TLine *axisX = new TLine(-max_val * 1.3, 0, max_val * 1.3, 0); 
        axisX->SetLineColor(13); 
        axisX->Draw();
        TLine *axisY = new TLine(0, -max_val * 1.3, 0, max_val * 1.3); 
        axisY->SetLineColor(13); 
        axisY->Draw();

        // Vector solución CLÁSICO (rojo, estilo del paso 1)
        TArrow *arr_cx = new TArrow(0, 0, cx_x, cx_y, 0.012, "|>");
        arr_cx->SetLineColor(kRed); 
        arr_cx->SetFillColor(kRed); 
        arr_cx->SetLineWidth(3);
        arr_cx->Draw();

        TLatex *texCX = new TLatex(cx_x * 1.08, cx_y * 1.08, "#color[2]{#vec{x}_{classical}}"); 
        texCX->SetTextSize(0.05); 
        texCX->Draw();

        if (microStep >= 17) {

            // QUANTUM solution vector (blue, superimposed)
            TArrow *arr_qx = new TArrow(0, 0, qx_x, qx_y, 0.012, "|>");
            arr_qx->SetLineColor(kAzure+2); 
            arr_qx->SetFillColor(kAzure+2); 
            arr_qx->SetLineWidth(3);
            arr_qx->Draw();

            TLatex *texQX = new TLatex(qx_x * 1.08, qx_y * 1.08, "#color[4]{#vec{x}_{quantum}}"); 
            texQX->SetTextSize(0.05); 
            texQX->Draw();

        }

    }

    c->Modified();
    c->Update();
    c->cd();

}

//* ============================== -DESTRUCTOR- ===============================
QHHLA_SoftEdu::~QHHLA_SoftEdu() {

    Cleanup();

}

//* ================================== -MAIN- =================================
int main(int argc, char **argv) {

    TApplication theApp("QHHLA_SoftEdu", &argc, argv);
    new QHHLA_SoftEdu(gClient->GetRoot(), 935, 660);
    theApp.Run();
    return 0;

}

ClassImp(QHHLA_SoftEdu);
