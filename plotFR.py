import ROOT,os

# ______________________________________________________________________________ ||
#inputElPath         = "Data/FakeRate_Vukasin_190326/FR_WZremoved_17.root"
#inputMuPath         = "Data/FakeRate_Vukasin_190326/FR_WZremoved_17.root"
#
#histNameMuEB        = "Data_FRmu_EB"
#histNameMuEE        = "Data_FRmu_EE"
#histNameElEB        = "Data_FRel_EB"
#histNameElEE        = "Data_FRel_EE"
#
#outputDir           = "/home/lucien/public_html/Higgs/DarkZ/FakeRate/20190327_plotFR_2017/"
#factor              = 1.2
#legPos              = [0.1,0.75,0.35,0.9]
#tag                 = "_2017"

inputElPath         = "Data/FakeRate_Vukasin_190301/fakeRates_el_2016.root"
inputMuPath         = "Data/FakeRate_Vukasin_190301/fakeRates_mu_2016.root"

histNameMuEB        = "h1D_FRmu_EB"
histNameMuEE        = "h1D_FRmu_EE"
histNameElEB        = "h1D_FRel_EB"
histNameElEE        = "h1D_FRel_EE"

outputDir           = "/home/lucien/public_html/Higgs/DarkZ/FakeRate/20190327_plotFR_2016/"
factor              = 1.2
legPos              = [0.1,0.75,0.35,0.9]
tag                 = "_2016"

# ______________________________________________________________________________ ||
ROOT.gROOT.SetBatch(ROOT.kTRUE)

# ______________________________________________________________________________ ||
inputElFile = ROOT.TFile(inputElPath)
inputMuFile = ROOT.TFile(inputMuPath)
histElEB = inputElFile.Get(histNameElEB)
histElEE = inputElFile.Get(histNameElEE)
histMuEB = inputMuFile.Get(histNameMuEB)
histMuEE = inputMuFile.Get(histNameMuEE)

# ______________________________________________________________________________ ||
histMuEB.SetLineColor(ROOT.kRed)
histMuEE.SetLineColor(ROOT.kBlue)
histMuEB.SetStats(0)
histMuEE.SetStats(0)
histMuEB.SetTitle("Muon Fake Rate")
histMuEE.SetTitle("Muon Fake Rate")
maximum = max([histMuEB.GetMaximum(),histMuEE.GetMaximum(),])
histMuEB.GetYaxis().SetRangeUser(0.,1.2*maximum)

c = ROOT.TCanvas()

leg = ROOT.TLegend(*legPos)
leg.AddEntry(histMuEB,"Barrel")
leg.AddEntry(histMuEE,"Endcap")

histMuEB.Draw()
histMuEE.Draw("same")
leg.Draw("same")

c.SaveAs(outputDir+"FR_mu%s.pdf"%tag)

# ______________________________________________________________________________ ||
histElEB.SetLineColor(ROOT.kRed)
histElEE.SetLineColor(ROOT.kBlue)
histElEB.SetStats(0)
histElEE.SetStats(0)
histElEB.SetTitle("Electron Fake Rate")
histElEE.SetTitle("Electron Fake Rate")
maximum = max([histElEB.GetMaximum(),histElEE.GetMaximum(),])
histElEB.GetYaxis().SetRangeUser(0.,1.2*maximum)

c = ROOT.TCanvas()

leg = ROOT.TLegend(*legPos)
leg.AddEntry(histElEB,"Barrel")
leg.AddEntry(histElEE,"Endcap")

histElEB.Draw()
histElEE.Draw("same")
leg.Draw("same")

c.SaveAs(outputDir+"FR_el%s.pdf"%tag)
