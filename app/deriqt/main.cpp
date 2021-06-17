#include "CTPTraderHandler.h"
#include "CTPMdHandler.h"
#include "INIReader.h"
#include "UserStruct.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <sys/types.h>
#include "TickToKlineHelper.h"
#include "DataStrategy.h"
#include "TStrategy.h"
// #include "models/data_analysis.h"
#include <algorithm>
#include <glog/logging.h>

int nRequestID = 0;
int DEBUG = 0;


//@param main mode instrument conf/trade_date
// bool cmp_max(std::pair<std::string, double> x, std::pair<std::string, double>y)
// {
//     return x.second < y.second;
// }

int main(int argc, char *argv[])
{

    // std::unordered_map<std::string, std::string> _m;
    // _m.insert(std::pair<std::string, std::string>("a","1"));
    // if(_m.find("b") == _m.end())
    // {
    //     std::cout<<"key not exist"<<std::endl;
    // }else{std::cout<<"key exist"<<std::endl;}
    // std::cout<<_m["a"]<<std::endl;
    // _m["a"] = "2";
    // std::cout<<_m["a"]<<std::endl;
    // return 0;
    // test_recordio();
    // return 0;
    // std::vector<std::pair<std::string, double>> v_tmp;
    // v_tmp.push_back(std::pair<std::string, double>("a", 4));
    // v_tmp.push_back(std::pair<std::string, double>("b", 3));
    // sort(v_tmp.begin(), v_tmp.end(), cmp_max);
    // for(const auto& t:v_tmp)
    // {
    //     std::cout<<t.first<<":"<<t.second<<std::endl;
    // }
    // return 0;

    // // ...

    // google::InitGoogleLogging(argv[0]);
    // FLAGS_log_dir = std::string("./log/");
    std::string _conf_file_name;
    std::string _instrument_id;
    std::string mode = "0";
    std::string _strategy_name = "data_strategy";
    std::vector<std::string> v_instrumentID;
    
    if (argc <= 1)
    {
        LOG(ERROR) << "Please enter a config name" ;
        _conf_file_name = "/home/kiki/projects/DERIQT/test.ini";
        v_instrumentID.push_back("rb2110");
        _strategy_name = "data_strategy";
    }
    else
    {
        _conf_file_name = argv[3];
        _instrument_id = argv[2];
        mode = argv[1];
        std::stringstream sstr(_instrument_id);
        std::string token;
        while (getline(sstr, token, ','))
        {
            v_instrumentID.push_back(token);
        }
    }
    
    // if(mode == "1")
    // {
    //     std::string _trade_date = argv[3];
    //     for(auto it=v_instrumentID.begin(); it != v_instrumentID.end(); ++it)
    //     {
    //         data_preprocessing(*it, _trade_date);
    //     }
    //     return 0;
    // }
#if 1
    QTStrategyBase *p_strategy = nullptr;
    if (_strategy_name == "data_strategy")
    {
        p_strategy = new DataStrategy("data_strategy");
    }
    else if (_strategy_name == "t_strategy")
    {
        p_strategy = new TStrategy("t_strategy");
    }
    p_strategy->init(v_instrumentID, _conf_file_name);



#if true
    sleep(5);
    std::string _user_id = "105600687";
    std::string _broker_id = "9040";

    std::vector<CThostFtdcInvestorPositionField *>  ret_pos = p_strategy->get_investor_position(_user_id, _broker_id);
    sleep(5);

    // int ret_trades = p_strategy->req_trade(_user_id, _broker_id);
    // sleep(5);

    std::vector<CThostFtdcTradingAccountField*>  ret_account = p_strategy->get_account(_user_id, _broker_id);
    sleep(5);

    // int ret_pos_detail = p_strategy->get_position_details(_user_id, _broker_id);
    sleep(5);
#endif

    // p_strategy->read_trading_account();
    // std::vector<CThostFtdcInvestorPositionField *> ret_position = p_strategy->get_investor_position(_user_id, _broker_id);
    // for(auto it=ret_position.begin(); it!=ret_position.end();++it)
    // {
    //     std::cout<<(*it)->InstrumentID<<","<<(*it)->CloseAmount<<","<<(*it)->OpenAmount<<","<<(*it)->Position<<","<<(*it)->OpenCost<<std::endl;
    // }
    //start strategy 
    p_strategy->start();
    p_strategy->stop();
    p_strategy->release();
#endif

    return 0;
}
