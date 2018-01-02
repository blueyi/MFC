#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

enum GlobalProperty{
	PropEnable3D=1,
	PropWallWidth,
	PropAxisShowState,
	PropDataLabelShowState,
	PropLegendShowState,//
	PropPointDepth,
	PropGapDepth,
	PropPerspective,
	PropRotateX,
	PropRotateY,
	PropGraphicsAntiliasing,
	PropTextAntiliasingQuality,
	PropChartPalette,
};
enum FormatCommandType{
	Format_Text=1,
	Format_ShapeColor1,
	Format_ShapeColor2,
	Format_ShapeGradient,
	Format_ShapeHatch,
	Format_OutlineColor,
	Format_OutlineStyle,
	Format_OutlineSize,
	Format_SizeWidth,
	Format_SizeLength,
	Format_OrientationAlignment,
	Format_OrientationDocking,
	Format_OrientationReverse,
	Format_FontName,
	Format_FontSize,
	Format_FontBold,
	Format_FontItalic,
	Format_FontUnderline,
	Format_FontDeleted,
	Format_FontLeft,
	Format_FontCenter,
	Format_FontRight
};
enum FormatElement{
	ElementChartTitle=0,
	ElementChartArea,
	ElementChartLegend,
	ElementChartXAxisTitle,
	ElementChartYAxisTitle
};
namespace ChartProvider {

	/// <summary>
	/// Summary for ChartProviderControl
	/// </summary>
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	public ref class ChartProviderControl : public System::Windows::Forms::UserControl
	{
	public:
		ChartProviderControl(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ChartProviderControl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(0, 0);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(344, 229);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			title1->DockedToChartArea = L"ChartArea1";
			title1->IsDockedInsideChartArea = false;
			title1->Name = L"Title1";
			title1->Text = L"Title";
			this->chart1->Titles->Add(title1);
			// 
			// ChartProviderControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->chart1);
			this->Name = L"ChartProviderControl";
			this->Size = System::Drawing::Size(344, 229);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public:
		void addNewPoint(System::String^ seriesName,System::String^ xPointLabel, System::Double yTimeValue);
		void resetChart();
		void setupNewSeries(System::String^ seriesName,int seriesType);
		void setCustomPropety(System::String^seriesName,System::String^ customProperty)
		{
			this->chart1->Series[seriesName]->CustomProperties=customProperty;
			//CustomProperties
		}
		void setElementLayout(int elementType,int layout)
		{
			if(elementType==1)
				//Chart Title :
			{
				System::Windows::Forms::DataVisualization::Charting::Title^  title1=this->chart1->Titles[0];
				if(layout==0)
					title1->Visible = false;
				if(layout==1)
				{
					title1->Visible=true;
					title1->IsDockedInsideChartArea = false;
				}
				if(layout==2)
				{
					title1->Visible=true;
					title1->IsDockedInsideChartArea = true;
				}
			}
		}
		void setGlobalProperty(int propertyID,int value);
		int getGlobalProperty(int propertyID);
		void setChartTypeForAllSeries(int seriesType);
		void setFormat(int FormatElement, int FormatCommand,System::String^ value);
		void saveImageToFile(System::String^ filePath,System::String^ format);
		void printPreview(int command);
		void setSeriesColor(System::String^ seriesName,System::String^ seriesColor);
	};
}
