#pragma once
#include <memory>
namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
	
	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::IO::Ports::SerialPort^ serialPort1;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ start_bt;
	private: System::Windows::Forms::Button^ stop_bt;


	private: System::Windows::Forms::Label^ label1;

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		bool button1_status = false;
		array<Byte> ^frameRTU_arr = gcnew array<Byte>(8);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->start_bt = (gcnew System::Windows::Forms::Button());
			this->stop_bt = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(20) {
				L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6",
					L"COM7", L"COM8", L"COM9", L"COM10", L"COM11", L"COM12", L"COM13", L"COM14", L"COM15", L"COM16", L"COM17", L"COM18", L"COM19",
					L"COM20"
			});
			this->comboBox1->Location = System::Drawing::Point(12, 12);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(167, 21);
			this->comboBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(197, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// start_bt
			// 
			this->start_bt->Enabled = false;
			this->start_bt->Location = System::Drawing::Point(12, 56);
			this->start_bt->Name = L"start_bt";
			this->start_bt->Size = System::Drawing::Size(120, 78);
			this->start_bt->TabIndex = 3;
			this->start_bt->Text = L"Start";
			this->start_bt->UseVisualStyleBackColor = true;
			this->start_bt->Click += gcnew System::EventHandler(this, &Form1::start_bt_Click);
			// 
			// stop_bt
			// 
			this->stop_bt->Enabled = false;
			this->stop_bt->Location = System::Drawing::Point(152, 56);
			this->stop_bt->Name = L"stop_bt";
			this->stop_bt->Size = System::Drawing::Size(120, 78);
			this->stop_bt->TabIndex = 3;
			this->stop_bt->Text = L"Stop";
			this->stop_bt->UseVisualStyleBackColor = true;
			this->stop_bt->Click += gcnew System::EventHandler(this, &Form1::stop_bt_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 137);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(138, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Serial Status: Disconnected";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 156);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->stop_bt);
			this->Controls->Add(this->start_bt);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::formClosing_Func);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	/*03H : read data from register
	06H : write single register
	08H : loop detection
	Address: 0x2000
	Bit 0-1: 
			00B: No function
			01B : Stop
			10B : Run
			11B : Jog + Run
	Bit 2-3: Reserved
	Bit 4-5
			00B: No function
			01B : FWD
			10B : REV
			11B : Change direction
	Bit 6-7
			00B: Comm.forced 1st accel / decel
			01B : Comm.forced 2nd accel / decel
	Bit 8 - 15 Reserved*/
		//ref page 108 in DELTA_IA_MDS-EL_UM_EN_20160308.pdf
	private: void FrameRTU_Get(uint8_t Address, uint8_t Function, uint16_t Data_Addr, uint16_t Data_Cont)
	{
		char frame_nonCheck[6];/* = { 0x01, 0x06, 0x01, 0x00, 0x17, 0x70 };*/
		frame_nonCheck[0] = Address;
		frame_nonCheck[1] = Function;
		memcpy(&frame_nonCheck[2], &Data_Addr, sizeof(Data_Addr));
		memcpy(&frame_nonCheck[4], &Data_Cont, sizeof(Data_Cont));
		//frame_nonCheck[4] = Data_Cont;
		uint16_t check = crc_chk(frame_nonCheck, sizeof(frame_nonCheck));
		char frameRTU[8];
		memcpy(frameRTU, frame_nonCheck, sizeof(frame_nonCheck));
		memcpy(frameRTU + sizeof(frame_nonCheck), &check, sizeof(check));
		for (int i = 0; i < sizeof(frameRTU); i++)
		{
			frameRTU_arr[i] = frameRTU[i];
		}
	};
	private: uint16_t crc_chk(char* data, unsigned char length) {
		int j;
		unsigned int reg_crc = 0xFFFF;
		while (length--) {
			reg_crc ^= *data++;
			for (j = 0; j < 8; j++) {
				if (reg_crc & 0x01) { /* LSB(b0)=1 */
					reg_crc = (reg_crc >> 1) ^ 0xA001;
				}
				else {
					reg_crc = reg_crc >> 1;
				}
			}
		}
		return reg_crc;
	};
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (comboBox1->Text != "")
		{
			if (!button1_status)
			{
				serialPort1->BaudRate = 9600;
				serialPort1->PortName = comboBox1->Text;
				try
				{
					serialPort1->Open();
					label1->Text = "Serial Status: Connected";
					button1->Text = "Disconnect";
					button1_status = true;
					start_bt->Enabled = true;
					stop_bt->Enabled = true;
				}
				catch (...)
				{
					MessageBox::Show("Have problem when open Serial", "ERR", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			else
			{
				try
				{
					serialPort1->Close();
					button1_status = false;
					button1->Text = "Connect";
					label1->Text = "Serial Status: Disconnected";
					start_bt->Enabled = false;
					stop_bt->Enabled = false;
				}
				catch (...)
				{
					MessageBox::Show("Have problem when close Serial", "ERR", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}
		else
		{
			MessageBox::Show("Please select COM port", "Infor", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		
	}
private: System::Void formClosing_Func(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	if (serialPort1->IsOpen == true)
	{
		serialPort1->Close();
	}
}

private: System::Void start_bt_Click(System::Object^ sender, System::EventArgs^ e) {
	
	FrameRTU_Get(0x01, 0x06, 0x0020, 0x1200); //start
	for (int i = 0; i < 8; i++)
	{
		Debug::Write(" 0x" + frameRTU_arr[i].ToString("X2"));
	}
	serialPort1->Write(frameRTU_arr, 0, 8);
}
private: System::Void stop_bt_Click(System::Object^ sender, System::EventArgs^ e) {
	FrameRTU_Get(0x01, 0x06, 0x0020, 0x0100); //stop
	for (int i = 0; i < 8; i++)
	{
		Debug::Write(" 0x" + frameRTU_arr[i].ToString("X2"));
	}
	serialPort1->Write(frameRTU_arr, 0, 8);
}

};
}
