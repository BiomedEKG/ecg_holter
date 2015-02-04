/*
#include"Waves.h"

void envelope(vector<double>::iterator signal_start, vector<double>::iterator signal_end, vector<double>::iterator hilbert_start, vector<double>::iterator hilbert_end)
{
	for(int i=0; i<signal_end-signal_start;i++)
	{
		*(signal_start+i)=sqrt(pow(*(signal_start+i),2)+pow(*(hilbert_start+i),2));
	}
}

WavesResult* Waves::compute(ResultKeeper *rkp)const {

	vector<double> *ECGBaselineData;
	vector<double> *RPeaksData;
	/*
	ECGBaselineData = rkp.GetResultECGBaseline.GetECGBaselineData(); /// Przypisanie danych ECGBaseline na ktorych beda wykonywane obliczenia
	RPeaksData = rkp.GetResultRPeaks.GetRPeaksData(); /// Przypisanie danych RPeaks na ktorych beda wykonywane obliczenia
	*//*

	WavesResult  ResultHolder = WavesResult();///stworz obiekt rezultatu
	ResultHolder.SetWavesResultData(WavesData);////Przypisz dane z klasy liczacej do danych klasy z klasy rezultatu

	return ResultHolder.getResult();// Zwroc odpowiedni wskaünik
}

void Waves::set_qrs_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	//onset_vector1 = costam;
	const float low_freq_lim = 0.5; //porownac te gowna z raportem
	const float hi_freq_lim = 40;
	double a_t_max, env_t=0.0, a_t=0.0;
	int window_qrs_onset=ceil(0.1*sampling_frequency);
	int sliding_win_start,s2=0,tp_int=0,w=0,temp_j=0,win_end=0;
	vector<double> envelope_win, qrs_onset_it;
	vector<double>::const_iterator tp, envelope_end, envelope_start;
	vector<double> signal(ECGBaselineData.end()-ECGBaselineData.begin()),hilbert(ECGBaselineData.end()-ECGBaselineData.begin());
	//2 LINIE PONIZEJ BEDZIE CHYBA MOZNA WYJEBAC, BO JAK NA RAZIE NIC Z TEGO NIE KORZYSTA
	//fft_filter(ECGBaselineData.begin(), ECGBaselineData.end(), signal.begin(), signal.end(),sampling_frequency,low_freq_lim,hi_freq_lim);
	//hilbert_transform(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
	envelope(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
	envelope_end=signal.end();
	envelope_start=signal.begin();
	//vector<double>::const_iterator ecg_baseline_start = ECGBaselineData.begin(); //sprawdzic. tu widac, jaki to typ danych
	//double gowno = ECGBaselineData.at(0); // wyjebac
	for(int i=0; i<RPeaksData.end()-RPeaksData.begin(); i++)
	{
		if (!((RPeaksData.at(i)-ECGBaselineData.at(0))-window_qrs_onset < 0))
		{
			a_t_max=-HUGE_VAL; //bylo: -INFINITY; czy mozna tak sobie zmienic...?
			sliding_win_start=RPeaksData.at(i)-ECGBaselineData.at(0)-window_qrs_onset;
			for(int j=RPeaksData.at(i)-ECGBaselineData.at(0)-1;j>=sliding_win_start;j--)
			{
				if (j+window_qrs_onset>envelope_end-envelope_start) // WSZYSTKO NIZEJ: CZY NIE TRZEBA ZAMIENIAC . NA -> ?
					win_end=envelope_end-envelope_start;
				else
					win_end=j+window_qrs_onset;
				envelope_win.clear();
				a_t=0;
				for(int k=j;k<=win_end;k++)
					envelope_win.push_back(*(envelope_start+k));
				env_t=*(envelope_start+j);
				tp=(envelope_win.begin());
				for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
				{
					a_t+=*it-env_t;
					if (*tp<*it)
						tp=it;
				}
				if (a_t_max<a_t)
				{
					a_t_max=a_t;
					s2=j;
					tp_int=tp-envelope_win.begin()+j-1;
				}
			}
			w=tp_int-s2;
			a_t_max=-HUGE_VAL; //POPRAWIC?
			for(int j=(RPeaksData.at(i)-ECGBaselineData.at(0))-1;j>=s2;j--)
			{
				a_t=0;
				envelope_win.clear();
				for(int k=j;k<=j+w;k++)
					envelope_win.push_back(*(envelope_start+k));
				env_t=*(envelope_start+j);
				for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
				{
					a_t+=*it-env_t;
				}
				if (a_t_max<a_t)
				{
					a_t_max=a_t;
					temp_j=j;
				}
			}
			if (temp_j!=0){
				qrs_onset_it.push_back(ECGBaselineData.at(0)+temp_j);
			}
		}
		// return nie powinno byc??? -> zmienilem na void, jest spoko?
	}
}

	void Waves::set_qrs_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
		const float low_freq_lim = 5;
		const float hi_freq_lim = 30;
		double a_t_max, env_t=0.0, a_t=0.0;
		int window_qrs_end=ceil(0.1*sampling_frequency);
		int sliding_win_end,s2=0,tp_int=0,w=0,temp_j=-1;
		vector<double> envelope_win;
		vector<double>::const_iterator tp, envelope_end, envelope_start;
		vector<double> signal(ECGBaselineData.end()-ECGBaselineData.begin());
		vector<double> hilbert(ECGBaselineData.end()-ECGBaselineData.begin()); // DO CZEGO TO KURWA JEST
		//fft_filter(ECGBaselineData.begin(), ECGBaselineData.end(), signal.begin(), signal.end(),sampling_frequency,low_freq_lim,hi_freq_lim);
		//hilbert_transform(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
		envelope(signal.begin(), signal.end(), hilbert.begin(), hilbert.end());
		envelope_end=signal.end();
		envelope_start=signal.begin();
		for(int i=0; i<RPeaksData.end()-RPeaksData.begin(); i++)
		{
			if (!((RPeaksData.at(i)-ECGBaselineData.at(0))+window_qrs_end > envelope_end-envelope_start))
			{
				a_t_max=-HUGE_VAL;
				sliding_win_end=(RPeaksData.at(i)-ECGBaselineData.at(0))+window_qrs_end;
				for(int j=(RPeaksData.at(i)-ECGBaselineData.at(0))+1;j<=sliding_win_end;j++)
				{
					envelope_win.clear();
					if (j-window_qrs_end<0)
					{
						for(int k=0;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					else
					{
						for(int k=j-window_qrs_end;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					a_t=0;
					env_t=*(envelope_start+j);
					tp=(envelope_win.begin());
					for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
					{
						a_t+=*it-env_t;
						if (*tp<*it)
						{
							tp=it;
						}
					}
					if (a_t_max<a_t)
					{
						a_t_max=a_t;
						s2=j;
						tp_int=tp-envelope_win.begin()+j-envelope_win.size();
					}
				}
				w=s2-tp_int;
				a_t_max=-HUGE_VAL;
				for(int j=(RPeaksData.at(i)-ECGBaselineData.at(0))+1;j<=s2;j++)
				{
					a_t=0;
					envelope_win.clear();
					if (j-w<0)
					{
						for(int k=0;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					else
					{
						for(int k=j-w;k<=j;k++)
							envelope_win.push_back(*(envelope_start+k));
					}
					env_t=*(envelope_start+j);
					for(vector<double>::iterator it=envelope_win.begin();it!=envelope_win.end();it++)
					{
						a_t+=*it-env_t;
					}
					if (a_t_max<a_t)
					{
						a_t_max=a_t;
						temp_j=j;
					}
				}
				if (temp_j!=-1)
				{
					qrs_end_it.push_back(ECGBaselineData.begin()+temp_j); //CO POETA MIAL NA MYSLI? o_O
				}
			}
		}
}
		/*
		const vector<vector<double>::const_iterator> & Waves::get_qrs_begin() //TO POETA MIAL NA MYSLI :D, glupie, zmienic na get_qrs_end
		{
		return qrs_end_it; //z tego beda korzystac kolejne funkcje
		}
		*//*
		void Waves::set_p_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){

			double Rv;
			double mediana=0;
			double Pmax=0;
			int P_mid;
			int ipeak=0;
			int poczatek;
			QVector<int> window_length;
			QVector<double> PToneset;
			QVector<double> dPToneset;
			QVector<double> window_signal;
			QVector<double> onset_signal;
			QVector<double> Pt;
			QVector<double> M;
			int p_one_end_window=ceil(0.1*sampling_frequency);
			for(int i=0;i<RPeaksData.size()-1;i++) // iteracja do ostatniego znalezionego piku R
			// for(int i=1;i<RPeaksData.size();i++)
			{
				//ponizej: i to jest chyba bzdura... bo to jest odejmowanie amplitudy w punkcie .at(0) od numeru probki w punkcie .at(i+1)
				//a chcemy znalezc 
				window_length.push_back(ceil(0.25*((RPeaksData.at(i+1)-ECGBaselineData.at(0))-(RPeaksData.at(i)-ECGBaselineData.at(0)))));
				// window_length.push_back(RPeaks.at(i
				// powyzej: do pustego wektora window_length dopisywane sa (jeden po drugim)
				// kolejne elementy o wartosciach 1/4*odleglosc miedzy biezacym, a poprzedzajacym pikiem R
				// w Rpeaks sπ INDEKSY WYBRANYCH ELEMENTOW z wektora ECGBaseline 
			}
			if((qrs_onset_it.at(0)-ECGBaselineData.begin())>(RPeaksData.at(0)-ECGBaselineData.at(0))) //jesli qrs_end_it jest dobrze, to tez bedzie dzialac
			{
				poczatek=0;
			}
			else
				poczatek=1;
			// ponizej szukamy szczytow fali P:
			//1. 
			for(int i=0;i<window_length.size();i++)
			{
				Rv=0.003;
				for(int j=0;j<window_length.at(i);j++)
				{
					window_signal.push_back(ECGBaselineData.at(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i)+j));
				}
				for(int j=0;j<window_signal.size();j++)
				{
					mediana+=window_signal.at(j);
				}
				mediana/=window_length.at(i);
				for(int j=0;j<window_signal.size();j++)
				{
					window_signal.replace(j,window_signal.at(j)-mediana); //czyzby problem bo vector zamiast QVector...?
					Pt.push_back(atan(window_signal.at(j)/Rv));
					M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
				}
				mediana=0;
				for(int j=0;j<Pt.size();j++)
				{
					if(Pmax<=Pt.at(j))
					{
						Pmax=Pt.at(j);
						ipeak=j+1;
					}
				}
				if(ipeak==1||ipeak==Pt.size())
				{
					window_signal.clear();
					Pt.clear();
					Pmax=0;
					M.clear();
					continue;
				}
				if((M.at(ipeak-2)<M.at(ipeak-1))&&(M.at(ipeak-1)>M.at(ipeak)))
				{
					P_mid=ipeak+(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i));
					Rv=0.005;
					for(int j=P_mid-p_one_end_window;j<P_mid;j++)
					{
						onset_signal.push_back(ECGBaselineData.at(j));
						mediana+=onset_signal.last();
					}
					mediana/=onset_signal.size();
					for(int j=0;j<onset_signal.size();j++)
					{
						onset_signal.replace(j,onset_signal.at(j)-mediana);
					}
					mediana=0;
					for(int j=0;j<onset_signal.size();j++)
					{
						PToneset.push_back(atan(onset_signal.at(j)/Rv));
						if(j==0)
							continue;
						else
						{
							dPToneset.push_back(PToneset.at(j)-PToneset.at(j-1));
							if(dPToneset.last()>0.07)
							{
								p_onset_it.push_back(ECGBaselineData.begin()+P_mid-p_one_end_window+j);
								break;
							}
						}
					}
				}
				window_signal.clear();
				onset_signal.clear();
				Pt.clear();
				M.clear();
				PToneset.clear();
				dPToneset.clear();
				Pmax=0;
			}
	}
	/*
	const vector<vector<double>::const_iterator> & Waves::get_p_onset() //TO POETA MIAL NA MYSLI :D
	{
	return p_onset_it; //z tego beda korzystac kolejne funkcje
	}
	*//*
	void Waves::set_p_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
		double Rv;
		double mediana=0;
		double Pmax=0;
		int P_mid;
		int ipeak;
		int poczatek;
		int window=0;
		QVector<int> window_length; //dojebalem QVectory, zobaczymy czy bedzie budowal BUDUJE W CHUJ :D
		QVector<double> PTend;
		QVector<double> dPTend;
		QVector<double> window_signal;
		QVector<double> onset_signal;
		QVector<double> Pt;
		QVector<double> M;
		int p_one_end_window=ceil(0.1*sampling_frequency);
		for(int i=0;i<RPeaksData.size()-1;i++)
		{
			window_length.push_back(ceil(0.25*((RPeaksData.at(i+1)-ECGBaselineData.at(0))-(RPeaksData.at(i)-ECGBaselineData.at(0)))));
		}
		if((qrs_onset_it.at(0)-ECGBaselineData.begin())>(RPeaksData.at(0)-ECGBaselineData.at(0)))
		{
			poczatek=0;
		}
		else
			poczatek=1;
		for(int i=0;i<window_length.size();i++)
		{
			Rv=0.003;
			for(int j=0;j<window_length.at(i);j++)
			{
				window_signal.push_back(ECGBaselineData.at(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i)+j));
			}
			for(int j=0;j<window_signal.size();j++)
			{
				mediana+=window_signal.at(j);
			}
			mediana/=window_length.at(i);
			for(int j=0;j<window_signal.size();j++)
			{
				window_signal.replace(j,window_signal.at(j)-mediana);
				Pt.push_back(atan(window_signal.at(j)/Rv));
				M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
			}
			mediana=0;
			for(int j=0;j<Pt.size();j++)
			{
				if(Pmax<=Pt.at(j))
				{
					Pmax=Pt.at(j);
					ipeak=j+1;
				}
			}
			if(ipeak==1||ipeak==Pt.size())
			{
				window_signal.clear();
				Pt.clear();
				Pmax=0;
				M.clear();
				continue;
			}
			if((M.at(ipeak-2)<M.at(ipeak-1))&&(M.at(ipeak-1)>M.at(ipeak)))
			{
				P_mid=ipeak+(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i));
				if(P_mid+p_one_end_window-1>qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin()) //nie powinno byc {} ??
					window=(qrs_onset_it.at(i+poczatek)-ECGBaselineData.begin())-P_mid+1;
				else
					window=p_one_end_window;
				Rv=0.005;
				for(int j=P_mid-1;j<P_mid+window-1;j++)
				{
					onset_signal.push_back(ECGBaselineData.at(j));
					mediana+=onset_signal.last();
				}
				mediana/=onset_signal.size();
				for(int j=0;j<onset_signal.size();j++)
				{
					onset_signal.replace(j,onset_signal.at(j)-mediana);
					PTend.push_back(atan(onset_signal.at(j)/Rv));
				}
				mediana=0;
				for(int j=onset_signal.size();j>0;j--)
				{
					if(j==(onset_signal.size()))
						continue;
					else
					{
						dPTend.push_front(PTend.at(j-1)-PTend.at(j));
					}
				}
				for(int j=dPTend.size();j>0;j--)
				{
					if(dPTend.at(j-1)>0.07)
					{
						p_end_it.push_back(ECGBaselineData.begin()+P_mid+j-2);
						break;
					}
				}
			}
			window_signal.clear();
			onset_signal.clear();
			Pt.clear();
			M.clear();
			PTend.clear();
			dPTend.clear();
			Pmax=0;
		}
	}

void Waves::set_t_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){

			double Rv;
			double mediana=0;
			double Tmax=0; //Pmax
			int T_mid; //P_mid
			int ipeak=0;
			int poczatek;
			QVector<int> window_length;
			QVector<double> PToneset;
			QVector<double> dPToneset;
			QVector<double> window_signal;
			QVector<double> onset_signal;
			QVector<double> Pt;
			QVector<double> M;
			int t_one_start_window=ceil(0.1*sampling_frequency); // tu zmienic na t_one_end_window / t_one_start_window
			for(int i=0;i<RPeaksData.size()-1;i++)
			{
				window_length.push_back(ceil(0.25*((RPeaksData.at(i+1)-ECGBaselineData.at(0))-(RPeaksData.at(i)-ECGBaselineData.at(0)))));
			}
			if((qrs_end_it.at(0)-ECGBaselineData.begin())>(RPeaksData.at(0)-ECGBaselineData.at(0))) //zmieniono na  qrs_end_it
			{
				poczatek=0;
			}
			else
				poczatek=1;
			for(int i=0;i<window_length.size();i++)
			{
				Rv=0.1; //zmieniono z 0.003
				for(int j=0;j<window_length.at(i);j++)
				{
					window_signal.push_back(ECGBaselineData.at(qrs_end_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i)+j)); //end
				}
				for(int j=0;j<window_signal.size();j++)
				{
					mediana+=window_signal.at(j);
				}
				mediana/=window_length.at(i);
				for(int j=0;j<window_signal.size();j++)
				{
					window_signal.replace(j,window_signal.at(j)-mediana);
					Pt.push_back(atan(window_signal.at(j)/Rv));
					M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
				}
				mediana=0;
				for(int j=0;j<Pt.size();j++)
				{
					if(Tmax<=Pt.at(j))
					{
						Tmax=Pt.at(j);
						ipeak=j+1;
					}
				}
				if(ipeak==1||ipeak==Pt.size())
				{
					window_signal.clear();
					Pt.clear();
					Tmax=0;
					M.clear();
					continue;
				}
				if((M.at(ipeak-2)<M.at(ipeak-1))&&(M.at(ipeak-1)>M.at(ipeak)))
				{
					T_mid=ipeak+(qrs_end_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i)); //end
					Rv=0.1; //zmieniono z 0.005
					for(int j=T_mid-t_one_start_window;j<T_mid;j++)
					{
						onset_signal.push_back(ECGBaselineData.at(j));
						mediana+=onset_signal.last();
					}
					mediana/=onset_signal.size();
					for(int j=0;j<onset_signal.size();j++)
					{
						onset_signal.replace(j,onset_signal.at(j)-mediana);
					}
					mediana=0;
					for(int j=0;j<onset_signal.size();j++)
					{
						PToneset.push_back(atan(onset_signal.at(j)/Rv));
						if(j==0)
							continue;
						else
						{
							dPToneset.push_back(PToneset.at(j)-PToneset.at(j-1));
							if(dPToneset.last()>0.07) // dlaczego 0.07...? :(
							{
								p_onset_it.push_back(ECGBaselineData.begin()+T_mid-t_one_start_window+j); // zmienic
								break;
							}
						}
					}
				}
				window_signal.clear();
				onset_signal.clear();
				Pt.clear();
				M.clear();
				PToneset.clear();
				dPToneset.clear();
				Tmax=0;
			}
	}

void Waves::set_t_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
		double Rv;
		double mediana=0;
		double Tmax=0; // Pmax --> Tmax
		int T_mid; //P_mid --> Tmax
		int ipeak;
		int poczatek;
		int window=0;
		QVector<int> window_length;
		QVector<double> PTend;
		QVector<double> dPTend;
		QVector<double> window_signal;
		QVector<double> onset_signal;
		QVector<double> Pt;
		QVector<double> M;
		int t_one_end_window=ceil(0.1*sampling_frequency); //p_one_end_window --> t_one_end_window
		for(int i=0;i<RPeaksData.size()-1;i++)
		{
			window_length.push_back(ceil(0.25*((RPeaksData.at(i+1)-ECGBaselineData.at(0))-(RPeaksData.at(i)-ECGBaselineData.at(0)))));
		}
		if((qrs_end_it.at(0)-ECGBaselineData.begin())>(RPeaksData.at(0)-ECGBaselineData.at(0)))
		{
			poczatek=0;
		}
		else
			poczatek=1;
		for(int i=0;i<window_length.size();i++)
		{
			Rv=0.003;
			for(int j=0;j<window_length.at(i);j++)
			{
				window_signal.push_back(ECGBaselineData.at(qrs_end_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i)+j));
			}
			for(int j=0;j<window_signal.size();j++)
			{
				mediana+=window_signal.at(j);
			}
			mediana/=window_length.at(i);
			for(int j=0;j<window_signal.size();j++)
			{
				window_signal.replace(j,window_signal.at(j)-mediana);
				Pt.push_back(atan(window_signal.at(j)/Rv));
				M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
			}
			mediana=0;
			for(int j=0;j<Pt.size();j++)
			{
				if(Tmax<=Pt.at(j))
				{
					Tmax=Pt.at(j);
					ipeak=j+1;
				}
			}
			if(ipeak==1||ipeak==Pt.size())
			{
				window_signal.clear();
				Pt.clear();
				Tmax=0;
				M.clear();
				continue;
			}
			if((M.at(ipeak-2)<M.at(ipeak-1))&&(M.at(ipeak-1)>M.at(ipeak)))
			{
				T_mid=ipeak+(qrs_end_it.at(i+poczatek)-ECGBaselineData.begin()-window_length.at(i));
				if(T_mid+t_one_end_window-1>qrs_end_it.at(i+poczatek)-ECGBaselineData.begin())
					window=(qrs_end_it.at(i+poczatek)-ECGBaselineData.begin())-T_mid+1;
				else
					window=t_one_end_window;
				Rv=0.005;
				for(int j=T_mid-1;j<T_mid+window-1;j++)
				{
					onset_signal.push_back(ECGBaselineData.at(j));
					mediana+=onset_signal.last();
				}
				mediana/=onset_signal.size();
				for(int j=0;j<onset_signal.size();j++)
				{
					onset_signal.replace(j,onset_signal.at(j)-mediana);
					PTend.push_back(atan(onset_signal.at(j)/Rv));
				}
				mediana=0;
				for(int j=onset_signal.size();j>0;j--)
				{
					if(j==(onset_signal.size()))
						continue;
					else
					{
						dPTend.push_front(PTend.at(j-1)-PTend.at(j));
					}
				}
				for(int j=dPTend.size();j>0;j--)
				{
					if(dPTend.at(j-1)>0.07)
					{
						p_end_it.push_back(ECGBaselineData.begin()+T_mid+j-2);
						break;
					}
				}
			}
			window_signal.clear();
			onset_signal.clear();
			Pt.clear();
			M.clear();
			PTend.clear();
			dPTend.clear();
			Tmax=0;
		}
	}
	*/

 //------------------------------------------------------------------------ LEPSZE WAVES: 
 /*


 #include"Waves.h"

WavesResult* Waves::compute(ResultKeeper *rkp)const {

	vector<double> *ECGBaselineData;
	vector<double> *RPeaksData;
	
	//ECGBaselineData = rkp.GetResultECGBaseline.GetECGBaselineData(); /// Przypisanie danych ECGBaseline na ktorych beda wykonywane obliczenia
	//RPeaksData = rkp.GetResultRPeaks.GetRPeaksData(); /// Przypisanie danych RPeaks na ktorych beda wykonywane obliczenia
	

	WavesResult  ResultHolder = WavesResult();///stworz obiekt rezultatu
	ResultHolder.SetWavesResultData(WavesData);////Przypisz dane z klasy liczacej do danych klasy z klasy rezultatu

	return ResultHolder.getResult();// Zwroc odpowiedni wskaünik
}

double Waves::get_vector_median(vector<double> v) {
	sort(v.begin(), v.end());
	if (v.size() % 2 == 0) {
		return (v[v.size()/2-1] + v[v.size()/2])/2;
	} else {
		return v[v.size()-1];
	}
}

void Waves::ustaw_qrs_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<double> ECGBaselineDataTP;
	// to jest wektor zawieracjacy indexy punktow qrs_onset w ecgBaselineData
	vector<int> ResultIndexVector;
	double Rv=0.001;

	// 1. transformacja wskazowa przy Rv=0.001 calego przefiltrowanego sygnalu, czyli wszystkich elementow wektora ECGBaselineData
	for (int i=0; i<ECGBaselineData.size(); ++i){
		ECGBaselineDataTP.push_back(atan(ECGBaselineData.at(i)/Rv));
	}
	//	Pt.push_back(atan(window_signal.at(j)/Rv));
		//	M.push_back(sqrt(pow(Rv,2)+ pow(window_signal.at(j),2)));
	

	// 2. poszukiwanie na lewo od kazdego piku R NA PRZETRANSFORMOWANYM SYGNALE punktu takiego, ze fi[n] < 0.25*pi
	//    kolejne probki wektora RPeaksData wskazuja na miejsce w wektorze ECGBaselineData, od ktorego trzeba szukac, cofajac sie
	//    szukac trzeba nie na ECGBaselineData, tylko na wektorze stworzonym w punkcie 1.
	//    dostajemy w wyniku dzialania wektor qrs_lewo numerow probek
	for (int i=RPeaksData.size()-1; i>=0; --i){
		double amp = 1;
		int index = 0;
		while (amp<=0.25*3.1415){
			for (int j = i; j>=0; --j){
				amp = ECGBaselineDataTP.at(j);
				index = j;
			}
		}
		vector<double> SortedMeasures;
		vector<double> Measures;
		// 3. 35 ms okno na lewo wzgledem probek o numerach wzietych z wektora qrs_lewo
	//    fs = 360 Hz --> ile probek przypada na 35 ms??
	//    czyli bierzemy pod uwage 13 probek, tzn. TransformedECGBaseline(qrs_lewo-13) : TransformedECGBaseline(qrs_lewo-1)
	//    TO ZAWSZE BEDZIE TAKIE SAMO OKNO
		for (int j=13; j>0; --j){
			while (index-j>0){
				SortedMeasures.push_back(ECGBaselineData.at(index-j));
				Measures.push_back(ECGBaselineData.at(index-j));
			}
		}
		// 4. w tym zakresie (13 probek) na ORYGINALNYM ECGBaselineData robimy po kolei:
	//    a) liczymy mediane WARTOSCI tych 13 probek ECGBaselineData 
	//    b) odejmujemy mediane od sygnalu
	//    c) liczymy wartosc bezwzgledna tego sygnalu ktory dostalismy w b) --> abs(costam(costam))
	//    d) robimy PT przy Rv = 0.005
	//    e) w kaødym oknie szukamy minimum i to sa punkty QRS_ONSET i je trzeba wspisac do wektora (jako numery probek im odpowiadajacych)
		sort(SortedMeasures.begin(), SortedMeasures.end());
		double median = SortedMeasures.at(6);
		double min = 4;
		int min_index = 0;
		for (int j=0; j<Measures.size(); ++j) {
			Measures[j] = atan(abs(Measures[j]-median)/0.005);
			if (Measures[j] < min) {
				min = Measures[j];
				min_index = j;
			}
		}
		ResultIndexVector.push_back(min_index);
	}
	qrs_onset_index_vector = ResultIndexVector;
}

void Waves::ustaw_qrs_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<double> ECGBaselineDataTP;
	// to jest wektor zawieracjacy indexy punktow qrs_onset w ecgBaselineData
	vector<int> ResultIndexVector;
	double Rv=0.001;

	// 1. transformacja wskazowa przy Rv=0.001 calego przefiltrowanego sygnalu, czyli wszystkich elementow wektora ECGBaselineData
	for (int i=0; i<ECGBaselineData.size(); ++i){
		ECGBaselineDataTP.push_back(atan(ECGBaselineData.at(i)/Rv));
	}
		
	for (int i=RPeaksData.size()-1; i>=0; --i){ // tak bylo dla qrs_onset, ale chyba przeszukiwanie od konca nie szkodzi
	//for (int i=0; i<=(RPeaksData.size()-1); ++i){ // i to jest za kaødym razem element RPeaksData, czyli nr piku R!!
		double amp = 1;
		int index = 0;
		while (amp<=0.25*3.1415){
			for (int j = i; j>=0; ++j){ // zmiana z --j, poniewaz idziemy w prawo od piku R
				amp = ECGBaselineDataTP.at(j);  // wpisujemy amplitude tego punktu (qrs+) do EBDTP w miejsce j.
				index = j;
			}
		}
		vector<double> SortedMeasures;
		vector<double> Measures;
		// 3. 35 ms okno na lewo wzgledem probek o numerach wzietych z wektora qrs_lewo
		//    czyli bierzemy pod uwage 13 probek, tzn. TransformedECGBaseline(qrs_lewo-13) : TransformedECGBaseline(qrs_lewo-1)
		// TERAZ TRZEBA NA PRAWO SZUKAC
		// for (int j=13; j>0; --j){
		for (int j=0; j<13; ++j){
			//while (index-j>0){ // tak bylo dla qrs_onset
			while (index+j<RPeaksData.size()){ // ZABEZPIECZENIE !!
				SortedMeasures.push_back(ECGBaselineData.at(index+j)); // bylo -j
				Measures.push_back(ECGBaselineData.at(index+j)); //bylo -j
			}
		}
		// 4. w tym zakresie (13 probek) na ORYGINALNYM ECGBaselineData robimy po kolei:
	//    a) liczymy mediane WARTOSCI tych 13 probek ECGBaselineData 
	//    b) odejmujemy mediane od sygnalu
	//    c) liczymy wartosc bezwzgledna tego sygnalu ktory dostalismy w b) --> abs(costam(costam))
	//    d) robimy PT przy Rv = 0.005
	//    e) w kaødym oknie szukamy minimum i to sa punkty QRS_ONSET i je trzeba wspisac do wektora (jako numery probek im odpowiadajacych)
		sort(SortedMeasures.begin(), SortedMeasures.end());
		double median = SortedMeasures.at(6);
		double min = 4;
		int min_index = 0;
		for (int j=0; j<Measures.size(); ++j) { // znowu mozemy uzyc j
			Measures[j] = atan(abs(Measures[j]-median)/0.005);
			if (Measures[j] < min) {
				min = Measures[j];
				min_index = j;
			}
		}
		ResultIndexVector.push_back(min_index);
	}
	qrs_end_index_vector = ResultIndexVector;
}

double Waves::get_derivative(vector<double> d){
	sort(d.begin(), d.end());
	if (d.size() % 2 == 0) {
		return (d[d.size()/2-1] + d[d.size()/2])/2;
	} else {
		return d[d.size()-1];
	}
}

void Waves::ustaw_p_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> p_onset_index;
	for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index;
		int j=0;
		// idziemy od poczatku RPeaksData dopoki nie dojdziemy do konca (pierwszy warunek) lub
		// nie znajdziemy pierwszego elementu (indexu) ktory jest wiekszy od danego qrs_onset punktu
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_onset_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j];
		immiediate_left_peak_index = RPeaksData[j-1]; // ZMIANA!!!!!    nie bylo zadeklarowane, ale czy moze byc j-1??
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_onset_index_vector[i]-windows_width), ECGBaselineData.begin() - qrs_onset_index_vector[i]);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) {
			window_signal[j] = atan((window_signal[j]-median)/0.003);
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}
		vector<double> left_window_in_a_window (window_signal.begin() + max_index - 6, window_signal.begin() + max_index);
		int index = left_window_in_a_window.size()-1; 
		
		//while (j>=0) {
			// tu policz pochodna z left_window_in_a_window[j]
			//double derivative = 1.231;
			//if (derivative < 0)
			//	break;
		//}

		double derivative = get_derivative(left_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<left_window_in_a_window.size(); ++j) {
			left_window_in_a_window[j] = atan(abs(left_window_in_a_window[j]-derivative)/0.005);
			if (left_window_in_a_window[j] < dt) {
				dt = left_window_in_a_window[j];
				dt_index = j;
			}
		}

		p_onset_index.push_back(dt_index); // EWENTUALNIE: p_onset_index.push_back(j); !!!
	}
	p_onset_index_vector = p_onset_index;
}

void Waves::ustaw_p_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> p_end_index;
	for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index;
		int j=0;
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_onset_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j];
		immiediate_left_peak_index = RPeaksData[j-1];
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_onset_index_vector[i]-windows_width), ECGBaselineData.begin() - qrs_onset_index_vector[i]);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) {
			window_signal[j] = atan((window_signal[j]-median)/0.003);
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}

		vector<double> right_window_in_a_window (window_signal.begin() + max_index, window_signal.begin() + max_index + 6);
		int index = right_window_in_a_window.size()-1;
		double derivative = get_derivative(right_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<right_window_in_a_window.size(); ++j) {
			right_window_in_a_window[j] = atan(abs(right_window_in_a_window[j]-derivative)/0.005);
			if (right_window_in_a_window[j] < dt) {
				dt = right_window_in_a_window[j];
				dt_index = j;
			}
		}
		p_end_index.push_back(dt_index);
	}
	p_end_index_vector = p_end_index;
}

void Waves::ustaw_t_onset(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> t_onset_index;
	//for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){ // zmienic na qrs end
		for (int i=qrs_end_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index; // Pierwszy R peak jaki znajdujemy przeszukujπc
																// oraz poprzedzajacy --> zmienic na nastepny
		int j=0;
		// idziemy od poczatku RPeaksData dopoki nie dojdziemy do konca (pierwszy warunek) lub
		// nie znajdziemy pierwszego elementu (indexu) ktory jest wiekszy od danego qrs_end punktu
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_end_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j+1]; //zmiana z [j] w stosunku do set_p_onset
		immiediate_left_peak_index = RPeaksData[j];
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_end_index_vector[i]), ECGBaselineData.begin() + qrs_end_index_vector[i] + windows_width);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) { // ZNAJDUJEMY INDEX MAKSIMUM
			window_signal[j] = atan((window_signal[j]-median)/0.1); // tu wystarczy 0.1
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}
		// ODTAD SZUKAMY W NOWYM OKNIE

		vector<double> left_window_in_a_window (window_signal.begin() + max_index - 9, window_signal.begin() + max_index); // szerokosc 9 probek
		int index = left_window_in_a_window.size()-1;
		double derivative = get_derivative(left_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<left_window_in_a_window.size(); ++j) {
			left_window_in_a_window[j] = atan(abs(left_window_in_a_window[j]-derivative)/0.1);
			if (left_window_in_a_window[j] < dt) {
				dt = left_window_in_a_window[j];
				dt_index = j;
			}
		}
		t_onset_index.push_back(dt_index);
	}
	t_onset_index_vector = t_onset_index;
}

void Waves::ustaw_t_end(vector<double> ECGBaselineData, vector<double> RPeaksData, int sampling_frequency){
	vector<int> t_end_index;
	//for (int i=qrs_onset_index_vector.size()-1; i>=0; --i){ // zmienic na qrs end
		for (int i=qrs_end_index_vector.size()-1; i>=0; --i){
		int first_right_peak_index, immiediate_left_peak_index; // Pierwszy R peak jaki znajdujemy przeszukujπc
																// oraz poprzedzajacy --> zmienic na nastepny
		int j=0;
		// idziemy od poczatku RPeaksData dopoki nie dojdziemy do konca (pierwszy warunek) lub
		// nie znajdziemy pierwszego elementu (indexu) ktory jest wiekszy od danego qrs_end punktu
		while (j<RPeaksData.size() || RPeaksData[j] < qrs_end_index_vector[i])
			++j;
		first_right_peak_index = RPeaksData[j+1]; //zmiana z [j] w stosunku do set_p_onset
		immiediate_left_peak_index = RPeaksData[j];
		int windows_width = ceil(0.25*(first_right_peak_index-immiediate_left_peak_index));
		vector<double> window_signal(ECGBaselineData.begin() + (qrs_end_index_vector[i]), ECGBaselineData.begin() + qrs_end_index_vector[i] + windows_width);
		double median = get_vector_median(window_signal);
		double max = -4;
		int max_index = 0;
		for (int j=0;j<window_signal.size();++j) { // ZNAJDUJEMY INDEX MAKSIMUM
			window_signal[j] = atan((window_signal[j]-median)/0.1); // tu wystarczy 0.1
			if (max < window_signal[j]){
				max = window_signal[j];
				max_index = j;
			}
		}

		vector<double> right_window_in_a_window (window_signal.begin() + max_index, window_signal.begin() + max_index + 9);
		int index = right_window_in_a_window.size()-1;
		
		double derivative = get_derivative(right_window_in_a_window);
		double dt = 4;
		int dt_index = 0;
		for (int j=0; j<right_window_in_a_window.size(); ++j) {
			right_window_in_a_window[j] = atan(abs(right_window_in_a_window[j]-derivative)/0.1);
			if (right_window_in_a_window[j] < dt) {
				dt = right_window_in_a_window[j];
				dt_index = j;
			}
		}

		t_end_index.push_back(dt_index);
	}
	t_end_index_vector = t_end_index;
}

*/