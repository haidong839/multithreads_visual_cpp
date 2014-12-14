#pragma once

#include <windows.h> 
#include <iostream>

namespace worker2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		int highestPercentageReached;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
			 BackgroundWorker^ worker;
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			InitializeBackgoundWorker();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 


	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(81, 47);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(84, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(33, 94);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(203, 23);
			this->progressBar1->Step = 1;
			this->progressBar1->TabIndex = 1;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(260, 141);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"worker test";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		void backgroundWorker1_DoWork( Object^ sender, DoWorkEventArgs^ e )
		{
			worker = dynamic_cast<BackgroundWorker^>(sender);
			worker->WorkerReportsProgress = true;

			e->Result = doSomeWork(worker, e );
		}

		void backgroundWorker1_RunWorkerCompleted( Object^ /*sender*/, RunWorkerCompletedEventArgs^ e )
		{
			MessageBox::Show( "Complete" );
		}

		// This event handler updates the progress bar. 
		void backgroundWorker1_ProgressChanged( Object^ /*sender*/, ProgressChangedEventArgs^ e )
		{
			this->progressBar1->Value = e->ProgressPercentage;
		}

		void InitializeBackgoundWorker()
		{
			highestPercentageReached = 0;
			backgroundWorker1->DoWork += gcnew DoWorkEventHandler( this, &Form1::backgroundWorker1_DoWork );
			backgroundWorker1->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &Form1::backgroundWorker1_RunWorkerCompleted );
			backgroundWorker1->ProgressChanged += gcnew ProgressChangedEventHandler( this, &Form1::backgroundWorker1_ProgressChanged );
		}

		long doSomeWork( BackgroundWorker^ worker, DoWorkEventArgs ^ e )
		{		
			Bitmap^ bitmap1  = dynamic_cast<Bitmap^>(Bitmap::FromFile("D:\\image1.jpg"));
			for(int ii=1; ii<100;ii++){				
				bitmap1->RotateFlip( RotateFlipType::Rotate90FlipY );
				bitmap1->Save("D:\\image22" + ii + ".jpg");	
				if(ii%11 == 0)
					worker->ReportProgress( ii );
			}
			worker->ReportProgress( 100);
			return 0;
		}


	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->button1->Enabled = false;
				 backgroundWorker1->RunWorkerAsync( );				 
			 }
	};
}

