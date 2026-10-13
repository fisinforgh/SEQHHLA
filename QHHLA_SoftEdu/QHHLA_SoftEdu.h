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

#ifndef QHHLA_SoftEdu_H
#define QHHLA_SoftEdu_H

#include "TGDockableFrame.h"
#include "TGMdiDecorFrame.h"
#include "TG3DLine.h"
#include "TGMdiFrame.h"
#include "TGMdiMainFrame.h"
#include "TGMdiMenu.h"
#include "TGColorDialog.h"
#include "TGColorSelect.h"
#include "TGListBox.h"
#include "TGNumberEntry.h"
#include "TGScrollBar.h"
#include "TGComboBox.h"
#include "TGuiBldHintsEditor.h"
#include "TGuiBldNameFrame.h"
#include "TGFrame.h"
#include "TGMenu.h"
#include "TGFileDialog.h"
#include "TGShutter.h"
#include "TGButtonGroup.h"
#include "TGCanvas.h"
#include "TGFSContainer.h"
#include "TGuiBldEditor.h"
#include "TGButton.h"
#include "TRootContextMenu.h"
#include "TGFSComboBox.h"
#include "TGLabel.h"
#include "TGMsgBox.h"
#include "TRootGuiBuilder.h"
#include "TGTab.h"
#include "TGListView.h"
#include "TGSplitter.h"
#include "TGStatusBar.h"
#include "TGListTree.h"
#include "TGuiBldGeometryFrame.h"
#include "TGToolTip.h"
#include "TGToolBar.h"
#include "TRootEmbeddedCanvas.h"
#include "TCanvas.h"
#include "TGuiBldDragManager.h"
#include "TPaveText.h"
#include "Rtypes.h"
#include "Riostream.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TGMsgBox.h"
#include "TLatex.h"
#include "TMarker.h"
#include "TMath.h"
#include "TMathText.h"
#include "TLine.h"
#include "TBox.h"
#include "TEllipse.h"
#include "TH1F.h"
#include "TArrow.h"
#include "TLegend.h"
#include "TArc.h"
#include "TGeoManager.h"
#include "TStyle.h"

#include <TComplex.h>
#include <vector>

class QHHLA_SoftEdu : public TGMainFrame { 

    private:
        //* ========== State Variables ==========
        Int_t m_macroStep;            // Control the general step (1 to 8)
        Int_t m_microStep;            // Control the internal details of each step
        Bool_t m_isRunning;           // Checks if the algorithm is active
        Int_t m_maxMicroSteps[9];     // Stores the maximum number of substeps (Indices 0 to 8)

        //* ========== Algebraic Structures (HHL Data) ==========
        TComplex fMatrixA[2][2];      // User's 2x2 complex matrix
        TComplex fVectorB[2];         // User's Vector b
        TComplex fVectorCX[4];        // Classical solution (4 entries: 2 unnormalized, 2 normalized)
        TComplex fVectorQX[2];        // Quantum solution

        //* ========== HHL Mathematical Data (calculated in DoStart) ==========
        Double_t fNormB, fNormU;       // ||b||, ||u||
        Double_t fLambda1, fLambda2;   // λ₁, λ₂  (real)
        TComplex fEigenvectors[2][2];  // |u₁⟩, |u₂⟩ (complex)
        TComplex fBeta1, fBeta2;       // β₁, β₂ (complex)

        Double_t fNormUSq;             // ||u||² (real)
        Double_t fIntDenomSq;          // √||u||² ||b||² (real)
        TComplex fbetaNum1, fbetaNum2; // Numerators of β (complex)
        Bool_t   fIsComplexMatrix;     // TRUE if the matrix has an imaginary part
        
        Double_t fAbsBetaNum2;         // Absolute value of the numerator of β₂ (real)
        TString  fSignBeta2;           // Sign of β₂ for display purposes

        Double_t fTimeScale;           // τ (time scale factor)
        Double_t fDemTau;              // Denominator for τ = 2π / 2^k
        Double_t fScaleFactor;         // Scale factor S = 1 / 2^k
        Double_t fScaledLambda1;       // QPE Phase 1 normalized [0, 1)
        Double_t fScaledLambda2;       // QPE Phase 2 normalized [0, 1)

        Int_t    fClockQubitsM;        // m (clock register qubits)
        Int_t    ftotalStates;         // m² total states 
        TString  fBinLambda1;          // Fractional binary representation λ₁
        TString  fBinLambda2;          // Fractional binary representation λ₂
        
        // Stores the phases in text for each eigenvalue and t-value
        std::vector<std::vector<TString>> fPhaseStrings; 

        Double_t fmappedLambda1;       // Mapped λ₁ to [0, 1)
        Double_t fmappedLambda2;       // Mapped λ₂ to [0, 1)
        Double_t fLambdaQPE1;          // Estimated eigenvalue1
        Double_t fLambdaQPE2;          // Estimated eigenvalue2
        
        Double_t fC;                   // Const C ≤ min|λⱼ|
        TVectorD fThetaAngles;         // θⱼ = 2arcsin(C/λⱼ)

        Double_t fProb1;               // Success Probability Ancilla |1⟩
        Double_t fNGlobal;             // Quantum normalization constant


        //* ========== CONCEPTS AND EXPLANATIONS ==========
        void AddConceptLines(TPaveText *pt, const TString& text);
        TString GetStepTitle(Int_t step);
        TString GetOverviewText(Int_t step, Int_t microStep);
        TString GetMathText(Int_t step, Int_t microStep);
        TString GetMatrixText(Int_t step, Int_t microStep);
        TString GetCircuitText(Int_t step, Int_t microStep);
        TString GetGraphText(Int_t step, Int_t microStep);

        //* ========== METHODS OF RENDERING ==========
        void UpdateVisuals();      // Central Rendering Director
        void DrawMathTab();        // Draw in ECanvasMATH
        void DrawMatrixTab();      // Draw in ECanvasMATRIX
        void DrawCircuitTab();     // Draw in ECanvasCIRCUIT
        void DrawGraphTab();       // Draw in ECanvasGRAPH

        //* ========== GLOBAL VISUAL AND CORE MATH ELEMENTS ==========
        void DrawStepTitle(TCanvas* canvas);           // Current step title
        void DrawProgressBar(TCanvas* canvas);         // Global progress bar
        void CalculateCoreMath();                      // HHL mathematical calculations
        TString GetStepName(Int_t step);               // Step Name

        //* ========== Modular Drawing Methods ==========
        void DrawMath_Step1(Int_t microStep);
        void DrawMatrix_Step1(Int_t microStep);
        void DrawCircuit_Step1(Int_t microStep);
        void DrawGraph_Step1(Int_t microStep);
        
        void DrawMath_Step2(Int_t microStep);
        void DrawMatrix_Step2(Int_t microStep);
        void DrawCircuit_Step2(Int_t microStep);
        void DrawGraph_Step2(Int_t microStep);

        void DrawMath_Step3(Int_t microStep);
        void DrawMatrix_Step3(Int_t microStep);
        void DrawCircuit_Step3(Int_t microStep);
        void DrawGraph_Step3(Int_t microStep);

        void DrawMath_Step4(Int_t microStep);
        void DrawMatrix_Step4(Int_t microStep);
        void DrawCircuit_Step4(Int_t microStep);
        void DrawGraph_Step4(Int_t microStep);

        void DrawMath_Step5(Int_t microStep);
        void DrawMatrix_Step5(Int_t microStep);
        void DrawCircuit_Step5(Int_t microStep);
        void DrawGraph_Step5(Int_t microStep);

        void DrawMath_Step6(Int_t microStep);
        void DrawMatrix_Step6(Int_t microStep);
        void DrawCircuit_Step6(Int_t microStep);
        void DrawGraph_Step6(Int_t microStep);

        void DrawMath_Step7(Int_t microStep);
        void DrawMatrix_Step7(Int_t microStep);
        void DrawCircuit_Step7(Int_t microStep);
        void DrawGraph_Step7(Int_t microStep);

        void DrawMath_Step8(Int_t microStep);
        void DrawMatrix_Step8(Int_t microStep);
        void DrawCircuit_Step8(Int_t microStep);
        void DrawGraph_Step8(Int_t microStep);
        

        //* ========== DISING GUI ==========
        TGMainFrame *Main;

        TGHorizontalFrame *Hframe1;
        TGHorizontalFrame *Hframe2;

        TGVerticalFrame *Vframe1;
        TGVerticalFrame *Vframe2;
        TGVerticalFrame *Vframe1a;
        TGVerticalFrame *Vframe1b;

        TGIcon *LogoAPP;
        TGIcon *LogoUD;
        TGIcon *LogoFINSIFOR;
        
        TGLabel *MatrixLabel;
        TGLabel *A11Label;
        TGLabel *A12Label;
        TGLabel *A21Label;
        TGLabel *A22Label;
        TGLabel *VectorLabel;
        TGLabel *b1Label;
        TGLabel *b2Label;

        TGGroupFrame *GFrameMENU; 
        
        TGComboBox *A11ComboBox;
        TGComboBox *A12ComboBox;
        TGComboBox *A21ComboBox;
        TGComboBox *A22ComboBox;
        TGComboBox *b1ComboBox;
        TGComboBox *b2ComboBox;

        TGHorizontal3DLine *HDivider;

        TGTextButton *ButtonSTART;
        TGTextButton *ButtonRESET;
        TGTextButton *ButtonHELP;
        TGTextButton *ButtonEXIT;
        TGTextButton *ButtonNEXTSTEP;
        TGTextButton *ButtonPREVSTEP;

        TGPictureButton *PButtonNEXT;
        TGPictureButton *PButtonBACK;
        TGPictureButton *PButtonCONCEPTS;

        TGTab *TabAlls;

        TGCompositeFrame *TabHOME;
        TGCompositeFrame *TabMATH;
        TGCompositeFrame *TabMATRIX;
        TGCompositeFrame *TabCIRCUIT;
        TGCompositeFrame *TabGRAPH;

        TRootEmbeddedCanvas *ECanvasHOME;
        TRootEmbeddedCanvas *ECanvasTitle;
        TRootEmbeddedCanvas *ECanvasMATH;
        TRootEmbeddedCanvas *ECanvasMATRIX;
        TRootEmbeddedCanvas *ECanvasCIRCUIT;
        TRootEmbeddedCanvas *ECanvasGRAPH;

        TPaveText *TPTTitle;

    public:
        QHHLA_SoftEdu(const TGWindow *p, UInt_t w, UInt_t h);
        virtual ~QHHLA_SoftEdu();

        //* ========== Control Methods (Slots) ==========
        void NextMacroStep();
        void PrevMacroStep();
        void NextMicroStep();
        void PrevMicroStep();
        void DoConcepts();
        void DoStart();     
        void DoReset();
        void DoWelcome(); 
        void DoHelp();
        
        //* ========== Helper Methods ==========
        void UpdateNavigationButtons();
        void DisableNavigationButtons();
        void EnableNavigationButtons();  
        TComplex ComboBoxToValue(TGComboBox* cb);
        TString FormatComplex(const TComplex& z);  // Helper for rendering a+bi
        void DecomposeSign(const TString& formatted, TString& outSign, TString& outValue); 
        TString DecimalToBinaryFraction(Double_t decimalValue, Int_t maxBits, Int_t &bitsNeeded);
        TString AngleToAlgebraicString(Double_t angle_rad);


};

#endif
